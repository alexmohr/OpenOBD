//
// Created by me on 27/01/19.
//

#ifndef OPEN_OBD2_WAMP_H
#define OPEN_OBD2_WAMP_H

#include <thread>
#include "wampcc/wampcc.h"
#include "../../communication/ICloseable.h"
#include "../../communication/ICommunicationInterface.h"
#include "../../OBD/OBDHandler.h"
#include "../VehicleDataProvider.h"


class Wamp : public ICloseable {
public:
    inline static const std::string REALM = "openobd";

private:
    shared_ptr<ICommunicationInterface> comInterface;
    shared_ptr<OBDHandler> obdHandler;
    unique_ptr<VehicleDataProvider> vehicleDataProvider;
private:
    bool exitRequested;
private:
    /* Create the wampcc kernel. */
    wampcc::kernel the_kernel;
    std::thread tServe;

public:
    Wamp(shared_ptr<ICommunicationInterface> comInterface,
         shared_ptr<OBDHandler> obdHandler);


public: // Implements ICloseable
    int closeInterface() override;

    int openInterface() override;

private:

    void serve();

private:

    void getPidsInService(wampcc::wamp_router &, wampcc::wamp_session &caller, wampcc::call_info info, Service service);

    void getPid(wampcc::wamp_router &, wampcc::wamp_session &caller, wampcc::call_info info, Service service, Pid pid);
};


#endif //OPEN_OBD2_WAMP_H
