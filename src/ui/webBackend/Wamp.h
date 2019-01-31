//
// Created by me on 27/01/19.
//

#ifndef OPEN_OBD2_WAMP_H
#define OPEN_OBD2_WAMP_H

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
    /* Create the wampcc kernel. */
    wampcc::kernel the_kernel;

public:
    Wamp(shared_ptr<ICommunicationInterface> comInterface,
         shared_ptr<OBDHandler> obdHandler);


public: // Implements ICloseable
    int closeInterface() override;

    int openInterface() override;

private:

    void foo(wampcc::wamp_router &, wampcc::wamp_session &caller, wampcc::call_info info, std::string cmd);
};


#endif //OPEN_OBD2_WAMP_H
