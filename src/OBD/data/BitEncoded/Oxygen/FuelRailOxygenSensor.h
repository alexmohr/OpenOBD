//
// Created by me on 30/12/18.
//

#ifndef OPEN_OBD2_FUELRAILOXYGENSENSOR_H
#define OPEN_OBD2_FUELRAILOXYGENSENSOR_H

#include "../../dataObject/CalculatedDataObject.h"

class FuelRailOxygenSensor {
private:
    unique_ptr<CalculatedDataObject<unsigned short, float>> fuelAirEquivalenceRatio;
    unique_ptr<CalculatedDataObject<unsigned short, float>> voltage;

public:
    FuelRailOxygenSensor();

    CalculatedDataObject<unsigned short, float> &getFuelAirEquivalenceRatio();

    CalculatedDataObject<unsigned short, float> &getVoltage();

    unsigned int toFrame(unsigned int &data);

    void fromFrame(byte *data, int size);
};


#endif //OPEN_OBD2_FUELRAILOXYGENSENSOR_H
