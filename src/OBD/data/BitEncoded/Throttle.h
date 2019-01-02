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

public:
    Throttle();

    CalculatedDataObject<byte, float> &getRelativeThrottlePosition();


    CalculatedDataObject<byte, float> &getThrottlePosition();

};


#endif //OPEN_OBD2_THROTTLE_H
