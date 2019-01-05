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

unsigned int ExtendedRangeOxygenSensor::toFrame(unsigned int &data, int &size) {
    data |= fuelAirEquivalenceRatio->toFrame(data, size) |
            current->toFrame(data, size);
    return data;
}

string ExtendedRangeOxygenSensor::getPrintableData() {
    return "fuelAirEquivalenceRatio: " + fuelAirEquivalenceRatio->getPrintableData() +
           "\ncurrent: " + current->getPrintableData();
}

int ExtendedRangeOxygenSensor::setValueFromString(string data) {
    auto parts = splitString(const_cast<char *>(data.c_str()));
    const int paramCount = 2;
    if (paramCount > parts.size()) {
        LOG(ERROR) << "Insufficient parameter count expected " << paramCount;
        return paramCount;
    }

    fuelAirEquivalenceRatio->setValueFromString(parts.at(0));
    current->setValueFromString(parts.at(1));
    return 0;
}

vector<DataObjectDescription *> ExtendedRangeOxygenSensor::getDescriptions() {
    return vector<DataObjectDescription *>{
            fuelAirEquivalenceRatio->getDescriptions().at(0),
            current->getDescriptions().at(0)};
}
