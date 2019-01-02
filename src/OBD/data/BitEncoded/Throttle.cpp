//
// Created by me on 01/01/19.
//

#include "Throttle.h"

Throttle::Throttle() {
    relativeThrottlePosition = CalculatedDataObjectFactory::percent();
    throttlePosition =  CalculatedDataObjectFactory::percent();
}


CalculatedDataObject<byte, float> &Throttle::getRelativeThrottlePosition() {
    return *relativeThrottlePosition;
}

CalculatedDataObject<byte, float> &Throttle::getThrottlePosition() {
    return *throttlePosition;
}
