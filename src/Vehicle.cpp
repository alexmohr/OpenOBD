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
    oxygenSystem = make_unique<OxygenSensors>();
    obdCompliance = make_unique<OBDCompliance>();
    catalyst = make_unique<Catalyst>();
    fuelSystemStates = make_unique<FuelSystemStates>();
    throttle = make_unique<Throttle>();


    commandedSecondaryAirStatus = make_unique<DataObject<StateOfCommandedSecondaryAir>>(
            A, 7, A, 0,
            unit_none, CommandedSecondaryAirStatusDoesNotExist, PumpCommandedOnForDiagnostics);

    speed = make_unique<DataObject<byte>>(A, 7, A, 0, unit_kph, (byte) 0, (byte) 255);
    warmUpsSinceCodesCleared = make_unique<DataObject<byte>>(A, 7, A, 0, unit_count, (byte) 0, (byte) 255);
    distanceTraveledSinceCodesCleared = make_unique<DataObject<unsigned short>>(A, 7, B, 0, unit_km, 0, 65535);

    auxiliaryInputStatus = make_unique<DataObject<bool>>(A, 0);
    runTimeSinceEngineStart = make_unique<DataObject<unsigned short>>(A, 7, B, 0, unit_seconds, 0, 65535);

    distanceTraveledWithMilOn = make_unique<DataObject<unsigned short>>(A, 7, B, 0, unit_km, 0, 65535);

    absoluteBarometricPressure = make_unique<DataObject<byte>>(A, 7, A, 0, unit_kPa, (byte) 0, (byte) 255);


    fuelRailPressure = CalculatedDataObjectFactory::kPa_0_079Value();
    fuelRailGaugePressure = CalculatedDataObjectFactory::kPa_UShortTimes10();
    commandedEGR = CalculatedDataObjectFactory::percent();

    egrError = CalculatedDataObjectFactory::percent_Percent128Minus100(A);
    commandedEvaporativePurge = CalculatedDataObjectFactory::percent();
    fuelTankLevelInput = CalculatedDataObjectFactory::percent();

    evaporativePurgeSystemVaporPressure = CalculatedDataObjectFactory::percent_Divided4TwoComplement();
    controlModuleVoltage = CalculatedDataObjectFactory::volt_Divided1000();
    absoluteLoadValue = CalculatedDataObjectFactory::percent_100Divided255TimesTimes256APlusB();

    fuelAirCommandedEquivalenceRatio = CalculatedDataObjectFactory::ratio_2Divided2Pow16TimesValue();
    ambientAirTemperature = CalculatedDataObjectFactory::celsius_AMinus40();
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

CalculatedDataObject<unsigned short, float> &Vehicle::getControlModuleVoltage() {
    return *controlModuleVoltage;
}

CalculatedDataObject<unsigned short, unsigned short> &Vehicle::getAbsoluteLoadValue() {
    return *absoluteLoadValue;
}

CalculatedDataObject<unsigned short, float> &Vehicle::getFuelAirCommandedEquivalenceRatio() {
    return *fuelAirCommandedEquivalenceRatio;
}

CalculatedDataObject<byte, short> &Vehicle::getAmbientAirTemperature() {
    return *ambientAirTemperature;
}

Throttle &Vehicle::getThrottle() {
    return *throttle;
}





