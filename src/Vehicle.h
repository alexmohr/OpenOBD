//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_VEHICLE_H
#define OPEN_OBD2_VEHICLE_H

#include <vector>

#include "OBD/data/BitEncoded/MonitorStatus.h"
#include "OBD/data/BitEncoded/FreezeDTC.h"
#include "OBD/data/BitEncoded/PidSupport.h"
#include "OBD/data/Enumerated/StateOfFuelSystem.h"
#include "OBD/data/Enumerated/StateOfCommandedSecondaryAir.h"
#include "OBD/data/BitEncoded/Oxygen/OxygenSensors.h"
#include "OBD/data/BitEncoded/OBDCompliance.h"


using namespace std;


class Vehicle {
private:
    unique_ptr<MonitorStatus> monitorStatus;
    unique_ptr<PidSupport> pidSupport;
    unique_ptr<FreezeDTC> freezeDTC;
    shared_ptr<Engine> engine;

    unique_ptr<DataObject<StateOfFuelSystem>> fuelSystem1;
    unique_ptr<DataObject<StateOfFuelSystem>> fuelSystem2;
    unique_ptr<DataObject<StateOfCommandedSecondaryAir>> commandedSecondaryAirStatus;

    unique_ptr<DataObject<byte>> speed;

    unique_ptr<CalculatedDataObject<byte, float>> throttlePosition;
    unique_ptr<OxygenSystem> oxygenSystem;
    unique_ptr<OBDCompliance> obdCompliance;

    unique_ptr<DataObject<bool>> auxiliaryInputStatus;
    unique_ptr<DataObject<unsigned short>> runTimeSinceEngineStart;
    unique_ptr<DataObject<unsigned short>> distanceTraveledWithMilOn;
    unique_ptr<CalculatedDataObject<unsigned short, float>> fuelRailPressure;
    unique_ptr<CalculatedDataObject<unsigned short, unsigned int>> fuelRailGaugePressure;


    /*

    2C	1	Commanded EGR	0	100	%	100 255 A {\displaystyle {\tfrac {100}{255}}A}
    2D	1	EGR Error	-100	99.2	%	100 128 A − 100 {\displaystyle {\tfrac {100}{128}}A-100}
    2E	1	Commanded evaporative purge	0	100	%	100 255 A {\displaystyle {\tfrac {100}{255}}A}
    2F	1	Fuel Tank Level Input	0	100	%	100 255 A {\displaystyle {\tfrac {100}{255}}A}
    30	1	Warm-ups since codes cleared	0	255	count	A {\displaystyle A}
    31	2	Distance traveled since codes cleared	0	65535	km	256 A + B {\displaystyle 256A+B}
    32	2	Evap. System Vapor Pressure	-8192	8191.75	Pa	256 A + B 4 {\displaystyle {\frac {256A+B}{4}}}  (AB is two's complement signed)[1]
    33	1	Absolute Barometric Pressure	0	255	kPa	A {\displaystyle A}

     */

    unique_ptr<CalculatedDataObject<byte, float>> commandedEGR;
    unique_ptr<CalculatedDataObject<byte, float>> egrError;
    unique_ptr<CalculatedDataObject<byte, float>> commandedEvaporativePurge;
    unique_ptr<CalculatedDataObject<byte, float>> fuelTankLevelInput;
    unique_ptr<DataObject<byte>> warmUpsSinceCodesCleared;
    unique_ptr<DataObject<unsigned short>> distanceTraveledSinceCodesCleared;
    unique_ptr<CalculatedDataObject<unsigned short, float>> evaporativePurgeSystemVaporPressure;
    unique_ptr<DataObject<byte>> absoluteBarometricPressure;

    shared_ptr<map<int, DataTroubleCode>> dtcMap;


public:
    explicit Vehicle(shared_ptr<map<int, DataTroubleCode>> dtcMap);

    ~Vehicle();
    // Vehicle(Vehicle &vehicle);
    // services
public:

    MonitorStatus &getMonitorStatus();

    PidSupport &getPidSupport();

    FreezeDTC &getFreezeDTC();

    Engine &getEngine();

    DataObject<StateOfFuelSystem> &getFuelSystem1();

    DataObject<StateOfFuelSystem> &getFuelSystem2();

    DataObject<byte> &getSpeed();

    CalculatedDataObject<byte, float> &getThrottlePosition();

    DataObject<StateOfCommandedSecondaryAir> &getCommandedSecondaryAirStatus();

    OxygenSystem &getOxygenSystem();

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

};


#endif //OPEN_OBD2_VEHICLE_H
