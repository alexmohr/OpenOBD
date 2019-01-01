//
// Created by me on 13/12/18.
//

#include "Vehicle.h"
#include "common/endian.h"


Vehicle::Vehicle(shared_ptr<map<int, DataTroubleCode>> dtcMap) {
    this->dtcMap = dtcMap;
    engine = make_shared<Engine>();
    monitorStatusSinceDTCsCleared = make_unique<MonitorStatus>(&engine);
    monitorStatusThisDriveCycle = make_unique<MonitorStatus>(&engine);


    pidSupport = make_unique<PidSupport>();
    freezeDTC = make_unique<FreezeDTC>(dtcMap);


    commandedSecondaryAirStatus = make_unique<DataObject<StateOfCommandedSecondaryAir>>(A, 7, A, 0);

    speed = make_unique<DataObject<byte>>(A, 7, A, 0, unit_kph, (byte) 0, (byte) 255);

    throttlePosition = make_unique<CalculatedDataObject<byte, float>>(
            A, 7, A, 0, CalculatedValues::toPercent, CalculatedValues::fromPercent,
            unit_percent, 0.0f, 100.0);

    oxygenSystem = make_unique<OxygenSensors>();
    obdCompliance = make_unique<OBDCompliance>();

    auxiliaryInputStatus = make_unique<DataObject<bool>>(A, 0);
    runTimeSinceEngineStart = make_unique<DataObject<unsigned short>>(A, 7, B, 0, unit_seconds, 0, 65535);

    distanceTraveledWithMilOn = make_unique<DataObject<unsigned short>>(A, 7, B, 0);

    fuelRailPressure = make_unique<CalculatedDataObject<unsigned short, float>>(
            A, 7, B, 0, CalculatedValues::to0_079_Times256APlusB, CalculatedValues::from0_079_Times256APlusB,
            unit_kPa, 0.0f, 5177.265f);

    fuelRailGaugePressure = make_unique<CalculatedDataObject<unsigned short, unsigned int>>(
            A, 7, B, 0, CalculatedValues::toUShortTimes10, CalculatedValues::fromUShortTimes10,
            unit_kPa, 0, 655350);


    commandedEGR = make_unique<CalculatedDataObject<byte, float>>(
            A, 7, A, 0,
            CalculatedValues::toPercent, CalculatedValues::fromPercent,
            unit_percent, 0.0f, 100.0f);

    egrError = make_unique<CalculatedDataObject<byte, float>>(
            A, 7, A, 0,
            CalculatedValues::toPercent128Minus100, CalculatedValues::fromPercent128Minus100,
            unit_percent, -100.0f, 99.2);

    commandedEvaporativePurge = make_unique<CalculatedDataObject<byte, float>>(
            A, 7, A, 0,
            CalculatedValues::toPercent, CalculatedValues::fromPercent,
            unit_percent, 0, 100);

    fuelTankLevelInput = make_unique<CalculatedDataObject<byte, float>>(
            A, 7, A, 0,
            CalculatedValues::toPercent, CalculatedValues::fromPercent,
            unit_percent, 0.0f, 100.0f);

    warmUpsSinceCodesCleared = make_unique<DataObject<byte>>(
            A, 7, A, 0,
            unit_count, (byte) 0, (byte) 255);

    distanceTraveledSinceCodesCleared = make_unique<DataObject<unsigned short>>(
            A, 7, B, 0,
            unit_km, 0, 65535);

    evaporativePurgeSystemVaporPressure = make_unique<CalculatedDataObject<unsigned short, float>>(
            A, 7, B, 0,
            CalculatedValues::to256APlusBDivided4TwoComplement, CalculatedValues::from256APlusBDivided4TwoComplement,
            unit_percent, -8192, 8191.75);

    absoluteBarometricPressure = make_unique<DataObject<byte>>(
            A, 7, A, 0,
            unit_kPa, (byte) 0, (byte) 255);

    catalyst = make_unique<Catalyst>();
    fuelSystemStates = make_unique<FuelSystemStates>();
}

Vehicle::~Vehicle() = default;


//Vehicle::Vehicle(Vehicle &vehicle) {
//
//}


MonitorStatus &Vehicle::getMonitorStatusSinceDTCsCleared() {
    return *monitorStatusSinceDTCsCleared;
}

MonitorStatus &Vehicle::getMonitorStatusThisDriveCycle() {
    return *monitorStatusThisDriveCycle;
}

PidSupport &Vehicle::getPidSupport() {
    return *pidSupport;
}


FreezeDTC &Vehicle::getFreezeDTC() {
    return *freezeDTC;
}


Engine &Vehicle::getEngine() {
    return *engine;
}

DataObject<byte> &Vehicle::getSpeed() {
    return *speed;
}

CalculatedDataObject<byte, float> &Vehicle::getThrottlePosition() {
    return *throttlePosition;
}

DataObject<StateOfCommandedSecondaryAir> &Vehicle::getCommandedSecondaryAirStatus() {
    return *commandedSecondaryAirStatus;
}

OxygenSensors &Vehicle::getOxygenSystem() {
    return *oxygenSystem;
}

OBDCompliance &Vehicle::getOBDCompliance() {
    return *obdCompliance;
}

DataObject<bool> &Vehicle::getAuxiliaryInputStatus() {
    return *auxiliaryInputStatus;
}

DataObject<unsigned short> &Vehicle::getRunTimeSinceEngineStart() {
    return *runTimeSinceEngineStart;
}

DataObject<unsigned short> &Vehicle::getDistanceTraveledWithMilOn() {
    return *distanceTraveledWithMilOn;
}

CalculatedDataObject<unsigned short, float> &Vehicle::getFuelRailPressure() {
    return *fuelRailPressure;
}

CalculatedDataObject<unsigned short, unsigned int> &Vehicle::getFuelRailGaugePressure() {
    return *fuelRailGaugePressure;
}

CalculatedDataObject<byte, float> &Vehicle::getCommandedEGR() {
    return *commandedEGR;
}

CalculatedDataObject<byte, float> &Vehicle::getEGRError() {
    return *egrError;
}

CalculatedDataObject<byte, float> &Vehicle::getCommandedEvaporativePurge() {
    return *commandedEvaporativePurge;
}

CalculatedDataObject<byte, float> &Vehicle::getFuelTankLevelInput() {
    return *fuelTankLevelInput;
}

DataObject<byte> &Vehicle::getWarmUpsSinceCodesCleared() {
    return *warmUpsSinceCodesCleared;
}

DataObject<unsigned short> &Vehicle::getDistanceTraveledSinceCodesCleared() {
    return *distanceTraveledSinceCodesCleared;
}

CalculatedDataObject<unsigned short, float> &Vehicle::getEvaporativePurgeSystemVaporPressure() {
    return *evaporativePurgeSystemVaporPressure;
}

DataObject<byte> &Vehicle::getAbsoluteBarometricPressure() {
    return *absoluteBarometricPressure;
}

Catalyst &Vehicle::getCatalyst() {
    return *catalyst;
}

FuelSystemStates &Vehicle::getFuelSystemStates() {
    return *fuelSystemStates;
}







