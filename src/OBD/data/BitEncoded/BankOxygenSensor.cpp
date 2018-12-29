//
// Created by me on 28/12/18.
//

#include "BankOxygenSensor.h"

BankOxygenSensor::BankOxygenSensor() {

    voltage = make_unique<CalculatedDataObject<byte, float>>(
            A, 7, A, 0, CalculatedValues::toADivided200, CalculatedValues::fromADivided200);

    shortTermFuelTrim = make_unique<CalculatedDataObject<byte, float>>(
            B, 7, B, 0, CalculatedValues::toPercent128Minus100, CalculatedValues::fromPercent128Minus100);
}


bool BankOxygenSensor::isSensorUsedInTrimCalc() {
    return shortTermFuelTrim->getValue() == 0xff;
}

CalculatedDataObject<byte, float> &BankOxygenSensor::getVoltage() {
    return *voltage;
}

CalculatedDataObject<byte, float> &BankOxygenSensor::getShortTermFuelTrim() {
    return *shortTermFuelTrim;
}

unsigned int BankOxygenSensor::toFrame(unsigned int &data) {
    data |= voltage->toFrame(data);
    data |= shortTermFuelTrim->toFrame(data);
    return data;
}

unsigned int BankOxygenSensor::fromFrame(byte *data, int size) {
    return 0;
}
