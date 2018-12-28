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

float CalculatedValues::toPercent128Minus100(byte val) {
    return (float) ((100.0 / 128) * (int) val) - 100;
}

byte CalculatedValues::fromPercent128Minus100(float val) {
    return (byte) ((32 * (val + 100)) / 25);
}

short CalculatedValues::toAMinus40(byte val) {
    return (short) ((short) val - 40);
}

byte CalculatedValues::fromAMinus40(short val) {
    return (byte) (val + 40);
}

