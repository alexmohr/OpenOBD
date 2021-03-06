//
// Created by me on 14/12/18.
//

#ifndef OPEN_OBD2_PID_H
#define OPEN_OBD2_PID_H

#include <vector>
#include <string>
#include "../Vehicle.h"
#include "Service.h"
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

    MonitoringStatusSinceDTCsCleared = 0x01,
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
    ThrottlePosition = 0x11,
    CommandedSecondaryAirStatus = 0x12,
    OxygenSensorsPresent = 0x13,
    BankOxygenSensor1 = 0x14,
    BankOxygenSensor2 = 0x15,
    BankOxygenSensor3 = 0x16,
    BankOxygenSensor4 = 0x17,
    BankOxygenSensor5 = 0x18,
    BankOxygenSensor6 = 0x19,
    BankOxygenSensor7 = 0x1A,
    BankOxygenSensor8 = 0x1B,
    OBDStandardsVehicleConformsTo = 0x1C,
    OxygenSensorsPresent4Banks = 0x1D,
    AuxiliaryInputStatus = 0x1E,
    RunTimeSinceEngineStart = 0x1F,
    DistanceTraveledWithMilOn = 0x21,
    FuelRailPressure = 0x22,
    FuelRailGaugePressure = 0x23,
    FuelRailOxygenSensor1 = 0x24,
    FuelRailOxygenSensor2 = 0x25,
    FuelRailOxygenSensor3 = 0x26,
    FuelRailOxygenSensor4 = 0x27,
    FuelRailOxygenSensor5 = 0x28,
    FuelRailOxygenSensor6 = 0x29,
    FuelRailOxygenSensor7 = 0x2A,
    FuelRailOxygenSensor8 = 0x2B,
    CommandedEGR = 0x2C,
    EGRError = 0x2D,
    CommandedEvaporativePurge = 0x2E,
    FuelTankLevelInput = 0x2F,
    WarmUpsSinceCodesCleared = 0x30,
    DistanceTraveledSinceCodesCleared = 0x31,
    EvaporativePurgeSystemVaporPressure = 0x32,
    AbsoluteBarometricPressure = 0x33,
    ExtendedRangeOxygenSensor1 = 0x34,
    ExtendedRangeOxygenSensor2 = 0x35,
    ExtendedRangeOxygenSensor3 = 0x36,
    ExtendedRangeOxygenSensor4 = 0x37,
    ExtendedRangeOxygenSensor5 = 0x38,
    ExtendedRangeOxygenSensor6 = 0x39,
    ExtendedRangeOxygenSensor7 = 0x3A,
    ExtendedRangeOxygenSensor8 = 0x3B,
    CatalystTemperatureBank1Sensor1 = 0x3C,
    CatalystTemperatureBank2Sensor1 = 0x3D,
    CatalystTemperatureBank1Sensor2 = 0x3E,
    CatalystTemperatureBank2Sensor2 = 0x3F,
    MonitorStatusThisDriveCycle = 0x41,
    ControlModuleVoltage = 0x42,
    AbsoluteLoadValue = 0x43,
    FuelAirCommandedEquivalenceRatio = 0x44,
    RelativeThrottlePosition = 0x45,
    AmbientAirTemperature = 0x46,
    AbsoluteThrottlePositionB = 0x47,
    AbsoluteThrottlePositionC = 0x48,
    AcceleratorPedalPositionD = 0x49,
    AcceleratorPedalPositionE = 0x4A,
    AcceleratorPedalPositionF = 0x4B,
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

    byte *getVehicleData(Service service, Vehicle *vehicle, int &size);

    void writeService1_2(Vehicle *vehicle, byte *data, int size);

    byte *readService1_2(Vehicle *vehicle, int &size);

    byte *getQueryForService(Service service, int &buflen);

    IFrameObject *getFrameObject(Vehicle *vehicle);
};


#endif //OPEN_OBD2_PID_H
