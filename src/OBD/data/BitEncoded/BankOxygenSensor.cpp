//
// Created by me on 28/12/18.
//

#include "BankOxygenSensor.h"

BankOxygenSensor::BankOxygenSensor() {

    auto foo = CalculatedDataObject<byte, float>(
            A, 7, A, 0, CalculatedValues::toADivided200, CalculatedValues::fromADivided200,
            unit_volt, 0.0f, 1.275f, DataObjectDescriptionText::BankOxygenSensorVoltage);

    voltage = make_unique<CalculatedDataObject<byte, float>>(
            A, 7, A, 0, CalculatedValues::toADivided200, CalculatedValues::fromADivided200,
            unit_volt, 0.0f, 1.275f, DataObjectDescriptionText::BankOxygenSensorVoltage);

    shortTermFuelTrim = make_unique<CalculatedDataObject<byte, float>>(
            B, 7, B, 0, CalculatedValues::toPercent128Minus100, CalculatedValues::fromPercent128Minus100,
            unit_percent, 0.0f, 99.2f, DataObjectDescriptionText::BankOxygenSensorShortFuelTrim);
}


bool BankOxygenSensor::isSensorUsedInTrimCalc() {
    return shortTermFuelTrim->getRawValue() != (byte) 0xff;
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

void BankOxygenSensor::fromFrame(byte *data, int size) {
    voltage->fromFrame(data, size);
    shortTermFuelTrim->fromFrame(data, size);
}

