//
// Created by me on 13/12/18.
//

#include "Vehicle.h"
#include "common/endian.h"


Vehicle::Vehicle(shared_ptr<map<int, DataTroubleCode>> dtcMap) {
    this->dtcMap = dtcMap;
    engine = make_shared<Engine>();
    monitorStatus = make_unique<MonitorStatus>(engine);
    pidSupport = make_unique<PidSupport>();
    freezeDTC = make_unique<FreezeDTC>(dtcMap);


    fuelSystem1 = make_unique<DataObject<StateOfFuelSystem>>(A, 7, A, 0);
    fuelSystem2 = make_unique<DataObject<StateOfFuelSystem>>(B, 7, B, 0);

    commandedSecondaryAirStatus = make_unique<DataObject<StateOfCommandedSecondaryAir>>(A, 7, A, 0);

    speed = make_unique<DataObject<byte>>(A, 7, A, 0);

    throttlePosition = make_unique<CalculatedDataObject<byte, float>>(
            A, 7, A, 0, CalculatedValues::toPercent, CalculatedValues::fromPercent);

    oxygenSystem = make_unique<OxygenSystem>();
    obdCompliance = make_unique<OBDCompliance>();

    auxiliaryInputStatus = make_unique<DataObject<bool>>(A, 0);
    runTimeSinceEngineStart = make_unique<DataObject<unsigned short>>(A, 7, B, 0);

    distanceTraveledWithMilOn = make_unique<DataObject<unsigned short>>(A, 7, B, 0);

    fuelRailPressure = make_unique<CalculatedDataObject<unsigned short, float>>(
            A, 7, B, 0, CalculatedValues::to0_079_Times256APlusB, CalculatedValues::from0_079_Times256APlusB);

    fuelRailGaugePressure = make_unique<CalculatedDataObject<unsigned short, unsigned int>>(
            A, 7, B, 0, CalculatedValues::toUShortTimes10, CalculatedValues::fromUShortTimes10);

}

Vehicle::~Vehicle() = default;


//Vehicle::Vehicle(Vehicle &vehicle) {
//
//}


MonitorStatus &Vehicle::getMonitorStatus() {
    return *monitorStatus;
}


PidSupport &Vehicle::getPidSupport() {
    return *pidSupport;
}


FreezeDTC &Vehicle::getFreezeDTC() {
    return *freezeDTC;
}

DataObject<StateOfFuelSystem> &Vehicle::getFuelSystem1() {
    return *fuelSystem1;
}

DataObject<StateOfFuelSystem> &Vehicle::getFuelSystem2() {
    return *fuelSystem2;
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

OxygenSystem &Vehicle::getOxygenSystem() {
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











