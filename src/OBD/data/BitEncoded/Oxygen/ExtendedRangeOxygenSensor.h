//
// Created by me on 30/12/18.
//

#ifndef OPEN_OBD2_EXTENDEDRANGEOXYGENSENSOR_H
#define OPEN_OBD2_EXTENDEDRANGEOXYGENSENSOR_H

#include "../../dataObject/CalculatedDataObject.h"

class ExtendedRangeOxygenSensor : public IFrameObject {
private:
    unique_ptr<CalculatedDataObject<unsigned short, float>> fuelAirEquivalenceRatio;
    unique_ptr<CalculatedDataObject<unsigned short, float>> current;
public:
    ExtendedRangeOxygenSensor();

    CalculatedDataObject<unsigned short, float> &getFuelAirEquivalenceRatio();

    CalculatedDataObject<unsigned short, float> &getCurrent();

public:// IFrameObject

    void fromFrame(byte *frame, int size) override;

    unsigned int toFrame(unsigned int &data) override;

    string getPrintableData() override;
};


#endif //OPEN_OBD2_EXTENDEDRANGEOXYGENSENSOR_H
