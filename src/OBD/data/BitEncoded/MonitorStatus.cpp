#include <utility>

//
// Created by me on 13/12/18.
//

#include "MonitorStatus.h"


MonitorStatus::MonitorStatus(shared_ptr<Engine> *engine) {
    this->engine = *engine;

    mil = make_unique<DataObject<bool>>(A, 7, DataObjectDescriptionText::getMonitorStatusMIL());

    dtcCount = make_unique<DataObject<unsigned short>>(A, 6, A, 0, unit_none, 0, 128,
                                                       DataObjectDescriptionText::getMonitorStatusDTC());

    components = make_unique<OBDTest>(DataObjectDescriptionText::getComponents(), B, 2, B, 6);
    fuelSystem = make_unique<OBDTest>(DataObjectDescriptionText::getFuelSystem(), B, 1, B, 5);
    misfire = make_unique<OBDTest>(DataObjectDescriptionText::getMisfire(), B, 0, B, 4);

}


unsigned int MonitorStatus::toFrame(unsigned int &data, int &size) {

    data = mil->toFrame(data, size);
    data |= dtcCount->toFrame(data, size);
    data |= components->toFrame(data, size);
    data |= misfire->toFrame(data, size);
    data |= fuelSystem->toFrame(data, size);
    data |= engine->toFrameForMonitoringSystem(data, size);
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

shared_ptr<DataObjectValueCollection> MonitorStatus::getDataObjectValue() {
    auto valueCollection = make_shared<DataObjectValueCollection>();
    valueCollection->merge(mil->getDataObjectValue());
    valueCollection->merge(dtcCount->getDataObjectValue());
    valueCollection->merge(components->getDataObjectValue());
    valueCollection->merge(misfire->getDataObjectValue());
    valueCollection->merge(fuelSystem->getDataObjectValue());
    valueCollection->merge(engine->getEngineSystem1().getDataObjectValue());
    valueCollection->merge(engine->getEngineSystem2().getDataObjectValue());
    valueCollection->merge(engine->getEngineSystem3().getDataObjectValue());
    valueCollection->merge(engine->getEngineSystem4().getDataObjectValue());
    valueCollection->merge(engine->getEngineSystem5().getDataObjectValue());
    valueCollection->merge(engine->getEngineSystem6().getDataObjectValue());
    valueCollection->merge(engine->getEngineSystem7().getDataObjectValue());
    valueCollection->merge(engine->getEngineSystem8().getDataObjectValue());
    valueCollection->merge(engine->getEngineType().getDataObjectValue());
    return valueCollection;
}

DataObjectStateCollection MonitorStatus::setValueFromString(string data) {
    vector<string> parts;
    auto rs = DataObjectStateFactory::boundCheck(25, data, parts);
    if (!rs.resultSet.empty()) {
        rs.msg = "\n\tMil:           1"
                 "\n\tDtcCount:      1"
                 "\n\tComponents:    2 (Available, Incomplete)"
                 "\n\tMisfire :      2 (Available, Incomplete)"
                 "\n\tFuelSystem:    2 (Available, Incomplete)"
                 "\n\tEngineSystem1: 2 (Available, Incomplete)"
                 "\n\tEngineSystem2: 2 (Available, Incomplete)"
                 "\n\tEngineSystem3: 2 (Available, Incomplete)"
                 "\n\tEngineSystem4: 2 (Available, Incomplete)"
                 "\n\tEngineSystem5: 2 (Available, Incomplete)"
                 "\n\tEngineSystem6: 2 (Available, Incomplete)"
                 "\n\tEngineSystem7: 2 (Available, Incomplete)"
                 "\n\tEngineSystem8: 2 (Available, Incomplete)\n";
        return rs;
    }

    // todo refactor me please :(
    DataObjectStateFactory::merge(rs, mil->setValueFromString(parts.at(0)));
    DataObjectStateFactory::merge(rs, dtcCount->setValueFromString(parts.at(1)));
    DataObjectStateFactory::merge(rs, components->setValueFromString(parts.at(2) + " " + parts.at(3)));
    DataObjectStateFactory::merge(rs, misfire->setValueFromString(parts.at(4) + " " + parts.at(5)));
    DataObjectStateFactory::merge(rs, fuelSystem->setValueFromString(parts.at(6) + " " + parts.at(7)));
    DataObjectStateFactory::merge(rs, engine->getEngineSystem1().setValueFromString(parts.at(8) + " " + parts.at(9)));
    DataObjectStateFactory::merge(rs, engine->getEngineSystem2().setValueFromString(parts.at(10) + " " + parts.at(11)));
    DataObjectStateFactory::merge(rs, engine->getEngineSystem3().setValueFromString(parts.at(12) + " " + parts.at(13)));
    DataObjectStateFactory::merge(rs, engine->getEngineSystem4().setValueFromString(parts.at(14) + " " + parts.at(15)));
    DataObjectStateFactory::merge(rs, engine->getEngineSystem5().setValueFromString(parts.at(16) + " " + parts.at(17)));
    DataObjectStateFactory::merge(rs, engine->getEngineSystem6().setValueFromString(parts.at(18) + " " + parts.at(19)));
    DataObjectStateFactory::merge(rs, engine->getEngineSystem7().setValueFromString(parts.at(20) + " " + parts.at(21)));
    DataObjectStateFactory::merge(rs, engine->getEngineSystem8().setValueFromString(parts.at(22) + " " + parts.at(23)));

    engine->setEngineType(static_cast<EngineType>(strtol(parts.at(24).c_str(), nullptr, 0)));
    rs.resultSet.push_back(DataObjectState()); // todo for engine. Always success. ... Needs to be changed
    return rs;
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
