//
// Created by me on 13/12/18.
//

#include "Vehicle.h"
#include "common/endian.h"


Vehicle::Vehicle(shared_ptr<Engine> engine, shared_ptr<map<int, DataTroubleCode>> dtcMap) {
    this->dtcMap = dtcMap;
    monitorStatus = make_unique<MonitorStatus>(engine);
    pidSupport = make_unique<PidSupport>();
    freezeDTC = make_unique<FreezeDTC>(dtcMap);

    fuelSystem1 = make_unique<DataObject<FuelSystemStatus>>(A, 7, B, 0);
}

Vehicle::~Vehicle() {
}


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












