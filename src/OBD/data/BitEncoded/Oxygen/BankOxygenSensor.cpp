//
// Created by me on 28/12/18.
//

#include "BankOxygenSensor.h"

BankOxygenSensor::BankOxygenSensor() {
    voltage = CalculatedDataObjectFactory::volt_ADivided200();
    shortTermFuelTrim = CalculatedDataObjectFactory::percent_Percent128Minus100(B);
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

string BankOxygenSensor::getPrintableData() {
    return "voltage: " + voltage->getPrintableData() +
           "\nshortTermFuelTrim: " + shortTermFuelTrim->getPrintableData();
}

