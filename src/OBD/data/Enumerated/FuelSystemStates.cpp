//
// Created by me on 01/01/19.
//

#include "FuelSystemStates.h"


FuelSystemStates::FuelSystemStates() {
    fuelSystem1 = make_unique<DataObject<StateOfFuelSystem>>(
            A, 7, A, 0, unit_none, StateOfFuelSystemDoesNotExist, ClosedLoopUsingOxygenSensorWithFault,
            DataObjectDescriptionText::getFuelSystemState(1));
    fuelSystem2 = make_unique<DataObject<StateOfFuelSystem>>(
            B, 7, B, 0, unit_none, StateOfFuelSystemDoesNotExist, ClosedLoopUsingOxygenSensorWithFault,
            DataObjectDescriptionText::getFuelSystemState(2));
}

DataObject<StateOfFuelSystem> &FuelSystemStates::getFuelSystem1() {
    return *fuelSystem1;
}

DataObject<StateOfFuelSystem> &FuelSystemStates::getFuelSystem2() {
    return *fuelSystem2;
}

unsigned int FuelSystemStates::toFrame(unsigned int &data, int &size) {
    data = fuelSystem1->toFrame(data, size) |
           fuelSystem2->toFrame(data, size);
    return data;
}

void FuelSystemStates::fromFrame(byte *frame, int size) {
    fuelSystem1->fromFrame(frame, size);
    fuelSystem2->fromFrame(frame, size);
}

shared_ptr<DataObjectValueCollection> FuelSystemStates::getDataObjectValue() {
    auto valueCollection = make_shared<DataObjectValueCollection>();
    valueCollection->merge(fuelSystem1->getDataObjectValue());
    valueCollection->merge(fuelSystem2->getDataObjectValue());
    return valueCollection;
}

DataObjectStateCollection FuelSystemStates::setValueFromString(string data) {
    vector<string> parts;
    auto rs = DataObjectStateFactory::boundCheck(2, data, parts);
    if (rs.resultSet.empty()) {
        DataObjectStateFactory::merge(rs, fuelSystem1->setValueFromString(parts.at(0)));
        DataObjectStateFactory::merge(rs, fuelSystem2->setValueFromString(parts.at(1)));
    } else {
        rs.msg = "Expected 2 values. FuelSystem1, FuelSystem2";
    }

    return rs;
}

vector<DataObjectDescription *> FuelSystemStates::getDescriptions() {
    return vector<DataObjectDescription *>{
            fuelSystem1->getDescriptions().at(0),
            fuelSystem2->getDescriptions().at(0)
    };
}

