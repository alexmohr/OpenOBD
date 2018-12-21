//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_VEHICLE_H
#define OPEN_OBD2_VEHICLE_H

#include <vector>

#include "OBD/data/BitEncoded/MonitorStatus.h"
#include "OBD/data/BitEncoded/FreezeDTC.h"
#include "OBD/data/BitEncoded/PidSupport.h"


using namespace std;




class Vehicle {
private:
    unique_ptr<MonitorStatus> monitorStatus;
    unique_ptr<PidSupport> pidSupport;
    unique_ptr<FreezeDTC> freezeDTC;

    int speed;
    int rpm;
    int coolantTemp;


    shared_ptr<map<int, DataTroubleCode>> dtcMap;



public:
    Vehicle(shared_ptr<Engine> engine, shared_ptr<map<int, DataTroubleCode>> dtcMap);
    ~Vehicle();
    Vehicle(Vehicle &vehicle);
    // services
public:

    MonitorStatus &getMonitorStatus();

    PidSupport &getPidSupport();

    FreezeDTC &getFreezeDTC();

};


#endif //OPEN_OBD2_VEHICLE_H
