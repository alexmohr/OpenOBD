//
// Created by me on 01/01/19.
//

#include "Throttle.h"

Throttle::Throttle() {
    relativeThrottlePosition = CalculatedDataObjectFactory::percent(
            DataObjectDescriptionText::getRelativeThrottlePosition());
    throttlePosition = CalculatedDataObjectFactory::percent(
            DataObjectDescriptionText::getThrottlePosition());
    absoluteThrottlePositionB = CalculatedDataObjectFactory::percent(
            DataObjectDescriptionText::getAbsoluteThrottlePosition("B"));
    absoluteThrottlePositionC = CalculatedDataObjectFactory::percent(
            DataObjectDescriptionText::getAbsoluteThrottlePosition("C"));
    acceleratorPedalPositionD = CalculatedDataObjectFactory::percent(
            DataObjectDescriptionText::getAbsoluteThrottlePosition("D"));
    acceleratorPedalPositionE = CalculatedDataObjectFactory::percent(
            DataObjectDescriptionText::getAbsoluteThrottlePosition("E"));
    acceleratorPedalPositionF = CalculatedDataObjectFactory::percent(
            DataObjectDescriptionText::getAbsoluteThrottlePosition("F"));

    commandedThrottleActuator = CalculatedDataObjectFactory::percent(
            DataObjectDescriptionText::getCommandedThrottleActuator());
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

CalculatedDataObject<byte, float> &Throttle::getCommandedThrottleActuator() {
    return *commandedThrottleActuator;
}
