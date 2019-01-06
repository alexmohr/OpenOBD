#include <memory>

//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_MONITORSTATUS_H
#define OPEN_OBD2_MONITORSTATUS_H

#include "../dataObject/DataObject.h"
#include "Engine.h"
#include "../OBDTest.h"
#include <memory>

using namespace std;


class MonitorStatus : public IFrameObject {
private:
    /**
     * Off or On, indicates if the CEL/MIL is on (or should be on)
     * * Byte A7
     */
    unique_ptr<DataObject<bool>> mil;

    /**
     * Number of confirmed emissions-related DTCs available for display.
     * Byte A6-A0
     */
    unique_ptr<DataObject<unsigned short>> dtcCount;


    /**
     * Defines which engine type the vehicle has
     */
    shared_ptr<Engine> engine;


    unique_ptr<OBDTest> components;
    unique_ptr<OBDTest> fuelSystem;
    unique_ptr<OBDTest> misfire;

public:
    explicit MonitorStatus(shared_ptr<Engine> *engine);


    bool getMil();

    void setMil(bool value);

    unsigned int getDtcCount();

    void setDtcCount(unsigned int count);

    Engine &getEngine();

    OBDTest &getComponents();

    OBDTest &getFuelSystem();

    OBDTest &getMisfire();

public:

    /**
     * Converts this object into frame data.
     */
    unsigned int toFrame(unsigned int &data, int &size) override;


    /**
     * Update the status with frame data.
     * @param frame The frame data.
     */
    void fromFrame(byte *frame, int size) override;

    string getPrintableData() override;

    DataObjectStateCollection setValueFromString(string data) override;

    vector<DataObjectDescription *> getDescriptions() override;
};

#endif //OPEN_OBD2_MONITORSTATUS_H
