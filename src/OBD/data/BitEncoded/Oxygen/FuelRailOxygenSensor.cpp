//
// Created by me on 30/12/18.
//

#include "FuelRailOxygenSensor.h"

FuelRailOxygenSensor::FuelRailOxygenSensor() {
    fuelAirEquivalenceRatio = CalculatedDataObjectFactory::ratio_2Divided2Pow16TimesValue();
    voltage = CalculatedDataObjectFactory::ratio_8Divided2Pow16TimesValue();
}

CalculatedDataObject<unsigned short, float> &FuelRailOxygenSensor::getFuelAirEquivalenceRatio() {
    return *fuelAirEquivalenceRatio;
}

CalculatedDataObject<unsigned short, float> &FuelRailOxygenSensor::getVoltage() {
    return *voltage;
}

unsigned int FuelRailOxygenSensor::toFrame(unsigned int &data, int &size) {
    return data |= fuelAirEquivalenceRatio->toFrame(data, size) |
                   voltage->toFrame(data, size);
}

void FuelRailOxygenSensor::fromFrame(byte *data, int size) {
    fuelAirEquivalenceRatio->fromFrame(data, size);
    voltage->fromFrame(data, size);
}

string FuelRailOxygenSensor::getPrintableData() {
    return "fuelAirEquivalenceRatio: " + fuelAirEquivalenceRatio->getPrintableData() +
           "\nvoltage: " + voltage->getPrintableData();
}

DataObjectStateCollection FuelRailOxygenSensor::setValueFromString(string data) {
    vector<string> parts;
    auto rs = DataObjectStateFactory::boundCheck(2, data, parts);
    if (rs.resultSet.empty()) {
        DataObjectStateFactory::merge(rs, fuelAirEquivalenceRatio->setValueFromString(parts.at(0)));
        DataObjectStateFactory::merge(rs, voltage->setValueFromString(parts.at(1)));
    } else {
        rs.msg = "Expected 2 values. fuelAirEquivalenceRatio, voltage";
    }

    return rs;
}

vector<DataObjectDescription *> FuelRailOxygenSensor::getDescriptions() {
    return vector<DataObjectDescription *>{
            fuelAirEquivalenceRatio->getDescriptions().at(0),
            voltage->getDescriptions().at(0)
    };
}
