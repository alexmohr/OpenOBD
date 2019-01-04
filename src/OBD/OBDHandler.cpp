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

byte *OBDHandler::createAnswerFrame(byte *request, int &size) {
    // Example request
    // size service pid ....
    // 0x02 0x01 0x00 0x00 0x00 0x00 0x00 0x00

    Service service;
    Pid pid;
    if (getFrameInfo((int) request[1], (int) request[0], pid, service) < 0) {
        LOG(ERROR) << "Received invalid or unsupported pid or service ";
        size = 0;
        return nullptr;
    }

    byte *data = pid.getVehicleData(service, vehicle.get(), size);
    if (nullptr == data) {
        LOG(ERROR) << "Not implemented pid or error";
        return nullptr;
    }
    return createAnswerFrame(service, pid, data, size);
}

byte *OBDHandler::createAnswerFrame(Service service, Pid pid, byte *data, int &size) {
    byte *result = (byte *) malloc(size + 2);

    result[0] = (byte) (service + ANSWER_OFFSET);
    result[1] = (byte) (pid.id);

    memcpy(result + 2, data, static_cast<size_t>(size));
    size = size + 2;
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

    Service service;
    Pid pid;
    if (getFrameInfo((int) frame[1], (int) frame[0] - ANSWER_OFFSET, pid, service) < 0) {
        return;
    }

    const int startByte = 2;
    // 1 byte is service, 1 byte is pid. rest is data
    int dataSize = frameSize -2;
    byte* data = (byte*)malloc(sizeof(byte)*dataSize);
    memcpy(data, frame+startByte, static_cast<size_t>(dataSize));

    Vehicle *updateVehicle = vehicle.get();
    if (FREEZE_FRAME == service) {
        updateVehicle = vehicleFreezeFrame.get();
    }
    pid.updateVehicle(service, updateVehicle, data, dataSize);
    LOG(DEBUG) << "\nUpdated vehicle, PID: " << pid.description;
    delete data;
}

int OBDHandler::getFrameInfo(int pidId, int serviceId, Pid &pid, Service &service) {
    service = static_cast<Service>(serviceId);
    if (pidConfig->find(service) == pidConfig->end()) {
        LOG(WARNING) << "Invalid PID" << to_string(pidId)
                     << " in service " << to_string(serviceId);
        return -1;
    }
    auto pc = pidConfig->at(service);
    pid = pc.pidList.at(pidId);
    return 0;
}


Vehicle * OBDHandler::getVehicle() {
    return vehicle.get();
}

Vehicle *OBDHandler::getVehicleFreezeFrame() {
    return vehicleFreezeFrame.get();
}



