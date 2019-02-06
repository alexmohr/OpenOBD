//
// Created by me on 27/01/19.
//

#include "Wamp.h"
#include "wampcc/json.h"
#include <functional>

Wamp::Wamp(shared_ptr<ICommunicationInterface> comInterface, shared_ptr<OBDHandler> obdHandler) {
    this->comInterface = comInterface;
    this->obdHandler = obdHandler;
    this->vehicleDataProvider = make_unique<VehicleDataProvider>(obdHandler, comInterface);
    this->exitRequested = false;
}

int Wamp::openInterface() {
    this->exitRequested = false;
    tServe = thread(&Wamp::serve, this);
    return 0;
}

int Wamp::closeInterface() {
    this->exitRequested = true;
    tServe.join();
    return 0;
}

void Wamp::serve() {

    // Create an embedded wamp router.
    wampcc::wamp_router router(&the_kernel);

    // Accept clients on IPv4 port, without authentication.
    auto lstFut = router.listen(wampcc::auth_provider::no_auth_required(), 55555);
    if (auto ec = lstFut.get()) {
        LOG(ERROR) << "Failed WAMP start" << ec.message();
        return;
    }

    router.callable("openobd", "greeting",
                    [](wampcc::wamp_router &, wampcc::wamp_session &ws, wampcc::call_info info) {
                        ws.result(info.request_id, {"hello"});
                    });

    for (auto const&[service, pidCollection] :  *obdHandler->getPidConfig()) {
        std::string serviceUrl = "get.service." + to_string(service);
        router.callable(REALM, serviceUrl,
                        std::bind(&Wamp::getPidsInService,
                                  this, std::placeholders::_1,
                                  std::placeholders::_2,
                                  std::placeholders::_3,
                                  service));

        for (const auto &pid: pidCollection.get_pid_list_as_vector()) {
            if (pid.name.empty()) { continue; }
            std::string pidUrl = serviceUrl + "." + pid.name;
            router.callable(REALM, pidUrl,
                            std::bind(&Wamp::getPid,
                                      this, std::placeholders::_1,
                                      std::placeholders::_2,
                                      std::placeholders::_3,
                                      service, pid));
        }
    }

    while (!exitRequested) {
        this_thread::sleep_for(100ms);
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
    std::string value;
    vehicleDataProvider->queryVehicle(pid, service);
    vehicleDataProvider->getPrintableDataForPid(service == 2, pid, value);

    wampcc::json_value v = wampcc::json_value::make_array();

    wampcc::json_object &rootObject = v.append_object();

    auto jsonService = wampcc::json_value::make_object();
    jsonService["id"] = service;
    rootObject["service"] = jsonService;

    auto jsonPid = wampcc::json_value::make_object();
    jsonPid["name"] = pid.name;
    jsonPid["id"] = pid.id;
    jsonPid["size"] = pid.size;
    jsonPid["name"] = pid.name;
    jsonPid["description"] = pid.description;
    jsonPid["datafields"] = pid.datafields;
    rootObject["pid"] = jsonPid;

    auto jsonData = wampcc::json_value::make_object();
    jsonData["string"] = value;
    rootObject["data"] = jsonData;

    caller.result(info.request_id, v.as<wampcc::json_array>());
}
