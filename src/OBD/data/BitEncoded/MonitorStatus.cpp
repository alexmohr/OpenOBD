//
// Created by me on 13/12/18.
//

#include "MonitorStatus.h"

byte *MonitorStatus::toFrame() {
    return nullptr;
}

MonitorStatus::MonitorStatus(Engine *engine) {
    this->engine = engine;

}

void MonitorStatus::fromFrame(byte *frame, int size) {
    dtcCount->setValue(frame, size);

    mil->setValue(frame, size);
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
