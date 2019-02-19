//
// Created by me on 27/01/19.
//

#include "Wamp.h"
#include "wampcc/json.h"
#include <functional>


// TODO WRITE TESTS <3

Wamp::Wamp(shared_ptr<ICommunicationInterface> comInterface, shared_ptr<OBDHandler> obdHandler,
           shared_ptr<VehicleDataProvider> vehicleDataProvider, APP_TYPE type) {
    this->comInterface = comInterface;
    this->obdHandler = obdHandler;
    this->vehicleDataProvider = vehicleDataProvider;
    this->exitRequested = false;
    this->type = type;


    this->subscriptions = make_unique<map<string, pair<Service, Pid>>>();
}

int Wamp::openInterface() {
    this->exitRequested = false;
    wampOpen = true;
    tServe = thread(&Wamp::serve, this);

    return 0;
}

int Wamp::closeInterface() {
    this->exitRequested = true;
    tServe.join();
    wampOpen = false;
    return 0;
}

bool Wamp::isOpen() {
    return wampOpen;
}

void Wamp::serve() {

    // Create an embedded wamp router->
    auto router = make_shared<wampcc::wamp_router>(&the_kernel);


    // Accept clients on IPv4 port, without authentication.
    auto lstFut = router->listen(wampcc::auth_provider::no_auth_required(), 55555);
    if (auto ec = lstFut.get()) {
        LOG(ERROR) << "Failed WAMP start" << ec.message();
        return;
    }

    string clearPidSubscriptionsUrl = "set.service.any.clearPidSubscriptions";
    router->callable(REALM, clearPidSubscriptionsUrl,
                     std::bind(&Wamp::clearPidSubscriptions, this,
                               std::placeholders::_1,
                               std::placeholders::_2,
                               std::placeholders::_3));

    string setUpdateRateUrl = "set.service.any.setUpdateRate";
    router->callable(REALM, setUpdateRateUrl,
                     std::bind(&Wamp::setUpdateRate, this,
                               std::placeholders::_1,
                               std::placeholders::_2,
                               std::placeholders::_3));


    for (auto const&[service, pidCollection] :  *obdHandler->getPidConfig()) {
        std::string serviceUrl = "get.service." + to_string(service);
        router->callable(REALM, serviceUrl,
                         std::bind(&Wamp::getPidsInService, this,
                                   std::placeholders::_1,
                                   std::placeholders::_2,
                                   std::placeholders::_3,
                                   service));

        for (const auto &pid: pidCollection.get_pid_list_as_vector()) {
            if (pid.name.empty()) { continue; }
            std::string url = serviceUrl + "." + pid.name;
            router->callable(REALM, url,
                             std::bind(&Wamp::getPid, this,
                                       std::placeholders::_1,
                                       std::placeholders::_2,
                                       std::placeholders::_3,
                                       service, pid));

            router->callable(REALM, url + ".subscribe",
                             std::bind(&Wamp::subscribeToPid, this,
                                       std::placeholders::_1,
                                       std::placeholders::_2,
                                       std::placeholders::_3,
                                       service, pid, url));

            router->callable(REALM, url + ".unsubscribe",
                             std::bind(&Wamp::unsubscribeFromPid, this,
                                       std::placeholders::_1,
                                       std::placeholders::_2,
                                       std::placeholders::_3,
                                       url));
        }
    }


    while (!exitRequested) {
        wampcc::json_value v = wampcc::json_value::make_array();
        for (auto const&[key, val] : *subscriptions) {
            auto json = getPidData(val.first, val.second);
            v.as<wampcc::json_array>().push_back(json);
        }

        auto args = wampcc::wamp_args();
        args.args_list = v.as<wampcc::json_array>();
        router->publish(REALM, "get.service.any.subscriptions", {}, args);

        this_thread::sleep_for(chrono::milliseconds(updateRate));
    }
}


void Wamp::getPidsInService(wampcc::wamp_router &, wampcc::wamp_session &caller,
                            wampcc::call_info info, Service service) {

    wampcc::json_value v = wampcc::json_value::make_array();
    wampcc::json_object &rootObject = v.append_object();
    auto pids = wampcc::json_value::make_array();

    auto &pidCollection = obdHandler->getPidConfig()->at(service);
    for (const auto &pid: pidCollection.get_pid_list_as_vector()) {
        if (pid.name.empty()) { continue; }
        pids.as<wampcc::json_array>().emplace_back(pid.name);
    }
    rootObject["pids"] = pids;
    caller.result(info.request_id, v.as<wampcc::json_array>());
}


