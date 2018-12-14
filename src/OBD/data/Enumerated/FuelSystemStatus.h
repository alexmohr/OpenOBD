//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_FUELSYSTEMSTATUS_H
#define OPEN_OBD2_FUELSYSTEMSTATUS_H


enum FuelSystemStatus{
    OpenLoopEngineTooCool = 1,
    ClosedLoopUsingOxygenSensor = 2,
    OpenLoadEngineLoadOrFuelCut = 4,
    OpenLoopFailure = 8;
    ClosedLoopUsingOxygenSensorWithFault = 16
};

#endif //OPEN_OBD2_FUELSYSTEMSTATUS_H
