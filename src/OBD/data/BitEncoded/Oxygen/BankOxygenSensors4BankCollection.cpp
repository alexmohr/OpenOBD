//
// Created by me on 01/01/19.
//

#include "BankOxygenSensors4BankCollection.h"


BankOxygenSensors4BankCollection::BankOxygenSensors4BankCollection() {

    bank1Sensor1presentIn4Banks =
            make_unique<DataObject<bool>>(A, 0, DataObjectDescriptionText::getBankSensorPresentIn4Banks(1, 1));
    bank1Sensor2presentIn4Banks =
            make_unique<DataObject<bool>>(A, 1, DataObjectDescriptionText::getBankSensorPresentIn4Banks(1, 2));
    bank2Sensor1presentIn4Banks =
            make_unique<DataObject<bool>>(A, 2, DataObjectDescriptionText::getBankSensorPresentIn4Banks(2, 1));
    bank2Sensor2presentIn4Banks =
            make_unique<DataObject<bool>>(A, 3, DataObjectDescriptionText::getBankSensorPresentIn4Banks(2, 2));
    bank3Sensor1presentIn4Banks =
            make_unique<DataObject<bool>>(A, 4, DataObjectDescriptionText::getBankSensorPresentIn4Banks(3, 1));
    bank3Sensor2presentIn4Banks =
            make_unique<DataObject<bool>>(A, 5, DataObjectDescriptionText::getBankSensorPresentIn4Banks(3, 2));
    bank4Sensor1presentIn4Banks =
            make_unique<DataObject<bool>>(A, 6, DataObjectDescriptionText::getBankSensorPresentIn4Banks(4, 1));
    bank4Sensor2presentIn4Banks =
            make_unique<DataObject<bool>>(A, 7, DataObjectDescriptionText::getBankSensorPresentIn4Banks(4, 2));

    allSensors = vector<DataObject<bool> *>();
    allSensors.push_back(bank1Sensor1presentIn4Banks.get());
    allSensors.push_back(bank1Sensor2presentIn4Banks.get());
    allSensors.push_back(bank2Sensor1presentIn4Banks.get());
    allSensors.push_back(bank2Sensor2presentIn4Banks.get());
    allSensors.push_back(bank3Sensor1presentIn4Banks.get());
    allSensors.push_back(bank3Sensor2presentIn4Banks.get());
    allSensors.push_back(bank4Sensor1presentIn4Banks.get());
    allSensors.push_back(bank4Sensor2presentIn4Banks.get());
}


DataObject<bool> &BankOxygenSensors4BankCollection::getBank1Sensor1presentIn4Banks() {
    return *bank1Sensor1presentIn4Banks;
}

DataObject<bool> &BankOxygenSensors4BankCollection::getBank1Sensor2presentIn4Banks() {
    return *bank1Sensor2presentIn4Banks;
}

DataObject<bool> &BankOxygenSensors4BankCollection::getBank2Sensor1presentIn4Banks() {
    return *bank2Sensor1presentIn4Banks;
}

DataObject<bool> &BankOxygenSensors4BankCollection::getBank2Sensor2presentIn4Banks() {
    return *bank2Sensor2presentIn4Banks;
}

DataObject<bool> &BankOxygenSensors4BankCollection::getBank3Sensor1presentIn4Banks() {
    return *bank3Sensor1presentIn4Banks;
}

DataObject<bool> &BankOxygenSensors4BankCollection::getBank3Sensor2presentIn4Banks() {
    return *bank3Sensor2presentIn4Banks;
}

DataObject<bool> &BankOxygenSensors4BankCollection::getBank4Sensor1presentIn4Banks() {
    return *bank4Sensor1presentIn4Banks;
}

DataObject<bool> &BankOxygenSensors4BankCollection::getBank4Sensor2presentIn4Banks() {
    return *bank4Sensor2presentIn4Banks;
}


void BankOxygenSensors4BankCollection::fromFrame(byte *frame, int size) {
    for (const auto &sensor: allSensors) {
        sensor->fromFrame(frame, size);
    }
}

unsigned int BankOxygenSensors4BankCollection::toFrame(unsigned int &data, int &size) {
    for (const auto &sensor: allSensors) {
        data |= sensor->toFrame(data, size);
    }

    return data;
}

shared_ptr<DataObjectValueCollection> BankOxygenSensors4BankCollection::getDataObjectValue() {
    auto valueCollection = make_shared<DataObjectValueCollection>();

    valueCollection->merge(bank1Sensor1presentIn4Banks->getDataObjectValue());
    valueCollection->merge(bank1Sensor2presentIn4Banks->getDataObjectValue());
    valueCollection->merge(bank2Sensor1presentIn4Banks->getDataObjectValue());
    valueCollection->merge(bank2Sensor2presentIn4Banks->getDataObjectValue());
    valueCollection->merge(bank3Sensor1presentIn4Banks->getDataObjectValue());
    valueCollection->merge(bank3Sensor2presentIn4Banks->getDataObjectValue());
    valueCollection->merge(bank4Sensor1presentIn4Banks->getDataObjectValue());
    valueCollection->merge(bank4Sensor2presentIn4Banks->getDataObjectValue());

    return valueCollection;
}

DataObjectStateCollection BankOxygenSensors4BankCollection::setValueFromString(string data) {
    vector<string> parts;
    auto rs = DataObjectStateFactory::boundCheck(8, data, parts);
    if (!rs.resultSet.empty()) {
        return rs;
    }

    int i;
    for (i = 0; i < (int) allSensors.size(); i++) {
        DataObjectStateFactory::merge(rs, allSensors.at(i)->setValueFromString(parts.at(i)));
    }

    return rs;
}

vector<DataObjectDescription *> BankOxygenSensors4BankCollection::getDescriptions() {
    vector<DataObjectDescription *> desc;
    for (const auto &sensor: allSensors) {
        auto sdesc = sensor->getDescriptions();
        desc.insert(desc.end(), sdesc.begin(), sdesc.end());
    }

    return desc;
}
