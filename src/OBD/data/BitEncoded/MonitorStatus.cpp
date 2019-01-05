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
    return "mil: " + mil->getPrintableData() +
           "\ndtcCount: " + dtcCount->getPrintableData() +
           "\ncomponents: " + components->getPrintableData() +
           "\nmisfire: " + misfire->getPrintableData() +
           "\nfuelSystem: " + fuelSystem->getPrintableData() +
           "\nEngineSystem1: " + engine->getEngineSystem1().getPrintableData() +
           "\nEngineSystem2: " + engine->getEngineSystem2().getPrintableData() +
           "\nEngineSystem3: " + engine->getEngineSystem3().getPrintableData() +
           "\nEngineSystem4: " + engine->getEngineSystem4().getPrintableData() +
           "\nEngineSystem5: " + engine->getEngineSystem5().getPrintableData() +
           "\nEngineSystem6: " + engine->getEngineSystem6().getPrintableData() +
           "\nEngineSystem7: " + engine->getEngineSystem7().getPrintableData() +
           "\nEngineSystem8: " + engine->getEngineSystem8().getPrintableData() +
           "\nEngineType: " + to_string(engine->getEngineType().getValue());
}

int MonitorStatus::setValueFromString(string data) {
    auto parts = splitString(const_cast<char *>(data.c_str()));
    const int paramCount = 24;
    if (paramCount > parts.size()) {
        LOG(ERROR) << "Insufficient parameter count expected " << paramCount << endl <<
                   "\n\tMil:           1" <<
                   "\n\tDtcCount:      1" <<
                   "\n\tComponents:    2 (Available, Incomplete)" <<
                   "\n\tMisfire :      2 (Available, Incomplete)" <<
                   "\n\tFuelSystem:    2 (Available, Incomplete)" <<
                   "\n\tEngineSystem1: 2 (Available, Incomplete)" <<
                   "\n\tEngineSystem2: 2 (Available, Incomplete)" <<
                   "\n\tEngineSystem3: 2 (Available, Incomplete)" <<
                   "\n\tEngineSystem4: 2 (Available, Incomplete)" <<
                   "\n\tEngineSystem5: 2 (Available, Incomplete)" <<
                   "\n\tEngineSystem6: 2 (Available, Incomplete)" <<
                   "\n\tEngineSystem7: 2 (Available, Incomplete)" <<
                   "\n\tEngineSystem8: 2 (Available, Incomplete)" << endl;
        return paramCount;
    }

    int i = 0;
    // todo refactor me please :(
    i += mil->setValueFromString(parts.at(0));
    i += dtcCount->setValueFromString(parts.at(1));
    i += components->setValueFromString(parts.at(2) + " " + parts.at(3));
    i += misfire->setValueFromString(parts.at(4) + " " + parts.at(5));
    i += fuelSystem->setValueFromString(parts.at(6) + " " + parts.at(7));
    i += engine->getEngineSystem1().setValueFromString(parts.at(8) + " " + parts.at(9));
    i += engine->getEngineSystem2().setValueFromString(parts.at(10) + " " + parts.at(11));
    i += engine->getEngineSystem3().setValueFromString(parts.at(12) + " " + parts.at(13));
    i += engine->getEngineSystem4().setValueFromString(parts.at(14) + " " + parts.at(15));
    i += engine->getEngineSystem5().setValueFromString(parts.at(16) + " " + parts.at(17));
    i += engine->getEngineSystem6().setValueFromString(parts.at(18) + " " + parts.at(19));
    i += engine->getEngineSystem7().setValueFromString(parts.at(20) + " " + parts.at(21));
    i += engine->getEngineSystem8().setValueFromString(parts.at(22) + " " + parts.at(23));
    engine->setEngineType(static_cast<EngineType>(strtol(parts.at(24).c_str(), nullptr, 0)));
    return i;
}

vector<DataObjectDescription *> MonitorStatus::getDescriptions() {
    auto descDesc = vector<vector<DataObjectDescription *>>{
            mil->getDescriptions(),
            dtcCount->getDescriptions(),
            components->getDescriptions(),
            misfire->getDescriptions(),
            fuelSystem->getDescriptions(),
            engine->getEngineSystem1().getDescriptions(),
            engine->getEngineSystem2().getDescriptions(),
            engine->getEngineSystem3().getDescriptions(),
            engine->getEngineSystem4().getDescriptions(),
            engine->getEngineSystem5().getDescriptions(),
            engine->getEngineSystem6().getDescriptions(),
            engine->getEngineSystem7().getDescriptions(),
            engine->getEngineSystem8().getDescriptions(),
            engine->getEngineType().getDescriptions()};

    auto desc = vector<DataObjectDescription *>();
    for (const auto &dd : descDesc) {
        for (const auto &d : dd) {
            desc.push_back(d);
        }
    }
    return desc;
}
