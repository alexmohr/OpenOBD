//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_MONITORSTATUS_H
#define OPEN_OBD2_MONITORSTATUS_H

#include "../DataObject.h"
#include "Engine.h"
#include "../OBDTest.h"



class MonitorStatus{
private:
    /**
     * Off or On, indicates if the CEL/MIL is on (or should be on)
     * * Byte A7
     */
    DataObject<bool> *mil = new DataObject<bool>(A, (byte)7);

    /**
     * Number of confirmed emissions-related DTCs available for display.
     * Byte A6-A0
     */
    DataObject<unsigned int> *dtcCount = new DataObject<unsigned int>(A,(byte)6, A,(byte)0);


    /**
     * Defines which engine type the vehicle has
     */
    Engine* engine;


    OBDTest *components = new OBDTest("Components", B,(byte)2,B,(byte)6);
    OBDTest *fuelSystem = new OBDTest("FuelSystem", B,(byte)1,B,(byte)5);
    OBDTest *misfire = new OBDTest("Misfire", B,(byte)0,B,(byte)4);

public:
    explicit MonitorStatus(Engine* engine);

    /**
     * Converts this object into frame data.
     * @return Byte array representing the monitoring status
     */
    byte* toFrame();

    /**
     * Update the status with frame data.
     * @param frame The frame data.
     */
    void fromFrame(byte *frame, int size);


    bool getMil();
    void setMil(bool value);

    unsigned int getDtcCount();
    void setDtcCount(unsigned int count);

    Engine* getEngine();

    OBDTest *getComponents();

    OBDTest *getFuelSystem();

    OBDTest *getMisfire();




};

#endif //OPEN_OBD2_MONITORSTATUS_H
