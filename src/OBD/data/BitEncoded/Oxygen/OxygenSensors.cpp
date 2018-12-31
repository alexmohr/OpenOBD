//
// Created by me on 28/12/18.
//

#include "OxygenSensors.h"

OxygenSystem::OxygenSystem() {
    bank1Sensor1present = make_unique<DataObject<bool>>(A, 0);
    bank1Sensor2present = make_unique<DataObject<bool>>(A, 1);
    bank1Sensor3present = make_unique<DataObject<bool>>(A, 2);
    bank1Sensor4present = make_unique<DataObject<bool>>(A, 3);
    bank2Sensor1present = make_unique<DataObject<bool>>(A, 4);
    bank2Sensor2present = make_unique<DataObject<bool>>(A, 5);
    bank2Sensor3present = make_unique<DataObject<bool>>(A, 6);
    bank2Sensor4present = make_unique<DataObject<bool>>(A, 7);

    bank1Sensor1presentIn4Banks = make_unique<DataObject<bool>>(A, 0);
    bank1Sensor2presentIn4Banks = make_unique<DataObject<bool>>(A, 1);
    bank2Sensor1presentIn4Banks = make_unique<DataObject<bool>>(A, 2);
    bank2Sensor2presentIn4Banks = make_unique<DataObject<bool>>(A, 3);
    bank3Sensor1presentIn4Banks = make_unique<DataObject<bool>>(A, 4);
    bank3Sensor2presentIn4Banks = make_unique<DataObject<bool>>(A, 5);
    bank4Sensor1presentIn4Banks = make_unique<DataObject<bool>>(A, 6);
    bank4Sensor2presentIn4Banks = make_unique<DataObject<bool>>(A, 7);

    bankOxygenSensor1 = make_unique<BankOxygenSensor>();
    bankOxygenSensor2 = make_unique<BankOxygenSensor>();
    bankOxygenSensor3 = make_unique<BankOxygenSensor>();
    bankOxygenSensor4 = make_unique<BankOxygenSensor>();
    bankOxygenSensor5 = make_unique<BankOxygenSensor>();
    bankOxygenSensor6 = make_unique<BankOxygenSensor>();
    bankOxygenSensor7 = make_unique<BankOxygenSensor>();
    bankOxygenSensor8 = make_unique<BankOxygenSensor>();

    fuelRailOxygenSensor1 = make_unique<FuelRailOxygenSensor>();
    fuelRailOxygenSensor2 = make_unique<FuelRailOxygenSensor>();
    fuelRailOxygenSensor3 = make_unique<FuelRailOxygenSensor>();
    fuelRailOxygenSensor4 = make_unique<FuelRailOxygenSensor>();
    fuelRailOxygenSensor5 = make_unique<FuelRailOxygenSensor>();
    fuelRailOxygenSensor6 = make_unique<FuelRailOxygenSensor>();
    fuelRailOxygenSensor7 = make_unique<FuelRailOxygenSensor>();
    fuelRailOxygenSensor8 = make_unique<FuelRailOxygenSensor>();

    extendedRangeOxygenSensor1 = make_unique<ExtendedRangeOxygenSensor>();
    extendedRangeOxygenSensor2 = make_unique<ExtendedRangeOxygenSensor>();
    extendedRangeOxygenSensor3 = make_unique<ExtendedRangeOxygenSensor>();
    extendedRangeOxygenSensor4 = make_unique<ExtendedRangeOxygenSensor>();
    extendedRangeOxygenSensor5 = make_unique<ExtendedRangeOxygenSensor>();
    extendedRangeOxygenSensor6 = make_unique<ExtendedRangeOxygenSensor>();
    extendedRangeOxygenSensor7 = make_unique<ExtendedRangeOxygenSensor>();
    extendedRangeOxygenSensor8 = make_unique<ExtendedRangeOxygenSensor>();
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

unsigned int OxygenSystem::getBankSensorsPresentToFrame(unsigned int &data) {
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

void OxygenSystem::getBankSensorsPresentFromFrame(byte *frame, int size) {
    bank1Sensor1present->fromFrame(frame, size);
    bank1Sensor2present->fromFrame(frame, size);
    bank1Sensor3present->fromFrame(frame, size);
    bank1Sensor4present->fromFrame(frame, size);
    bank2Sensor1present->fromFrame(frame, size);
    bank2Sensor2present->fromFrame(frame, size);
    bank2Sensor3present->fromFrame(frame, size);
    bank2Sensor4present->fromFrame(frame, size);
}

DataObject<bool> &OxygenSystem::getBank1Sensor1presentIn4Banks() {
    return *bank1Sensor1presentIn4Banks;
}

DataObject<bool> &OxygenSystem::getBank1Sensor2presentIn4Banks() {
    return *bank1Sensor2presentIn4Banks;
}

DataObject<bool> &OxygenSystem::getBank2Sensor1presentIn4Banks() {
    return *bank2Sensor1presentIn4Banks;
}

DataObject<bool> &OxygenSystem::getBank2Sensor2presentIn4Banks() {
    return *bank2Sensor2presentIn4Banks;
}

DataObject<bool> &OxygenSystem::getBank3Sensor1presentIn4Banks() {
    return *bank3Sensor1presentIn4Banks;
}

DataObject<bool> &OxygenSystem::getBank3Sensor2presentIn4Banks() {
    return *bank3Sensor2presentIn4Banks;
}

DataObject<bool> &OxygenSystem::getBank4Sensor1presentIn4Banks() {
    return *bank4Sensor1presentIn4Banks;
}

DataObject<bool> &OxygenSystem::getBank4Sensor2presentIn4Banks() {
    return *bank4Sensor2presentIn4Banks;
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


void OxygenSystem::getBankSensorsPresentIn4BanksFromFrame(byte *frame, int size) {
    bank1Sensor1presentIn4Banks->fromFrame(frame, size);
    bank1Sensor2presentIn4Banks->fromFrame(frame, size);
    bank2Sensor1presentIn4Banks->fromFrame(frame, size);
    bank2Sensor2presentIn4Banks->fromFrame(frame, size);
    bank3Sensor1presentIn4Banks->fromFrame(frame, size);
    bank3Sensor2presentIn4Banks->fromFrame(frame, size);
    bank4Sensor1presentIn4Banks->fromFrame(frame, size);
    bank4Sensor2presentIn4Banks->fromFrame(frame, size);
}

unsigned int OxygenSystem::getBankSensorsPresentIn4BanksToFrame(unsigned int &data) {
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


FuelRailOxygenSensor &OxygenSystem::getFuelRailOxygenSensor1() {
    return *fuelRailOxygenSensor1;
}

FuelRailOxygenSensor &OxygenSystem::getFuelRailOxygenSensor2() {
    return *fuelRailOxygenSensor2;
}

FuelRailOxygenSensor &OxygenSystem::getFuelRailOxygenSensor3() {
    return *fuelRailOxygenSensor3;
}

FuelRailOxygenSensor &OxygenSystem::getFuelRailOxygenSensor4() {
    return *fuelRailOxygenSensor4;
}

FuelRailOxygenSensor &OxygenSystem::getFuelRailOxygenSensor5() {
    return *fuelRailOxygenSensor5;
}

FuelRailOxygenSensor &OxygenSystem::getFuelRailOxygenSensor6() {
    return *fuelRailOxygenSensor6;
}

FuelRailOxygenSensor &OxygenSystem::getFuelRailOxygenSensor7() {
    return *fuelRailOxygenSensor7;
}

FuelRailOxygenSensor &OxygenSystem::getFuelRailOxygenSensor8() {
    return *fuelRailOxygenSensor8;
}


ExtendedRangeOxygenSensor &OxygenSystem::getExtendedRangeOxygenSensor1() {
    return *extendedRangeOxygenSensor1;
}

ExtendedRangeOxygenSensor &OxygenSystem::getExtendedRangeOxygenSensor2() {
    return *extendedRangeOxygenSensor2;
}

ExtendedRangeOxygenSensor &OxygenSystem::getExtendedRangeOxygenSensor3() {
    return *extendedRangeOxygenSensor3;
}

ExtendedRangeOxygenSensor &OxygenSystem::getExtendedRangeOxygenSensor4() {
    return *extendedRangeOxygenSensor4;
}

ExtendedRangeOxygenSensor &OxygenSystem::getExtendedRangeOxygenSensor5() {
    return *extendedRangeOxygenSensor5;
}

ExtendedRangeOxygenSensor &OxygenSystem::getExtendedRangeOxygenSensor6() {
    return *extendedRangeOxygenSensor6;
}

ExtendedRangeOxygenSensor &OxygenSystem::getExtendedRangeOxygenSensor7() {
    return *extendedRangeOxygenSensor7;
}

ExtendedRangeOxygenSensor &OxygenSystem::getExtendedRangeOxygenSensor8() {
    return *extendedRangeOxygenSensor8;
}
