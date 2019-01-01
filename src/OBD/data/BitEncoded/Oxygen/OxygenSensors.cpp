//
// Created by me on 28/12/18.
//

#include "OxygenSensors.h"

OxygenSensors::OxygenSensors() {

    bankOxygenSensorCollection = make_unique<BankOxygenSensorsCollection>();
    bankOxygenSensor4BankCollection = make_unique<BankOxygenSensors4BankCollection>();

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


BankOxygenSensor &OxygenSensors::getBankOxygenSensor1() {
    return *bankOxygenSensor1;
}

BankOxygenSensor &OxygenSensors::getBankOxygenSensor2() {
    return *bankOxygenSensor2;
}

BankOxygenSensor &OxygenSensors::getBankOxygenSensor3() {
    return *bankOxygenSensor3;
}

BankOxygenSensor &OxygenSensors::getBankOxygenSensor4() {
    return *bankOxygenSensor4;
}

BankOxygenSensor &OxygenSensors::getBankOxygenSensor5() {
    return *bankOxygenSensor5;
}

BankOxygenSensor &OxygenSensors::getBankOxygenSensor6() {
    return *bankOxygenSensor6;
}

BankOxygenSensor &OxygenSensors::getBankOxygenSensor7() {
    return *bankOxygenSensor7;
}

BankOxygenSensor &OxygenSensors::getBankOxygenSensor8() {
    return *bankOxygenSensor8;
}

FuelRailOxygenSensor &OxygenSensors::getFuelRailOxygenSensor1() {
    return *fuelRailOxygenSensor1;
}

FuelRailOxygenSensor &OxygenSensors::getFuelRailOxygenSensor2() {
    return *fuelRailOxygenSensor2;
}

FuelRailOxygenSensor &OxygenSensors::getFuelRailOxygenSensor3() {
    return *fuelRailOxygenSensor3;
}

FuelRailOxygenSensor &OxygenSensors::getFuelRailOxygenSensor4() {
    return *fuelRailOxygenSensor4;
}

FuelRailOxygenSensor &OxygenSensors::getFuelRailOxygenSensor5() {
    return *fuelRailOxygenSensor5;
}

FuelRailOxygenSensor &OxygenSensors::getFuelRailOxygenSensor6() {
    return *fuelRailOxygenSensor6;
}

FuelRailOxygenSensor &OxygenSensors::getFuelRailOxygenSensor7() {
    return *fuelRailOxygenSensor7;
}

FuelRailOxygenSensor &OxygenSensors::getFuelRailOxygenSensor8() {
    return *fuelRailOxygenSensor8;
}


ExtendedRangeOxygenSensor &OxygenSensors::getExtendedRangeOxygenSensor1() {
    return *extendedRangeOxygenSensor1;
}

ExtendedRangeOxygenSensor &OxygenSensors::getExtendedRangeOxygenSensor2() {
    return *extendedRangeOxygenSensor2;
}

ExtendedRangeOxygenSensor &OxygenSensors::getExtendedRangeOxygenSensor3() {
    return *extendedRangeOxygenSensor3;
}

ExtendedRangeOxygenSensor &OxygenSensors::getExtendedRangeOxygenSensor4() {
    return *extendedRangeOxygenSensor4;
}

ExtendedRangeOxygenSensor &OxygenSensors::getExtendedRangeOxygenSensor5() {
    return *extendedRangeOxygenSensor5;
}

ExtendedRangeOxygenSensor &OxygenSensors::getExtendedRangeOxygenSensor6() {
    return *extendedRangeOxygenSensor6;
}

ExtendedRangeOxygenSensor &OxygenSensors::getExtendedRangeOxygenSensor7() {
    return *extendedRangeOxygenSensor7;
}

ExtendedRangeOxygenSensor &OxygenSensors::getExtendedRangeOxygenSensor8() {
    return *extendedRangeOxygenSensor8;
}

BankOxygenSensorsCollection &OxygenSensors::getBankOxygenSensorsCollection() {
    return *bankOxygenSensorCollection;
}

BankOxygenSensors4BankCollection &OxygenSensors::getBankOxygenSensor4BankCollection() {
    return *bankOxygenSensor4BankCollection;
}
