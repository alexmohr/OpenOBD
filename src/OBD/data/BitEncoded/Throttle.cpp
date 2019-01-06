//
// Created by me on 01/01/19.
//

#include "Throttle.h"

Throttle::Throttle() {
    relativeThrottlePosition = CalculatedDataObjectFactory::percent();
    throttlePosition =  CalculatedDataObjectFactory::percent();
    absoluteThrottlePositionB = CalculatedDataObjectFactory::percent();
    absoluteThrottlePositionC = CalculatedDataObjectFactory::percent();
    acceleratorPedalPositionD = CalculatedDataObjectFactory::percent();
    acceleratorPedalPositionE = CalculatedDataObjectFactory::percent();
    acceleratorPedalPositionF = CalculatedDataObjectFactory::percent();
}


CalculatedDataObject<byte, float> &Throttle::getRelativeThrottlePosition() {
    return *relativeThrottlePosition;
}

CalculatedDataObject<byte, float> &Throttle::getThrottlePosition() {
    return *throttlePosition;
}

CalculatedDataObject<byte, float> &Throttle::getAbsoluteThrottlePositionB() {
    return *absoluteThrottlePositionB;
}

CalculatedDataObject<byte, float> &Throttle::getAbsoluteThrottlePositionC() {
    return *absoluteThrottlePositionC;
}

CalculatedDataObject<byte, float> &Throttle::getAcceleratorPedalPositionD() {
    return *acceleratorPedalPositionD;
}

CalculatedDataObject<byte, float> &Throttle::getAcceleratorPedalPositionE() {
    return *acceleratorPedalPositionE;
}

CalculatedDataObject<byte, float> &Throttle::getAcceleratorPedalPositionF() {
    return *acceleratorPedalPositionF;
}