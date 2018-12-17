//
// Created by me on 14/12/18.
//

#ifndef OPEN_OBD2_PID_H
#define OPEN_OBD2_PID_H

#include <vector>
#include <string>
#include "Vehicle.h"
#include "Service.h"

using namespace std;

class Pid {
public:
    int id;
    int size;
    string description;
    int datafields;
    vector<float> maxValues;
    vector<float> minValues;
    vector<string> units;
    vector<string> formulas;

    void updateVehicle(Service service, Vehicle *vehicle, byte *data, int dataSize);
    byte* getVehicleData(Service service, Vehicle *vehicle);

    void updateService1_2(Vehicle *vehicle, byte *data, int size);
    byte* readService1_2(Vehicle *vehicle);

    int to_int32(byte* data);

};


#endif //OPEN_OBD2_PID_H
