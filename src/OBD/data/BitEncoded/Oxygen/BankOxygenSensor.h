//
// Created by me on 28/12/18.
//

#ifndef OPEN_OBD2_BANKOXYGENSENSOR_H
#define OPEN_OBD2_BANKOXYGENSENSOR_H

#include "../../dataObject/CalculatedDataObject.h"

class BankOxygenSensor : public IFrameObject {
private:
    unique_ptr<CalculatedDataObject<byte, float>> voltage;
    unique_ptr<CalculatedDataObject<byte, float>> shortTermFuelTrim;


public:
    explicit BankOxygenSensor();

    bool isSensorUsedInTrimCalc();

    CalculatedDataObject<byte, float> &getVoltage();

    CalculatedDataObject<byte, float> &getShortTermFuelTrim();

public: // IFrameObject
    unsigned int toFrame(unsigned int &data) override;

    void fromFrame(byte *data, int size) override;

    string getPrintableData() override;

};


#endif //OPEN_OBD2_BANKOXYGENSENSOR_H
