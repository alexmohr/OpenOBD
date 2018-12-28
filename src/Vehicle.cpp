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

    speed = make_unique<DataObject<byte>>(A, 7, A, 0);
}

Vehicle::~Vehicle() = default;


Vehicle::Vehicle(Vehicle &vehicle) {

}


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












