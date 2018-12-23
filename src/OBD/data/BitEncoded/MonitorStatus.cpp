//
// Created by me on 13/12/18.
//

#include "MonitorStatus.h"

unsigned int MonitorStatus::toFrame() {
    unsigned int data = 0;

    data = mil->toFrame(data);
    data |= dtcCount->toFrame(data);
    data |= components->toFrame(data);
    data |= misfire->toFrame(data);
    data |= fuelSystem->toFrame(data);
    data |= engine->toFrameForMonitoringSystem(data);
    return data;
}

MonitorStatus::MonitorStatus(shared_ptr<Engine> engine) {
    this->engine = engine;

}

void MonitorStatus::fromFrame(byte *frame, int size) {
    mil->fromFrame(frame, size);
    dtcCount->fromFrame(frame, size);

    engine->fromFrameForMonitoringSystem(frame, size);

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

Engine &MonitorStatus::getEngine() {
    return *engine;
}

OBDTest &MonitorStatus::getComponents() {
    return *components;
}

OBDTest &MonitorStatus::getFuelSystem() {
    return *fuelSystem;
}

OBDTest &MonitorStatus::getMisfire() {
    return *misfire;
}
