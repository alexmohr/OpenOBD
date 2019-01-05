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
    data |= bank1Sensor1present->getValue() |
            bank1Sensor2present->toFrame(data, size) |
            bank1Sensor3present->toFrame(data, size) |
            bank1Sensor4present->toFrame(data, size) |
            bank2Sensor1present->toFrame(data, size) |
            bank2Sensor2present->toFrame(data, size) |
            bank2Sensor3present->toFrame(data, size) |
            bank2Sensor4present->toFrame(data, size);
    size = 1;
    return data;
}

void BankOxygenSensorsCollection::fromFrame(byte *frame, int size) {
    bank1Sensor1present->fromFrame(frame, size);
    bank1Sensor2present->fromFrame(frame, size);
    bank1Sensor3present->fromFrame(frame, size);
    bank1Sensor4present->fromFrame(frame, size);
    bank2Sensor1present->fromFrame(frame, size);
    bank2Sensor2present->fromFrame(frame, size);
    bank2Sensor3present->fromFrame(frame, size);
    bank2Sensor4present->fromFrame(frame, size);
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

int BankOxygenSensorsCollection::setValueFromString(string data) {
    auto parts = splitString(const_cast<char *>(data.c_str()));
    const int paramCount = 8;
    if (paramCount > parts.size()) {
        LOG(ERROR) << "Insufficient parameter count expected " << paramCount;
        return paramCount;
    }

    bank1Sensor1present->setValueFromString(parts.at(0));
    bank1Sensor2present->setValueFromString(parts.at(1));
    bank1Sensor3present->setValueFromString(parts.at(2));
    bank1Sensor4present->setValueFromString(parts.at(3));
    bank2Sensor1present->setValueFromString(parts.at(4));
    bank2Sensor2present->setValueFromString(parts.at(5));
    bank2Sensor3present->setValueFromString(parts.at(6));
    bank2Sensor4present->setValueFromString(parts.at(7));

    return 0;
}

vector<DataObjectDescription *> BankOxygenSensorsCollection::getDescriptions() {
    return vector<DataObjectDescription *>{
            bank1Sensor1present->getDescriptions().at(0),
            bank1Sensor2present->getDescriptions().at(0),
            bank1Sensor3present->getDescriptions().at(0),
            bank1Sensor4present->getDescriptions().at(0),
            bank2Sensor1present->getDescriptions().at(0),
            bank2Sensor2present->getDescriptions().at(0),
            bank2Sensor3present->getDescriptions().at(0),
            bank2Sensor4present->getDescriptions().at(0)};
}
