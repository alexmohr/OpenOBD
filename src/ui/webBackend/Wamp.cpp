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

    /* Create an embedded wamp router. */
    wampcc::wamp_router router(&the_kernel);

    /* Accept clients on IPv4 port, without authentication. */
    auto lstFut = router.listen(wampcc::auth_provider::no_auth_required(), 55555);
    if (auto ec = lstFut.get()) {
        LOG(ERROR) << "Failed WAMP start" << ec.message();
        return;
    }

    auto supportedPids = vehicleDataProvider->getSupportedPids();
    for (const auto &pid : supportedPids) {
        router.callable(REALM, "get/service/1/supportedPids/" + pid.second.name,
                        std::bind(&Wamp::getPid,
                                  this, std::placeholders::_1,
                                  std::placeholders::_2,
                                  std::placeholders::_3,
                                  pid.second, pid.first
                        ));
    }

    router.callable(REALM, "get/service/1/supportedPids/",
                    std::bind(&Wamp::getSupportedPids,
                              this, std::placeholders::_1,
                              std::placeholders::_2,
                              std::placeholders::_3
                    ));

    while (!exitRequested) {
        this_thread::sleep_for(100ms);
    }
}

void Wamp::getSupportedPids(wampcc::wamp_router &, wampcc::wamp_session &caller, wampcc::call_info info) {
    auto data = wampcc::json_array();

    auto supportedPids = vehicleDataProvider->getSupportedPids();
//    for (const auto &pid : supportedPids) {
////        data.emplace_back(pid);
////todo
//    }

//    caller.result(info.request_id, data);
}


void Wamp::getPid(wampcc::wamp_router &, wampcc::wamp_session &caller, wampcc::call_info info, Pid pid,
                  Service service) {
    auto data = wampcc::json_array();
//    vehicleDataProvider->
//            vehicleDataProvider->queryVehicle(Pid
//    pid, Service
//    service)
    //data.emplace_back()
}