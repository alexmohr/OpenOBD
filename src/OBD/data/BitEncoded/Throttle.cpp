//
// Created by me on 01/01/19.
//

#include "Throttle.h"

Throttle::Throttle() {
    relativeThrottlePosition = make_unique<CalculatedDataObject<byte, float>>(
            A, 7, A, 0, CalculatedValues::toPercent, CalculatedValues::fromPercent,
            unit_percent, 0, 100);

    throttlePosition = make_unique<CalculatedDataObject<byte, float>>(
            A, 7, A, 0, CalculatedValues::toPercent, CalculatedValues::fromPercent,
            unit_percent, 0.0f, 100.0);

}


CalculatedDataObject<byte, float> &Throttle::getRelativeThrottlePosition() {
    return *relativeThrottlePosition;
}

CalculatedDataObject<byte, float> &Throttle::getThrottlePosition() {
    return *throttlePosition;
}
