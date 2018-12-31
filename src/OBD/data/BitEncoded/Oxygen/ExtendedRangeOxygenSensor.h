//
// Created by me on 30/12/18.
//

#ifndef OPEN_OBD2_EXTENDEDRANGEOXYGENSENSOR_H
#define OPEN_OBD2_EXTENDEDRANGEOXYGENSENSOR_H

#include "../../dataObject/CalculatedDataObject.h"

class ExtendedRangeOxygenSensor {
private:
    unique_ptr<CalculatedDataObject<unsigned short, float>> fuelAirEquivalenceRatio;
    unique_ptr<CalculatedDataObject<unsigned short, float>> current;
public:
    ExtendedRangeOxygenSensor();

    CalculatedDataObject<unsigned short, float> &getFuelAirEquivalenceRatio();

    CalculatedDataObject<unsigned short, float> &getCurrent();

    void fromFrame(byte *frame, int size);

    unsigned int toFrame(unsigned int &data);
};


#endif //OPEN_OBD2_EXTENDEDRANGEOXYGENSENSOR_H
