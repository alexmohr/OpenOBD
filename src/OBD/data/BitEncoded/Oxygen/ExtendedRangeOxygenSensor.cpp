//
// Created by me on 30/12/18.
//

#include "ExtendedRangeOxygenSensor.h"

ExtendedRangeOxygenSensor::ExtendedRangeOxygenSensor() {
    fuelAirEquivalenceRatio = make_unique<CalculatedDataObject<unsigned short, float>>(
            A, 7, B, 0,

            CalculatedValues::to2Divided65536Times256PlusB, CalculatedValues::from2Divided65536Times256PlusB,
            unit_ratio, 0, 1.9999f);

    current = make_unique<CalculatedDataObject<unsigned short, float>>(
            C, 7, D, 0,
            CalculatedValues::toAPlusBDivided256Minus128, CalculatedValues::fromAPlusBDivided256Minus128,
            unit_mA, -128.0f, 127.9999f);
}

CalculatedDataObject<unsigned short, float> &ExtendedRangeOxygenSensor::getFuelAirEquivalenceRatio() {
    return *fuelAirEquivalenceRatio;
}

CalculatedDataObject<unsigned short, float> &ExtendedRangeOxygenSensor::getCurrent() {
    return *current;
}

void ExtendedRangeOxygenSensor::fromFrame(byte *frame, int size) {
    fuelAirEquivalenceRatio->fromFrame(frame, size);
    current->fromFrame(frame, size);
}

unsigned int ExtendedRangeOxygenSensor::toFrame(unsigned int &data) {
    data |= fuelAirEquivalenceRatio->toFrame(data) |
            current->toFrame(data);
    return data;
}
