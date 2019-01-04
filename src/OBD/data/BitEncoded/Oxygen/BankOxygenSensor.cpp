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

unsigned int BankOxygenSensor::toFrame(unsigned int &data, int &size) {
    data |= voltage->toFrame(data, size);
    data |= shortTermFuelTrim->toFrame(data, size);
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

void BankOxygenSensor::setValueFromString(string data) {
    auto parts = splitString(const_cast<char *>(data.c_str()));
    if (2 > parts.size()) {
        LOG(ERROR) << "Insufficient parameter count expected 2";
    }

    voltage->setValueFromString(parts.at(0));
    shortTermFuelTrim->setValueFromString(parts.at(1));
}

