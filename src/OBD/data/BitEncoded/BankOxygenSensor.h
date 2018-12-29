//
// Created by me on 28/12/18.
//

#ifndef OPEN_OBD2_BANKOXYGENSENSOR_H
#define OPEN_OBD2_BANKOXYGENSENSOR_H

#include "../CalculatedDataObject.h"

class BankOxygenSensor {
private:
    unique_ptr<CalculatedDataObject<byte, float>> voltage;
    unique_ptr<CalculatedDataObject<byte, float>> shortTermFuelTrim;


public:
    explicit BankOxygenSensor();

    bool isSensorUsedInTrimCalc();

    CalculatedDataObject<byte, float> &getVoltage();

    CalculatedDataObject<byte, float> &getShortTermFuelTrim();

    unsigned int toFrame(unsigned int &data);

    void fromFrame(byte *data, int size);

};


#endif //OPEN_OBD2_BANKOXYGENSENSOR_H
