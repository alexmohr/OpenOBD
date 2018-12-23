//
// Created by me on 23/12/18.
//

#include "CalculatedValues.h"

float CalculatedValues::toPercent(byte val) {
    return (float) (100.0 / 255.0 * (int) val);
}

byte CalculatedValues::fromPercent(float val) {
    return (byte) ((val * 255) / 100);
}
