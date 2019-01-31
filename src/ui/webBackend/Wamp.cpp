//
// Created by me on 27/01/19.
//

#include "Wamp.h"
#include <functional>

Wamp::Wamp(shared_ptr<ICommunicationInterface> comInterface, shared_ptr<OBDHandler> obdHandler) {
    this->comInterface = comInterface;
    this->obdHandler = obdHandler;
    this->vehicleDataProvider = make_unique<VehicleDataProvider>(obdHandler, comInterface);
}

void Wamp::foo(wampcc::wamp_router &, wampcc::wamp_session &caller, wampcc::call_info info, std::string cmd) {

}

int Wamp::openInterface() {
    /* Create an embedded wamp router. */
    wampcc::wamp_router router(&the_kernel);

    /* Accept clients on IPv4 port, without authentication. */
    auto fut = router.listen(wampcc::auth_provider::no_auth_required(), 55555);
    if (auto ec = fut.get()) {
        LOG(ERROR) << "Failed WAMP start" << ec.message();
        return 1;
    }

    auto supportedPids = vehicleDataProvider->getSupportedPids();
    for (const auto &supportedPid : supportedPids) {
        router.callable(REALM, "get_" + supportedPid,
                        std::bind(&Wamp::foo,
                                  this, std::placeholders::_1,
                                  std::placeholders::_2,
                                  std::placeholders::_3,
                                  "get " + supportedPid

                        ));
    }

/*
    [](wampcc::wamp_router &, wampcc::wamp_session &caller, wampcc::call_info info) {
        vehicleDataProvider->getSupportedPids();

        caller.result(info.request_id, {"hello"});
    });*/
}

int Wamp::closeInterface() {
    return 0;
}
