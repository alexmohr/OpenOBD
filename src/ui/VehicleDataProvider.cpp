//
// Created by me on 30/01/19.
//

#include "VehicleDataProvider.h"


VehicleDataProvider::VehicleDataProvider(shared_ptr<OBDHandler> obdHandler,
                                         shared_ptr<ICommunicationInterface> comInterface) {

    this->obdHandler = obdHandler;
    this->comInterface = comInterface;
}

bool VehicleDataProvider::configureVehicle() const {
    // query the vehicle which PID's it supports
    Pid pidObj;
    Service serviceObj;
    DataObjectState state;

    bool anyError = false;
    for (auto &service: services) {
        for (const auto &id: pidIds) {
            if (obdHandler->getServiceAndPidInfo(id, service, pidObj, serviceObj) != SUCCESS) {
                continue;
            }

            if (!pidObj.name.empty()) {
                state = queryVehicle(pidObj, serviceObj);
                anyError |= state.type != (SUCCESS) && state.type != (NOT_SUPPORTED);
            }
        }
    }

    return anyError;
}

DataObjectState VehicleDataProvider::queryVehicle(Pid pid, Service service) const {
    if (obdHandler->isPidSupported(service, pid.id).type != SUCCESS) {
        return NOT_SUPPORTED;
    }

    const int maxTries = 3;
    int tries = 0;
    int frameLen = 0;
    auto retVal = DataObjectState(SUCCESS);
    auto timeout = 500ms;
    const string timeoutWarning = "Failed to retrieve pid " + to_string(pid.id)
                                  + " in service " + to_string(service) + " in " + to_string(maxTries) + " tries";

    byte *frame = pid.getQueryForService(service, frameLen);
    int bufSize = 255;
    byte *buf = new byte[bufSize];
    int readSize = 0;
    bool success = false;

    do {
        comInterface->send(frame, frameLen);
        bool hasTimeout = false;
        auto t0 = chrono::high_resolution_clock::now();
        while (readSize <= 0 && !hasTimeout) {
            comInterface->receive(buf, bufSize, readSize);
            hasTimeout = (chrono::high_resolution_clock::now() - t0) > timeout;
        }

        if (hasTimeout || readSize < 1) {
            continue;
        }

        obdHandler->updateFromFrame(buf, readSize);
        success = true;
    } while (!success && tries++ < maxTries);


    if (!success) {
        LOG(WARNING) << timeoutWarning;
        retVal = DataObjectState(TIMEOUT);
    }

    delete[] frame;
    delete[] buf;
    return retVal;
}


bool VehicleDataProvider::getPid(const string &pidName, Pid &pid, Service &service) const {
    if (pidName.empty()) {
        return false;
    }

    bool foundPid = false;
    for (auto const&[serviceObj, pidCollection] :  *obdHandler->getPidConfig()) {
        for (const auto &pidObj: pidCollection.get_pid_list_as_vector()) {
            if (pidName == pidObj.name) {
                pid = pidObj;
                service = serviceObj;
                foundPid = true;
                break;
            }
        }

        if (foundPid) {
            break;
        }
    }

    if (!foundPid) {
        return false;
    }

    return obdHandler->getServiceAndPidInfo(pid.id, service, pid, service) == SUCCESS;
}


DataObjectState VehicleDataProvider::getPrintableDataForPid(bool freezeFrameVehicle, const Pid &pid,
                                                            shared_ptr<DataObjectValueCollection> &value) const {
    IFrameObject *frameObject;
    if (freezeFrameVehicle) {
        frameObject = pid.getFrameObject(obdHandler->getFreezeFrameVehicle());
    } else {
        frameObject = pid.getFrameObject(obdHandler->getVehicle());
    }

    if (frameObject == nullptr) {
        return DataObjectState(NOT_SUPPORTED);
    }
    value = frameObject->getDataObjectValue();
    return DataObjectState(SUCCESS);
}



