//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_VEHICLE_H
#define OPEN_OBD2_VEHICLE_H

#include <vector>

#include "OBD/data/BitEncoded/MonitorStatus.h"
#include "OBD/data/BitEncoded/FreezeDTC.h"
#include "OBD/data/BitEncoded/Pid/PidSupport.h"
#include "OBD/data/Enumerated/StateOfFuelSystem.h"
#include "OBD/data/Enumerated/StateOfCommandedSecondaryAir.h"
#include "OBD/data/BitEncoded/Oxygen/OxygenSensors.h"
#include "OBD/data/BitEncoded/OBDCompliance.h"
#include "OBD/data/BitEncoded/Catalyst.h"
#include "OBD/data/Enumerated/FuelSystemStates.h"
#include "OBD/data/BitEncoded/Throttle.h"

using namespace std;

class Vehicle {
private:
    unique_ptr<MonitorStatus> monitorStatusSinceDTCsCleared;
    unique_ptr<MonitorStatus> monitorStatusThisDriveCycle;

    unique_ptr<PidSupport> pidSupport;
    unique_ptr<FreezeDTC> freezeDTC;
    shared_ptr<Engine> engine;


    unique_ptr<DataObject<StateOfCommandedSecondaryAir>> commandedSecondaryAirStatus;

    unique_ptr<DataObject<byte>> speed;
    unique_ptr<OxygenSensors> oxygenSystem;
    unique_ptr<OBDCompliance> obdCompliance;

    unique_ptr<DataObject<bool>> auxiliaryInputStatus;
    unique_ptr<DataObject<unsigned short>> runTimeSinceEngineStart;
    unique_ptr<DataObject<unsigned short>> distanceTraveledWithMilOn;
    unique_ptr<CalculatedDataObject<unsigned short, float>> fuelRailPressure;
    unique_ptr<CalculatedDataObject<unsigned short, unsigned int>> fuelRailGaugePressure;


    unique_ptr<CalculatedDataObject<byte, float>> commandedEGR;
    unique_ptr<CalculatedDataObject<byte, float>> egrError;
    unique_ptr<CalculatedDataObject<byte, float>> commandedEvaporativePurge;
    unique_ptr<CalculatedDataObject<byte, float>> fuelTankLevelInput;
    unique_ptr<DataObject<byte>> warmUpsSinceCodesCleared;
    unique_ptr<DataObject<unsigned short>> distanceTraveledSinceCodesCleared;
    unique_ptr<CalculatedDataObject<unsigned short, float>> evaporativePurgeSystemVaporPressure;
    unique_ptr<DataObject<byte>> absoluteBarometricPressure;


    unique_ptr<CalculatedDataObject<unsigned short, float>> controlModuleVoltage;
    unique_ptr<CalculatedDataObject<unsigned short, unsigned short>> absoluteLoadValue;
    unique_ptr<CalculatedDataObject<unsigned short, float>> fuelAirCommandedEquivalenceRatio;
    unique_ptr<CalculatedDataObject<byte, short>> ambientAirTemperature;


    unique_ptr<Catalyst> catalyst;

    unique_ptr<FuelSystemStates> fuelSystemStates;
    unique_ptr<Throttle> throttle;

    shared_ptr<map<int, DataTroubleCode>> dtcMap;


public:
    explicit Vehicle(shared_ptr<map<int, DataTroubleCode>> dtcMap);

    ~Vehicle();
    // Vehicle(Vehicle &vehicle);
    // services
public:

    MonitorStatus &getMonitorStatusSinceDTCsCleared();

    MonitorStatus &getMonitorStatusThisDriveCycle();

    PidSupport &getPidSupport();

    FreezeDTC &getFreezeDTC();

    Engine &getEngine();

    DataObject<byte> &getSpeed();

    DataObject<StateOfCommandedSecondaryAir> &getCommandedSecondaryAirStatus();

    OxygenSensors &getOxygenSystem();

    OBDCompliance &getOBDCompliance();


    DataObject<bool> &getAuxiliaryInputStatus();

    DataObject<unsigned short> &getRunTimeSinceEngineStart();

    DataObject<unsigned short> &getDistanceTraveledWithMilOn();

    CalculatedDataObject<unsigned short, float> &getFuelRailPressure();

    CalculatedDataObject<unsigned short, unsigned int> &getFuelRailGaugePressure();

    CalculatedDataObject<byte, float> &getCommandedEGR();

    CalculatedDataObject<byte, float> &getEGRError();

    CalculatedDataObject<byte, float> &getCommandedEvaporativePurge();

    CalculatedDataObject<byte, float> &getFuelTankLevelInput();

    DataObject<byte> &getWarmUpsSinceCodesCleared();

    DataObject<unsigned short> &getDistanceTraveledSinceCodesCleared();

    CalculatedDataObject<unsigned short, float> &getEvaporativePurgeSystemVaporPressure();

    DataObject<byte> &getAbsoluteBarometricPressure();

    Catalyst &getCatalyst();

    FuelSystemStates &getFuelSystemStates();

    CalculatedDataObject<unsigned short, float> &getControlModuleVoltage();

    CalculatedDataObject<unsigned short, unsigned short> &getAbsoluteLoadValue();

    CalculatedDataObject<unsigned short, float> &getFuelAirCommandedEquivalenceRatio();

    CalculatedDataObject<byte, short> &getAmbientAirTemperature();

    Throttle &getThrottle();
};


#endif //OPEN_OBD2_VEHICLE_H
