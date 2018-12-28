//
// Created by me on 14/12/18.
//

#ifndef OPEN_OBD2_PID_H
#define OPEN_OBD2_PID_H

#include <vector>
#include <string>
#include "../Vehicle.h"
#include "../Service.h"
#include "../common/conversion.h"

using namespace std;

enum Service1Pids {
    SupportedPid01_20 = 0x00,
    SupportedPid21_40 = 0x20,
    SupportedPid41_60 = 0x40,
    SupportedPid61_80 = 0x60,
    SupportedPid81_A0 = 0x80,
    SupportedPidA1_C0 = 0xA0,
    SupportedPidC1_E0 = 0xC0,

    MonitoringStatus = 0x01,
    FreezeDTCPid = 0x02,
    FuelSystemStatus = 0x03,
    CalculatedEngineLoad = 0x04,
    EngineCoolantTemperature = 0x05,
    ShortTermFuelTrimBank1 = 0x06,
    LongTermFuelTrimBank1 = 0x07,
    ShortTermFuelTrimBank2 = 0x08,
    LongTermFuelTrimBank2 = 0x09,
    FuelPressure = 0x0a,
    IntakeManifoldAbsolutePressure = 0x0B,
    EngineRPM = 0x0C,
    VehicleSpeed = 0x0D,
    TimingAdvance = 0x0E,
    IntakeAirTemperature = 0x0F,
    MAFAirFlowRate = 0x10,

};

class Pid {
public:
    // todo refactor to getter / setter methods
    int id;
    int size;
    string description;
    int datafields;
    vector<float> maxValues;
    vector<float> minValues;
    vector<string> units;

    void updateVehicle(Service service, Vehicle *vehicle, byte *data, int dataSize);
    byte* getVehicleData(Service service, Vehicle *vehicle);

    void updateService1_2(Vehicle *vehicle, byte *data, int size);
    byte* readService1_2(Vehicle *vehicle);

};


#endif //OPEN_OBD2_PID_H
