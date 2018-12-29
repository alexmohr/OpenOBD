//
// Created by me on 13/12/18.
//

#include "OBDHandler.h"
#include "easylogging++.h"


OBDHandler::OBDHandler(Vehicle *vehicle, Vehicle *vehicleFreezeFrame,
                       unique_ptr<map<Service, PidCollection>> pidConfig) {
    this->vehicle = vehicle;
    this->vehicleFreezeFrame = vehicleFreezeFrame;
    this->pidConfig = move(pidConfig);

}

byte *OBDHandler::createAnswerFrame(byte *frame) {
    // Example frame
    // size service pid ....
    // 0x02 0x01 0x00 0x00 0x00 0x00 0x00 0x00

    Service service;
    Pid pid;
    getFrameInfo(frame, (int)frame[0], pid, service);


    byte* data = pid.getVehicleData(service, vehicle);
    int dataSize = 0;
    if (data != nullptr) {
        dataSize = (sizeof(data)/2); // todo fix division
    }

    byte* result = (byte*)malloc(dataSize + 2);

    result[0] = (byte)(service + ANSWER_OFFSET);
    result[1] = (byte)(pid.id);

    memcpy(result+2, data, static_cast<size_t>(dataSize));
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
    getFrameInfo(frame, (int)frame[0]-ANSWER_OFFSET, pid, service);

    const int startByte = 2;
    // 1 byte is service, 1 byte is pid. rest is data
    int dataSize = frameSize -2;
    byte* data = (byte*)malloc(sizeof(byte)*dataSize);
    memcpy(data, frame+startByte, static_cast<size_t>(dataSize));

    Vehicle *updateVehicle = vehicle;
    if (FREEZE_FRAME == service) {
        updateVehicle = vehicleFreezeFrame;
    }
    pid.updateVehicle(service, updateVehicle, data, dataSize);
}

void OBDHandler::getFrameInfo(const byte *frame, int serviceId, Pid &pid, Service &service) {
    service = static_cast<Service>(serviceId);
    auto pc = pidConfig->at(service);
    pid = pc.pidList.at((int)frame[1]);
    LOG(DEBUG) << "Creating information for pid " << to_string(pid.id)
               << " in service " << service << " : " << pid.description;
}


Vehicle * OBDHandler::getVehicle() {
    return vehicle;
}
