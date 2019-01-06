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

DataObjectStateCollection BankOxygenSensor::setValueFromString(string data) {
    vector<string> parts;
    auto rs = DataObjectStateFactory::boundCheck(2, data, parts);
    if (rs.resultSet.empty()) {
        DataObjectStateFactory::merge(rs, voltage->setValueFromString(parts.at(0)));
        DataObjectStateFactory::merge(rs, shortTermFuelTrim->setValueFromString(parts.at(1)));
    } else {
        rs.msg = "Expected 2 values. Voltage, ShortTermFuelTrim";
    }
    return rs;
}

vector<DataObjectDescription *> BankOxygenSensor::getDescriptions() {
    return vector<DataObjectDescription *>{voltage->getDescriptions().at(0),
                                           shortTermFuelTrim->getDescriptions().at(0)};
}

