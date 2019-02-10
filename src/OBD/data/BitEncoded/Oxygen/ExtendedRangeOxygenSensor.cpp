//
// Created by me on 30/12/18.
//

#include "ExtendedRangeOxygenSensor.h"

ExtendedRangeOxygenSensor::ExtendedRangeOxygenSensor() {
    fuelAirEquivalenceRatio = CalculatedDataObjectFactory::ratio_2Divided2Pow16TimesValue(
            DataObjectDescriptionText::getFuelAirEquivalenceRatio());
    current = CalculatedDataObjectFactory::mA_ValueMinus128(
            DataObjectDescriptionText::getCurrent());
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

shared_ptr<DataObjectValueCollection> ExtendedRangeOxygenSensor::getDataObjectValue() {
    auto valueCollection = make_shared<DataObjectValueCollection>();
    valueCollection->merge(fuelAirEquivalenceRatio->getDataObjectValue());
    valueCollection->merge(current->getDataObjectValue());
    return valueCollection;
}

DataObjectStateCollection ExtendedRangeOxygenSensor::setValueFromString(string data) {
    vector<string> parts;
    auto rs = DataObjectStateFactory::boundCheck(2, data, parts);
    if (rs.resultSet.empty()) {
        DataObjectStateFactory::merge(rs, fuelAirEquivalenceRatio->setValueFromString(data));
        DataObjectStateFactory::merge(rs, current->setValueFromString(data));
    } else {
        rs.msg = "Expected 2 values. fuelAirEquivalenceRatio, current";
    }

    return rs;
}

vector<DataObjectDescription *> ExtendedRangeOxygenSensor::getDescriptions() {
    return vector<DataObjectDescription *>{
            fuelAirEquivalenceRatio->getDescriptions().at(0),
            current->getDescriptions().at(0)};
}
