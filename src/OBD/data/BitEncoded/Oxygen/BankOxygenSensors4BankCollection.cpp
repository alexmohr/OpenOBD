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
    bank1Sensor1presentIn4Banks->fromFrame(frame, size);
    bank1Sensor2presentIn4Banks->fromFrame(frame, size);
    bank2Sensor1presentIn4Banks->fromFrame(frame, size);
    bank2Sensor2presentIn4Banks->fromFrame(frame, size);
    bank3Sensor1presentIn4Banks->fromFrame(frame, size);
    bank3Sensor2presentIn4Banks->fromFrame(frame, size);
    bank4Sensor1presentIn4Banks->fromFrame(frame, size);
    bank4Sensor2presentIn4Banks->fromFrame(frame, size);
}

unsigned int BankOxygenSensors4BankCollection::toFrame(unsigned int &data) {
    data |= bank1Sensor1presentIn4Banks->getValue() |
            bank1Sensor2presentIn4Banks->toFrame(data) |
            bank2Sensor1presentIn4Banks->toFrame(data) |
            bank2Sensor2presentIn4Banks->toFrame(data) |
            bank3Sensor1presentIn4Banks->toFrame(data) |
            bank3Sensor2presentIn4Banks->toFrame(data) |
            bank4Sensor1presentIn4Banks->toFrame(data) |
            bank4Sensor2presentIn4Banks->toFrame(data);

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
