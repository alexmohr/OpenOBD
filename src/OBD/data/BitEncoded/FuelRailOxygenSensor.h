//
// Created by me on 30/12/18.
//

#ifndef OPEN_OBD2_FUELRAILOXYGENSENSOR_H
#define OPEN_OBD2_FUELRAILOXYGENSENSOR_H

#include "../dataObject/CalculatedDataObject.h"

class FuelRailOxygenSensor {
private:
    unique_ptr<CalculatedDataObject<byte, float>> fuelAirEquivalenceRatio;
    unique_ptr<CalculatedDataObject<byte, float>> voltage;

public:
    explicit FuelRailOxygenSensor();
};


#endif //OPEN_OBD2_FUELRAILOXYGENSENSOR_H
