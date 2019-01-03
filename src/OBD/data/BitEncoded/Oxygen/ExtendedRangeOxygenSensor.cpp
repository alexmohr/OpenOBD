//
// Created by me on 30/12/18.
//

#include "ExtendedRangeOxygenSensor.h"

ExtendedRangeOxygenSensor::ExtendedRangeOxygenSensor() {
    fuelAirEquivalenceRatio = CalculatedDataObjectFactory::ratio_2Divided2Pow16TimesValue();
    current = CalculatedDataObjectFactory::mA_ValueMinus128();
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

unsigned int ExtendedRangeOxygenSensor::toFrame(unsigned int &data, unsigned int &size) {
    data |= fuelAirEquivalenceRatio->toFrame(data, size) |
            current->toFrame(data, size);
    return data;
}

string ExtendedRangeOxygenSensor::getPrintableData() {
    return "fuelAirEquivalenceRatio: " + fuelAirEquivalenceRatio->getPrintableData() +
           "\ncurrent: " + current->getPrintableData();
}

void ExtendedRangeOxygenSensor::setValueFromString(string data) {
    auto parts = splitString(const_cast<char *>(data.c_str()));
    if (2 > parts.size()) {
        LOG(ERROR) << "Insufficient parameter count expected 2";
    }

    fuelAirEquivalenceRatio->setValueFromString(parts.at(0));
    current->setValueFromString(parts.at(1));
}
