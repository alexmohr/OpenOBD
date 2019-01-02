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
