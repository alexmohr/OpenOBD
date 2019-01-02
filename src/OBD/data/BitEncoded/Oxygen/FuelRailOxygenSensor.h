//
// Created by me on 30/12/18.
//

#ifndef OPEN_OBD2_FUELRAILOXYGENSENSOR_H
#define OPEN_OBD2_FUELRAILOXYGENSENSOR_H

#include "../../dataObject/CalculatedDataObjectFactory.h"

class FuelRailOxygenSensor : public IFrameObject {
private:
    unique_ptr<CalculatedDataObject<unsigned short, float>> fuelAirEquivalenceRatio;
    unique_ptr<CalculatedDataObject<unsigned short, float>> voltage;

public:
    FuelRailOxygenSensor();

    CalculatedDataObject<unsigned short, float> &getFuelAirEquivalenceRatio();

    CalculatedDataObject<unsigned short, float> &getVoltage();

public:// IFrameObject

    unsigned int toFrame(unsigned int &data, unsigned int &size) override;

    void fromFrame(byte *data, int size) override;

    string getPrintableData() override;
};


#endif //OPEN_OBD2_FUELRAILOXYGENSENSOR_H
