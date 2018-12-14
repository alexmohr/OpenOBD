//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_VEHICLE_H
#define OPEN_OBD2_VEHICLE_H

#include <vector>

#include "OBD/data/BitEncoded/MonitorStatus.h"

using namespace std;



class Vehicle {
private:
    vector<int>* supportedPids;
    MonitorStatus* monitorStatus;

    int speed;
    int rpm;
    int coolantTemp;

public:
    explicit Vehicle(Engine* engine);
    ~Vehicle();
    Vehicle(Vehicle &vehicle);

    byte* PIDSupported01_20;
    byte* PIDSupported21_40;
    byte* PIDSupported41_60;
    byte* PIDSupported61_80;
    byte* PIDSupported81_A0;
    byte* PIDSupportedA1_C0;
    byte* PIDSupportedC1_E0;

    MonitorStatus* getMonitorStatus();
};


#endif //OPEN_OBD2_VEHICLE_H
