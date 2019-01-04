#include <utility>

//
// Created by me on 13/12/18.
//

#include "MonitorStatus.h"


MonitorStatus::MonitorStatus(shared_ptr<Engine> *engine) {
    this->engine = *engine;

    mil = make_unique<DataObject<bool>>(A, 7, DataObjectDescriptionText::MonitorStatusMIL);

    dtcCount = make_unique<DataObject<unsigned short>>(A, 6, A, 0, unit_none, 0, 128,
                                                       DataObjectDescriptionText::MonitorStatusDTC);

    components = make_unique<OBDTest>("Components", B, 2, B, 6);
    fuelSystem = make_unique<OBDTest>("FuelSystem", B, 1, B, 5);
    misfire = make_unique<OBDTest>("Misfire", B, 0, B, 4);

}


unsigned int MonitorStatus::toFrame(unsigned int &data, int &size) {

    data = mil->toFrame(data, size);
    data |= dtcCount->toFrame(data, size);
    data |= components->toFrame(data, size);
    data |= misfire->toFrame(data, size);
    data |= fuelSystem->toFrame(data, size);
    data |= engine->toFrameForMonitoringSystem(data, size);
    size = 32; // this size is in bits
    return data;
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

string MonitorStatus::getPrintableData() {
    return "mil" + mil->getPrintableData() +
           "\ndtcCount" + dtcCount->getPrintableData() +
           "\ncomponents" + components->getPrintableData() +
           "\nmisfire" + misfire->getPrintableData() +
           "\nfuelSystem" + fuelSystem->getPrintableData() +
           "\nEngineSystem1" + engine->getEngineSystem1().getPrintableData() +
           "\nEngineSystem2" + engine->getEngineSystem2().getPrintableData() +
           "\nEngineSystem3" + engine->getEngineSystem3().getPrintableData() +
           "\nEngineSystem4" + engine->getEngineSystem4().getPrintableData() +
           "\nEngineSystem5" + engine->getEngineSystem5().getPrintableData() +
           "\nEngineSystem6" + engine->getEngineSystem6().getPrintableData() +
           "\nEngineSystem7" + engine->getEngineSystem7().getPrintableData() +
           "\nEngineSystem8" + engine->getEngineSystem8().getPrintableData() +
           "\nEngineType" + to_string(engine->getEngineType());
}

void MonitorStatus::setValueFromString(string data) {
    auto parts = splitString(const_cast<char *>(data.c_str()));
    if (14 > parts.size()) {
        LOG(ERROR) << "Insufficient parameter count expected 14"
                   << "\nMil, DtcCount, Misfire, Fuelsystem"
                   << "\nEngineSystem1..8 EngineType" << endl;
    }


    mil->setValueFromString(parts.at(0));
    dtcCount->setValueFromString(parts.at(1));
    components->setValueFromString(parts.at(2));
    misfire->setValueFromString(parts.at(3));
    fuelSystem->setValueFromString(parts.at(4));
    engine->getEngineSystem1().setValueFromString(parts.at(5));
    engine->getEngineSystem2().setValueFromString(parts.at(6));
    engine->getEngineSystem3().setValueFromString(parts.at(7));
    engine->getEngineSystem4().setValueFromString(parts.at(8));
    engine->getEngineSystem5().setValueFromString(parts.at(9));
    engine->getEngineSystem6().setValueFromString(parts.at(10));
    engine->getEngineSystem7().setValueFromString(parts.at(11));
    engine->getEngineSystem8().setValueFromString(parts.at(12));
    engine->setEngineType(static_cast<EngineType>(strtol(parts.at(13).c_str(), nullptr, 0)));
}