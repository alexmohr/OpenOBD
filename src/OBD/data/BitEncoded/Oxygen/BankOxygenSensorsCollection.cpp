//
// Created by me on 01/01/19.
//

#include "BankOxygenSensorsCollection.h"

BankOxygenSensorsCollection::BankOxygenSensorsCollection() {
    bank1Sensor1present = make_unique<DataObject<bool>>(A, 0);
    bank1Sensor2present = make_unique<DataObject<bool>>(A, 1);
    bank1Sensor3present = make_unique<DataObject<bool>>(A, 2);
    bank1Sensor4present = make_unique<DataObject<bool>>(A, 3);
    bank2Sensor1present = make_unique<DataObject<bool>>(A, 4);
    bank2Sensor2present = make_unique<DataObject<bool>>(A, 5);
    bank2Sensor3present = make_unique<DataObject<bool>>(A, 6);
    bank2Sensor4present = make_unique<DataObject<bool>>(A, 7);

    allSensors = vector<DataObject<bool> *>{
            bank1Sensor1present.get(), bank1Sensor2present.get(), bank1Sensor3present.get(), bank1Sensor4present.get(),
            bank2Sensor1present.get(), bank2Sensor2present.get(), bank2Sensor3present.get(), bank2Sensor4present.get()};
}


DataObject<bool> &BankOxygenSensorsCollection::getBank1Sensor1present() {
    return *bank1Sensor1present;
}

DataObject<bool> &BankOxygenSensorsCollection::getBank1Sensor2present() {
    return *bank1Sensor2present;
}

DataObject<bool> &BankOxygenSensorsCollection::getBank1Sensor3present() {
    return *bank1Sensor3present;
}

DataObject<bool> &BankOxygenSensorsCollection::getBank1Sensor4present() {
    return *bank1Sensor4present;
}

DataObject<bool> &BankOxygenSensorsCollection::getBank2Sensor1present() {
    return *bank2Sensor1present;
}

DataObject<bool> &BankOxygenSensorsCollection::getBank2Sensor2present() {
    return *bank2Sensor2present;
}

DataObject<bool> &BankOxygenSensorsCollection::getBank2Sensor3present() {
    return *bank2Sensor3present;
}

DataObject<bool> &BankOxygenSensorsCollection::getBank2Sensor4present() {
    return *bank2Sensor4present;
}

unsigned int BankOxygenSensorsCollection::toFrame(unsigned int &data, int &size) {
    for (const auto &sensor: allSensors) {
        data |= sensor->toFrame(data, size);
    }
    return data;
}

void BankOxygenSensorsCollection::fromFrame(byte *frame, int size) {
    for (const auto &sensor: allSensors) {
        sensor->fromFrame(frame, size);
    }
}

string BankOxygenSensorsCollection::getPrintableData() {
    return "bank1Sensor1present: " + bank1Sensor1present->getPrintableData() +
           "bank1Sensor2present: " + bank1Sensor2present->getPrintableData() +
           "bank1Sensor3present: " + bank1Sensor3present->getPrintableData() +
           "bank1Sensor4present: " + bank1Sensor4present->getPrintableData() +
           "bank2Sensor1present: " + bank2Sensor1present->getPrintableData() +
           "bank2Sensor2present: " + bank2Sensor2present->getPrintableData() +
           "bank2Sensor3present: " + bank2Sensor3present->getPrintableData() +
           "bank2Sensor4present: " + bank2Sensor4present->getPrintableData();
}

DataObjectStateCollection BankOxygenSensorsCollection::setValueFromString(string data) {
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

vector<DataObjectDescription *> BankOxygenSensorsCollection::getDescriptions() {
    vector<DataObjectDescription *> desc;
    for (const auto &sensor: allSensors) {
        auto sdesc = sensor->getDescriptions();
        desc.insert(desc.end(), sdesc.begin(), sdesc.end());
    }
    return desc;
}
