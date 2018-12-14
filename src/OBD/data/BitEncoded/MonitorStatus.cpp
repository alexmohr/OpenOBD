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

void MonitorStatus::fromFrame(byte *frame) {
    engine->fromFrame(frame);
    mil->setValue(frame);
    dtcCount->setValue(frame);
    components->fromFrame(frame);
    misfire->fromFrame(frame);
    fuelSystem->fromFrame(frame);
}

bool MonitorStatus::getMil() {
    return false;
}

void MonitorStatus::setMil(bool value) {

}

unsigned int MonitorStatus::getDtcCount() {
    return 0;
}

void MonitorStatus::setDtcCount(unsigned int status) {

}

Engine* MonitorStatus::getEngine() {
    return engine;
}
