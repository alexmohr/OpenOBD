//
// Created by me on 30/01/19.
//

#include "VehicleDataProvider.h"


VehicleDataProvider::VehicleDataProvider(shared_ptr<OBDHandler> obdHandler,
                                         shared_ptr<ICommunicationInterface> comInterface) {

    this->obdHandler = obdHandler;
    this->comInterface = comInterface;
}

vector<string> VehicleDataProvider::getSupportedPids() const {
    Service service;
    Pid pid;
    vector<string> supportedPids = vector<string>();
    for (const auto &cmdName : COMMAND_MAPPING) {
        if (obdHandler->getServiceAndPidInfo(
                cmdName.second.getPidId(), cmdName.second.getService(), pid, service) != 0) {
            LOG(FATAL) << "Pid with ID " << pid.id << "does only exist in cmdHandler";
            continue;
        }

        if (obdHandler->getVehicle()->getPidSupport().getPidSupported(service, pid.id)) {
            supportedPids.push_back(cmdName.first);
        }
    }
    return supportedPids;
}

bool VehicleDataProvider::configureVehicle() const {
    // query the vehicle which PID's it supports
    vector<Service1Pids> pidIds{
            SupportedPid01_20, SupportedPid21_40, SupportedPid41_60, SupportedPid61_80,
            SupportedPid81_A0, SupportedPidA1_C0, SupportedPidC1_E0,
    };

    auto service = POWERTRAIN;
    bool anyError = false;
    for (const auto &id: pidIds) {
        Pid pid;
        if (obdHandler->getServiceAndPidInfo(id, service, pid, service) < 0) {
            LOG(ERROR) << "failed to get pid information";
        }

        anyError |= queryVehicle(pid, service).type != SUCCESS;
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


