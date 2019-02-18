//
// Created by me on 27/01/19.
//

#ifndef OPEN_OBD2_WAMP_H
#define OPEN_OBD2_WAMP_H

#include <thread>
#include <map>
#include <mutex>
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
    APP_TYPE type;

private:
    bool exitRequested;
    bool wampOpen;
    long updateRate = 1000;

private:
    unique_ptr<map<string, pair<Service, Pid>>> subscriptions;
    std::mutex subscriptionMutex;

private:
    /* Create the wampcc kernel. */
    wampcc::kernel the_kernel;
    std::thread tServe;

public:
    Wamp(shared_ptr<ICommunicationInterface> comInterface,
         shared_ptr<OBDHandler> obdHandler,
         APP_TYPE type);


public: // Implements ICloseable
    int closeInterface() override;

    int openInterface() override;

    bool isOpen() override;

public:
    bool isExitRequested();

private:

    void serve();

private: // wamp calls.

    void getPidsInService(wampcc::wamp_router &, wampcc::wamp_session &caller, wampcc::call_info info, Service service);

    void getPid(wampcc::wamp_router &, wampcc::wamp_session &caller, wampcc::call_info info, Service service, Pid pid);

    void subscribeToPid(wampcc::wamp_router &, wampcc::wamp_session &caller, wampcc::call_info info, Service service,
                        Pid pid, string key);

    void
    unsubscribeFromPid(wampcc::wamp_router &, wampcc::wamp_session &caller, wampcc::call_info info, string key);

    void clearPidSubscriptions(wampcc::wamp_router &, wampcc::wamp_session &caller, wampcc::call_info info);

    void setUpdateRate(wampcc::wamp_router &, wampcc::wamp_session &caller, wampcc::call_info info);

private:
    template<typename T>
    void addVectorToJsonObject(wampcc::json_value &obj, string name, vector<T> vec) const;

    wampcc::json_value getPidData(const Service &service, const Pid &pid) const;
};


#endif //OPEN_OBD2_WAMP_H
