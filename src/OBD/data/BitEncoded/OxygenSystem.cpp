//
// Created by me on 28/12/18.
//

#include "OxygenSystem.h"

OxygenSystem::OxygenSystem() {
    bank1Sensor1present = make_unique<DataObject<bool>>(A, 0);
    bank1Sensor2present = make_unique<DataObject<bool>>(A, 1);
    bank1Sensor3present = make_unique<DataObject<bool>>(A, 2);
    bank1Sensor4present = make_unique<DataObject<bool>>(A, 3);
    bank2Sensor1present = make_unique<DataObject<bool>>(A, 4);
    bank2Sensor2present = make_unique<DataObject<bool>>(A, 5);
    bank2Sensor3present = make_unique<DataObject<bool>>(A, 6);
    bank2Sensor4present = make_unique<DataObject<bool>>(A, 7);

    bankOxygenSensor1 = make_unique<BankOxygenSensor>();
    bankOxygenSensor2 = make_unique<BankOxygenSensor>();
    bankOxygenSensor3 = make_unique<BankOxygenSensor>();
    bankOxygenSensor4 = make_unique<BankOxygenSensor>();
    bankOxygenSensor5 = make_unique<BankOxygenSensor>();
    bankOxygenSensor6 = make_unique<BankOxygenSensor>();
    bankOxygenSensor7 = make_unique<BankOxygenSensor>();
    bankOxygenSensor8 = make_unique<BankOxygenSensor>();
}


DataObject<bool> &OxygenSystem::getBank1Sensor1present() {
    return *bank1Sensor1present;
}

DataObject<bool> &OxygenSystem::getBank1Sensor2present() {
    return *bank1Sensor2present;
}

DataObject<bool> &OxygenSystem::getBank1Sensor3present() {
    return *bank1Sensor3present;
}

DataObject<bool> &OxygenSystem::getBank1Sensor4present() {
    return *bank1Sensor4present;
}

DataObject<bool> &OxygenSystem::getBank2Sensor1present() {
    return *bank2Sensor1present;
}

DataObject<bool> &OxygenSystem::getBank2Sensor2present() {
    return *bank2Sensor2present;
}

DataObject<bool> &OxygenSystem::getBank2Sensor3present() {
    return *bank2Sensor3present;
}

DataObject<bool> &OxygenSystem::getBank2Sensor4present() {
    return *bank2Sensor4present;
}

unsigned int OxygenSystem::bankSensorsPresentToFrame(unsigned int &data) {
    data |= bank1Sensor1present->getValue() |
            bank1Sensor2present->toFrame(data) |
            bank1Sensor3present->toFrame(data) |
            bank1Sensor4present->toFrame(data) |
            bank2Sensor1present->toFrame(data) |
            bank2Sensor2present->toFrame(data) |
            bank2Sensor3present->toFrame(data) |
            bank2Sensor4present->toFrame(data);

    return data;
}

void OxygenSystem::bankSensorsPresentFromFrame(byte *frame, int size) {
    bank1Sensor1present->fromFrame(frame, size);
    bank1Sensor2present->fromFrame(frame, size);
    bank1Sensor3present->fromFrame(frame, size);
    bank1Sensor4present->fromFrame(frame, size);
    bank2Sensor1present->fromFrame(frame, size);
    bank2Sensor2present->fromFrame(frame, size);
    bank2Sensor3present->fromFrame(frame, size);
    bank2Sensor4present->fromFrame(frame, size);
}


BankOxygenSensor &OxygenSystem::getBankOxygenSensor1() {
    return *bankOxygenSensor1;
}

BankOxygenSensor &OxygenSystem::getBankOxygenSensor2() {
    return *bankOxygenSensor2;
}

BankOxygenSensor &OxygenSystem::getBankOxygenSensor3() {
    return *bankOxygenSensor3;
}

BankOxygenSensor &OxygenSystem::getBankOxygenSensor4() {
    return *bankOxygenSensor4;
}

BankOxygenSensor &OxygenSystem::getBankOxygenSensor5() {
    return *bankOxygenSensor5;
}

BankOxygenSensor &OxygenSystem::getBankOxygenSensor6() {
    return *bankOxygenSensor6;
}

BankOxygenSensor &OxygenSystem::getBankOxygenSensor7() {
    return *bankOxygenSensor7;
}

BankOxygenSensor &OxygenSystem::getBankOxygenSensor8() {
    return *bankOxygenSensor8;
}


