//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_VEHICLE_H
#define OPEN_OBD2_VEHICLE_H

#include <vector>

#include "OBD/data/BitEncoded/MonitorStatus.h"

using namespace std;

enum PidRange {
    Pid01_20,
    Pid21_40,
    Pid41_60,
    Pid61_80,
    Pid81_A0,
    PidA1_C0,
    PidC1_E0
};


class Vehicle {
private:
    MonitorStatus* monitorStatus;

    int speed;
    int rpm;
    int coolantTemp;

    void initPid(vector<DataObject<bool>> *data);

    vector<DataObject<bool>> *PIDSupported01_20;
    vector<DataObject<bool>> *PIDSupported21_40;
    vector<DataObject<bool>> *PIDSupported41_60;
    vector<DataObject<bool>> *PIDSupported61_80;
    vector<DataObject<bool>> *PIDSupported81_A0;
    vector<DataObject<bool>> *PIDSupportedA1_C0;
    vector<DataObject<bool>> *PIDSupportedC1_E0;



public:
    explicit Vehicle(Engine* engine);
    ~Vehicle();
    Vehicle(Vehicle &vehicle);


    void setPidSupported(int pid, bool supported);

    bool getPidSupported(int pid);

    void setPidSupportedFromFrame(PidRange pid, byte *data, int size);

    unsigned int getPidSupportedRange(PidRange pid, unsigned int &data);

    void setPids(vector<DataObject<bool>> *pids, byte *data, int size);

    unsigned int getPids(vector<DataObject<bool>> *pids, unsigned int &data);

    MonitorStatus* getMonitorStatus();
};


#endif //OPEN_OBD2_VEHICLE_H
