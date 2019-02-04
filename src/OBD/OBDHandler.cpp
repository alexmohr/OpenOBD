//
// Created by me on 13/12/18.
//

#include "OBDHandler.h"
#include "easylogging++.h"

OBDHandler::OBDHandler(unique_ptr<map<Service, PidCollection>> pidConfig, map<int, DataTroubleCode> dtcMap) {
    vehicle = make_unique<Vehicle>(make_unique<map<int, DataTroubleCode>>(dtcMap));
    vehicleFreezeFrame = make_unique<Vehicle>(make_unique<map<int, DataTroubleCode>>(dtcMap));

    this->pidConfig = move(pidConfig);
}

shared_ptr<OBDHandler> OBDHandler::createInstance() {
    Config p = Config();

    // todo make paths configurable
    auto pcMap = map<Service, PidCollection>();
    p.parseJson("../configuration/pidConfig.json", pcMap);

    auto dtcMap = map<int, DataTroubleCode>();
    p.parseJson("../configuration/dtcConfig.json", dtcMap);

    return make_shared<OBDHandler>(
            make_unique<map<Service, PidCollection>>(pcMap),
            dtcMap);
}


byte *OBDHandler::createAnswerFrame(byte *request, int &size) {
    // Example request
    // size service pid ....
    // 0x02 0x01 0x00 0x00 0x00 0x00 0x00 0x00

    if (size < 2) {
        byte service = (byte) 0;
        return createErrorFrame(INCORRECT_MESSAGE_LENGTH_OR_FORMAT, size, service);
    }

    Service service;
    Pid pid;
    if (getServiceAndPidInfo((int) request[1], (int) request[0], pid, service) != SUCCESS) {
        return createErrorFrame(SUB_FUNCTION_NOT_SUPPORTED, size, request[1]);
    }

    if (isPidSupported(service, pid.id).type != SUCCESS) {
        return createErrorFrame(SUB_FUNCTION_NOT_SUPPORTED, size, request[1]);
    }

    byte *data = pid.getVehicleData(service, vehicle.get(), size);
    if (nullptr == data) {
        LOG(ERROR) << "Received a request which is not supported or caused an error: " <<
                   "ServiceID: " << service << ", PID: " << pid.id;
        return createErrorFrame(SUB_FUNCTION_NOT_SUPPORTED, size, request[1]);
    }
    byte *answerData = createAnswerFrame(service, pid, data, size);
    delete[] data;
    return answerData;
}

byte *OBDHandler::createAnswerFrame(Service service, Pid pid, byte *data, int &size) {
    byte *result = new byte[size + 2];

    result[0] = (byte) (service + ANSWER_OFFSET);
    result[1] = (byte) (pid.id);

    memcpy(result + 2, data, static_cast<size_t>(size));
    size = size + 2;
    return result;
}

byte *OBDHandler::createErrorFrame(int type, int &size, byte &attemptedFunction) {
    size = 3;
    byte *result = new byte[size];
    result[0] = (byte) NEGATIVE_RESPONSE;
    result[1] = attemptedFunction;
    result[2] = (byte) type;
    return result;
}

void OBDHandler::updateFromFrame(byte *frame, int frameSize) {
    /* example response
     * 0x06 0x41 0x00 0xbe 0x7e 0xb8 0x13 0xaa
     * 0: 0x06 sizeof answer
     * 1: 0x41 service
     * 2: 0x00 pid
     * 3: 0xbe 0x7e 0xb8 0x13 0xaa data
     */

    if (frame[0] == (byte) NEGATIVE_RESPONSE) {
        return;
    }

    Service service;
    Pid pid;
    if (getServiceAndPidInfo((int) frame[1], (int) frame[0] - ANSWER_OFFSET, pid, service) != SUCCESS) {
        return;
    }

    const int startByte = 2;
    // 1 byte is service, 1 byte is pid. rest is data
    int dataSize = frameSize - 2;
    byte *data = new byte[dataSize];
    memcpy(data, frame + startByte, static_cast<size_t>(dataSize));

    Vehicle *updateVehicle = vehicle.get();
    if (FREEZE_FRAME == service) {
        updateVehicle = vehicleFreezeFrame.get();
    }
    pid.updateVehicle(service, updateVehicle, data, dataSize);
    LOG(DEBUG) << "\nUpdated vehicle, PID: " << pid.description;
    delete[] data;
}

ErrorType OBDHandler::getServiceAndPidInfo(int pidId, int serviceId, Pid &pid, Service &service) {
    service = static_cast<Service>(serviceId);
    auto it = pidConfig->find(service);
    if (it == pidConfig->end()) {
        LOG(INFO) << "Not supported service: " << serviceId;
        return NOT_SUPPORTED;
    }

    auto pidCollection = it->second;
    auto pidIt = pidCollection.pidList.find(pidId);
    if (pidIt == pidCollection.pidList.end() || pidIt->second.name.empty()) {
        LOG(INFO) << "Not supported pid " << pidId << " in service " << serviceId;
        return NOT_SUPPORTED;
    }

    pid = pidIt->second;
    return SUCCESS;
}


Vehicle *OBDHandler::getVehicle() {
    return vehicle.get();
}

Vehicle *OBDHandler::getFreezeFrameVehicle() {
    return vehicleFreezeFrame.get();
}


DataObjectState OBDHandler::isPidSupported(Service service, int pid) {
    if (!(vehicle->getPidSupport().getPidSupported(service, pid))) {
        LOG(INFO) << "Requested command is not supported by vehicle, service:" << to_string(service)
                  << ", pid: " << to_string(pid) << endl;
        return DataObjectState(NOT_SUPPORTED);
    }
    return DataObjectState(SUCCESS);
}

map<Service, PidCollection> *OBDHandler::getPidConfig() {
    return this->pidConfig.get();
}






