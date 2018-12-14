//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_MONITORSTATUS_H
#define OPEN_OBD2_MONITORSTATUS_H

#include "types.h"
#include "../DataObject.h"
#include "Engine.h"
#include "../OBDTest.h"



class MonitorStatus{
private:
    /**
     * Off or On, indicates if the CEL/MIL is on (or should be on)
     * * Byte A7
     */
    DataObject<bool> mil = DataObject<bool>(A, 7);

    /**
     * Number of confirmed emissions-related DTCs available for display.
     * Byte A6-A0
     */
    DataObject<unsigned int> dtcCount = DataObject<unsigned int>(A,6, A,0);


    /**
     * Defines which engine type the vehicle has
     */
    Engine engineStatus;


    OBDTest components = OBDTest("Components", B,2,B,6);
    OBDTest fuelSystem = OBDTest("FuelSystem", B,1,B,5);
    OBDTest misfire = OBDTest("Misfire", B,0,B,4);

public:

    /**
     * Create a monitor status object from a frame
     * @param frameData the can frame data.
     */
    MonitorStatus(BYTE *frameData);


    /**
     * Create the object from simulated data.
     * @param mil the status of the mil
     * @param dtcCount number of trouble codes
     * @param engine engine of the vehicle
     */
    MonitorStatus(bool mil, unsigned int dtcCount, Engine engine);

    /**
     * Converts this object into frame data.
     * @return Byte array representing the monitoring status
     */
    BYTE* toFrame();

};

#endif //OPEN_OBD2_MONITORSTATUS_H
