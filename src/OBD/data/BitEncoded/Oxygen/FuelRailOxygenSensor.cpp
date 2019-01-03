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

unsigned int FuelRailOxygenSensor::toFrame(unsigned int &data, unsigned int &size) {
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

void FuelRailOxygenSensor::setValueFromString(string data) {
    auto parts = splitString(const_cast<char *>(data.c_str()));
    if (2 > parts.size()) {
        LOG(ERROR) << "Insufficient parameter count expected 2";
    }

    fuelAirEquivalenceRatio->setValueFromString(parts.at(0));
    voltage->setValueFromString(parts.at(1));
}
