//
// Created by me on 13/12/18.
//

#include "Vehicle.h"

Vehicle::Vehicle(Engine *engine) {
    supportedPids = new vector<int>();
    monitorStatus = new MonitorStatus(engine);
}

Vehicle::~Vehicle() {
    delete supportedPids;
//    delete monitorStatus;
}


Vehicle::Vehicle(Vehicle &vehicle) {

}

void Vehicle::fromFrame(byte *frame) {
    monitorStatus->fromFrame(frame);
}

MonitorStatus *Vehicle::getMonitorStatus() {
    return monitorStatus;
}

