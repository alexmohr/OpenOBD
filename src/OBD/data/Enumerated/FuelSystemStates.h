//
// Created by me on 01/01/19.
//

#ifndef OPEN_OBD2_FUELSYSTEMSTATES_H
#define OPEN_OBD2_FUELSYSTEMSTATES_H


#include "StateOfFuelSystem.h"
#include "../dataObject/DataObject.h"

class FuelSystemStates : public IFrameObject {
private:
    unique_ptr<DataObject<StateOfFuelSystem>> fuelSystem1;
    unique_ptr<DataObject<StateOfFuelSystem>> fuelSystem2;
public:
    FuelSystemStates();

    DataObject<StateOfFuelSystem> &getFuelSystem1();

    DataObject<StateOfFuelSystem> &getFuelSystem2();

public:
    unsigned int toFrame(unsigned int &data, unsigned int &size) override;

    void fromFrame(byte *frame, int size) override;

    string getPrintableData() override;

};


#endif //OPEN_OBD2_FUELSYSTEMSTATES_H
