//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_VEHICLE_H
#define OPEN_OBD2_VEHICLE_H

#include <vector>

#include "BitEncoded/MonitorStatus.h"

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
    void fromFrame(byte* frame);


    MonitorStatus* getMonitorStatus();
};


#endif //OPEN_OBD2_VEHICLE_H
