//
// Created by me on 13/12/18.
//

#include "MonitorStatus.h"

byte *MonitorStatus::toFrame() {
    unsigned int data = 0;

    data = mil->toFrame(data) |
           dtcCount->toFrame(data) |
           components->toFrame(data) |
           misfire->toFrame(data) |
           fuelSystem->toFrame(data) |
           engine->toFrame(data);

    byte *retVal = new byte[4];
    retVal[0] = (byte) (data & 0xFF);
    retVal[1] = (byte) ((data >> 8) & 0xFF);
    retVal[2] = (byte) ((data >> 16) & 0xFF);
    retVal[3] = (byte) ((data >> 24) & 0xFF);
    return retVal;
}

MonitorStatus::MonitorStatus(Engine *engine) {
    this->engine = engine;

}

void MonitorStatus::fromFrame(byte *frame, int size) {
    mil->fromFrame(frame, size);
    dtcCount->fromFrame(frame, size);

    engine->fromFrame(frame, size);

    components->fromFrame(frame, size);
    misfire->fromFrame(frame, size);
    fuelSystem->fromFrame(frame, size);
}


bool MonitorStatus::getMil() {
    return mil->getValue();
}

void MonitorStatus::setMil(bool value) {
    mil->setValue(value);
}

unsigned int MonitorStatus::getDtcCount() {
    return dtcCount->getValue();
}

void MonitorStatus::setDtcCount(unsigned int count) {
    dtcCount->setValue(count);
}

Engine* MonitorStatus::getEngine() {
    return engine;
}

OBDTest *MonitorStatus::getComponents() {
    return components;
}

OBDTest *MonitorStatus::getFuelSystem() {
    return fuelSystem;
}

OBDTest *MonitorStatus::getMisfire() {
    return misfire;
}