void
Wamp::getPid(wampcc::wamp_router &, wampcc::wamp_session &caller, wampcc::call_info info, Service service, Pid pid) {
    auto json = getPidData(service, pid);
    wampcc::json_value v = wampcc::json_value::make_array();
    v.as<wampcc::json_array>().push_back(json);

    caller.result(info.request_id, v.as<wampcc::json_array>());
}

template<typename T>
void Wamp::addVectorToJsonObject(wampcc::json_value &obj, string name, vector<T> vec) const {
    obj[name] = wampcc::json_value::make_array();
    for (const auto &value : vec) {
        obj[name].as<wampcc::json_array>().emplace_back(value);
    }
}

void Wamp::subscribeToPid(wampcc::wamp_router &, wampcc::wamp_session &caller, wampcc::call_info info, Service service,
                          Pid pid, string key) {
    subscriptionMutex.lock();
    subscriptions->insert({key, {service, pid}});
    subscriptionMutex.unlock();
}

void
Wamp::unsubscribeFromPid(wampcc::wamp_router &, wampcc::wamp_session &caller, wampcc::call_info info, string key) {
    subscriptionMutex.lock();
    subscriptions->erase(key);
    subscriptionMutex.unlock();
}

void Wamp::clearPidSubscriptions(wampcc::wamp_router &, wampcc::wamp_session &caller, wampcc::call_info info) {
    subscriptionMutex.lock();
    subscriptions->clear();
    subscriptionMutex.unlock();
}


wampcc::json_value Wamp::getPidData(const Service &service, const Pid &pid) const {
    shared_ptr<DataObjectValueCollection> dataObjectValue;
    if (type != ECU) {
        vehicleDataProvider->queryVehicle(pid, service);
    }
    vehicleDataProvider->getPrintableDataForPid(service == 2, pid, dataObjectValue);

    wampcc::json_value v = wampcc::json_value::make_object();

    auto jsonService = wampcc::json_value::make_object();
    jsonService["id"] = service;
    v["service"] = jsonService;

    auto jsonPid = wampcc::json_value::make_object();
    jsonPid["name"] = pid.name;
    jsonPid["id"] = pid.id;
    jsonPid["size"] = pid.size;
    jsonPid["name"] = pid.name;
    jsonPid["description"] = pid.description;
    jsonPid["datafields"] = pid.datafields;
    addVectorToJsonObject(jsonPid, "minValues", pid.minValues);
    addVectorToJsonObject(jsonPid, "maxValues", pid.maxValues);
    addVectorToJsonObject(jsonPid, "units", pid.units);

    v["pid"] = jsonPid;

    auto jsonData = wampcc::json_value::make_array();
    wampcc::json_value jsonDataValue;
    for (const shared_ptr<DataObjectValue> &dataVal : *dataObjectValue->getValues()) {
        jsonDataValue = wampcc::json_value::make_object();
        jsonDataValue["numberValue"] = dataVal->getValue();

        const auto &desc = dataVal->getDescription();
        jsonDataValue["name"] = desc->getDescriptionText();
        jsonDataValue["name"] = desc->getDescriptionText();
        jsonDataValue["unit"] = desc->getUnit().toShortString();
        jsonDataValue["min"] = desc->getMin();
        jsonDataValue["max"] = desc->getMax();

        auto details = wampcc::json_value::make_object();
        for (const auto &detail : *dataVal->getDetails()) {
            details[detail.first] = detail.second;
        }
        jsonDataValue["details"] = details;
        jsonData.as<wampcc::json_array>().push_back(jsonDataValue);
    }
    v["data"] = jsonData;
    return v;
}

bool Wamp::isExitRequested() {
    return this->exitRequested;
}

void Wamp::setUpdateRate(wampcc::wamp_router &, wampcc::wamp_session &caller, wampcc::call_info info) {
    if (info.args.args_list.size() == 1) {
        updateRate = info.args.args_list[0].as_int();
    }

}

