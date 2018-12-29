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
#include "OBD/data/BitEncoded/OxygenSystem.h"
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
};


#endif //OPEN_OBD2_VEHICLE_H
