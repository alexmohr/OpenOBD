//
// Created by me on 01/01/19.
//

#include "BankOxygenSensors4BankCollection.h"


BankOxygenSensors4BankCollection::BankOxygenSensors4BankCollection() {

    bank1Sensor1presentIn4Banks = make_unique<DataObject<bool>>(A, 0);
    bank1Sensor2presentIn4Banks = make_unique<DataObject<bool>>(A, 1);
    bank2Sensor1presentIn4Banks = make_unique<DataObject<bool>>(A, 2);
    bank2Sensor2presentIn4Banks = make_unique<DataObject<bool>>(A, 3);
    bank3Sensor1presentIn4Banks = make_unique<DataObject<bool>>(A, 4);
    bank3Sensor2presentIn4Banks = make_unique<DataObject<bool>>(A, 5);
    bank4Sensor1presentIn4Banks = make_unique<DataObject<bool>>(A, 6);
    bank4Sensor2presentIn4Banks = make_unique<DataObject<bool>>(A, 7);

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

    size = 1;
    return data;
}

string BankOxygenSensors4BankCollection::getPrintableData() {
    return "bank1Sensor1presentIn4Banks: " + bank1Sensor1presentIn4Banks->getPrintableData() + "\n" +
           "bank1Sensor2presentIn4Banks: " + bank1Sensor2presentIn4Banks->getPrintableData() + "\n" +
           "bank2Sensor1presentIn4Banks: " + bank2Sensor1presentIn4Banks->getPrintableData() + "\n" +
           "bank2Sensor2presentIn4Banks: " + bank2Sensor2presentIn4Banks->getPrintableData() + "\n" +
           "bank3Sensor1presentIn4Banks: " + bank3Sensor1presentIn4Banks->getPrintableData() + "\n" +
           "bank3Sensor2presentIn4Banks: " + bank3Sensor2presentIn4Banks->getPrintableData() + "\n" +
           "bank4Sensor1presentIn4Banks: " + bank4Sensor1presentIn4Banks->getPrintableData() + "\n" +
           "bank4Sensor2presentIn4Banks: " + bank4Sensor2presentIn4Banks->getPrintableData() + "\n";
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
