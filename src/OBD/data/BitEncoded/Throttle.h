//
// Created by me on 01/01/19.
//

#ifndef OPEN_OBD2_THROTTLE_H
#define OPEN_OBD2_THROTTLE_H

#include "../dataObject/CalculatedDataObjectFactory.h"

class Throttle {
private:
    unique_ptr<CalculatedDataObject<byte, float>> relativeThrottlePosition;

    unique_ptr<CalculatedDataObject<byte, float>> throttlePosition;

    unique_ptr<CalculatedDataObject<byte, float>> absoluteThrottlePositionB;
    unique_ptr<CalculatedDataObject<byte, float>> absoluteThrottlePositionC;
    unique_ptr<CalculatedDataObject<byte, float>> acceleratorPedalPositionD;
    unique_ptr<CalculatedDataObject<byte, float>> acceleratorPedalPositionE;
    unique_ptr<CalculatedDataObject<byte, float>> acceleratorPedalPositionF;
    unique_ptr<CalculatedDataObject<byte, float>> commandedThrottleActuator;


public:
    Throttle();

    CalculatedDataObject<byte, float> &getRelativeThrottlePosition();


    CalculatedDataObject<byte, float> &getThrottlePosition();

    CalculatedDataObject<byte, float> &getAbsoluteThrottlePositionB();

    CalculatedDataObject<byte, float> &getAbsoluteThrottlePositionC();

    CalculatedDataObject<byte, float> &getAcceleratorPedalPositionD();

    CalculatedDataObject<byte, float> &getAcceleratorPedalPositionE();

    CalculatedDataObject<byte, float> &getAcceleratorPedalPositionF();

    CalculatedDataObject<byte, float> &getCommandedThrottleActuator();


};


#endif //OPEN_OBD2_THROTTLE_H
