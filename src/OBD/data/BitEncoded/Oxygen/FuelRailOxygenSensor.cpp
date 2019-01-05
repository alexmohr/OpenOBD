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

unsigned int FuelRailOxygenSensor::toFrame(unsigned int &data, int &size) {
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

int FuelRailOxygenSensor::setValueFromString(string data) {
    auto parts = splitString(const_cast<char *>(data.c_str()));
    const int paramCount = 2;
    if (paramCount > parts.size()) {
        LOG(ERROR) << "Insufficient parameter count expected " << paramCount;
        return paramCount;
    }

    fuelAirEquivalenceRatio->setValueFromString(parts.at(0));
    voltage->setValueFromString(parts.at(1));

    return 0;
}

vector<DataObjectDescription *> FuelRailOxygenSensor::getDescriptions() {
    return vector<DataObjectDescription *>{
            fuelAirEquivalenceRatio->getDescriptions().at(0),
            voltage->getDescriptions().at(0)
    };
}
