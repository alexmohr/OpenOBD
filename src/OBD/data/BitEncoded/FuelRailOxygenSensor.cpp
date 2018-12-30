//
// Created by me on 30/12/18.
//

#include "FuelRailOxygenSensor.h"

FuelRailOxygenSensor::FuelRailOxygenSensor() {
    fuelAirEquivalenceRatio = make_unique<CalculatedDataObject<unsigned short, float>>(
            A, 7, B, 0,
            CalculatedValues::to2Divided65536Times256PlusB, CalculatedValues::from2Divided65536Times256PlusB,
            unit_ratio, 0.0f, 1.9999f);

    voltage = make_unique<CalculatedDataObject<unsigned short, float>>(
            C, 7, D, 0, CalculatedValues::to8Divided65536Times256PlusB,
            CalculatedValues::from8Divided65536Times256PlusB,
            unit_ratio, 0.0f, 7.9999f);
}

CalculatedDataObject<unsigned short, float> &FuelRailOxygenSensor::getFuelAirEquivalenceRatio() {
    return *fuelAirEquivalenceRatio;
}

CalculatedDataObject<unsigned short, float> &FuelRailOxygenSensor::getVoltage() {
    return *voltage;
}

unsigned int FuelRailOxygenSensor::toFrame(unsigned int &data) {
    return data |= fuelAirEquivalenceRatio->toFrame(data) |
                   voltage->toFrame(data);
}

void FuelRailOxygenSensor::fromFrame(byte *data, int size) {
    fuelAirEquivalenceRatio->fromFrame(data, size);
    voltage->fromFrame(data, size);
}
