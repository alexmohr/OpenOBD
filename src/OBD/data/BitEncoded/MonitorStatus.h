#include <memory>

//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_MONITORSTATUS_H
#define OPEN_OBD2_MONITORSTATUS_H

#include "../DataObject.h"
#include "Engine.h"
#include "../OBDTest.h"
#include <memory>

using namespace std;


class MonitorStatus{
private:
    /**
     * Off or On, indicates if the CEL/MIL is on (or should be on)
     * * Byte A7
     */
    unique_ptr<DataObject<bool>> mil = make_unique<DataObject<bool>>(A, 7);

    /**
     * Number of confirmed emissions-related DTCs available for display.
     * Byte A6-A0
     */
    unique_ptr<DataObject<unsigned int>> dtcCount = make_unique<DataObject<unsigned int>>(A, 6, A, 0);


    /**
     * Defines which engine type the vehicle has
     */
    shared_ptr<Engine> engine;


    unique_ptr<OBDTest> components = make_unique<OBDTest>("Components", B, 2, B, 6);
    unique_ptr<OBDTest> fuelSystem = make_unique<OBDTest>("FuelSystem", B, 1, B, 5);
    unique_ptr<OBDTest> misfire = make_unique<OBDTest>("Misfire", B, 0, B, 4);

public:
    explicit MonitorStatus(shared_ptr<Engine> engine);

    /**
     * Converts this object into frame data.
     */
    unsigned int toFrame();

    /**
     * Update the status with frame data.
     * @param frame The frame data.
     */
    void fromFrame(byte *frame, int size);


    bool getMil();

    void setMil(bool value);

    unsigned int getDtcCount();

    void setDtcCount(unsigned int count);

    Engine &getEngine();

    OBDTest &getComponents();

    OBDTest &getFuelSystem();

    OBDTest &getMisfire();
};

#endif //OPEN_OBD2_MONITORSTATUS_H
