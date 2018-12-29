//
// Created by me on 23/12/18.
//

#include "CalculatedValues.h"
#include "DataObject.h"
#include "../../common/conversion.h"

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

unsigned short CalculatedValues::to3A(byte val) {
    return (unsigned short) (3 * (unsigned short) val);
}

byte CalculatedValues::from3A(unsigned short val) {
    return (byte) (val / 3);
}

float CalculatedValues::to256APlusBDivided4(unsigned short val) {
    byte *bVal = ushortToByteArray(val);
    // (256A + B)/4
    return ((256.0f * (float) bVal[0] + (float) bVal[1]) / 4.0f);
}

unsigned short CalculatedValues::from256APlusBDivided4(float val) {
    // A = 1/256 (4 p - B)
    // B = 4 (p - 64 A)

    // A = B = 1/256 (4 p - B)=4 (p - 64 A)
    // Solve for B:
    // B = 65536 A - 1020 p
    // insert in A:
    // A = 1/256 (4 p - (65536 A - 1020 p))
    // solve for A:
    // A = (4 p)/257

    byte bVal[2];
    float a = ceil((4 * val) / 257);
    bVal[0] = (byte) (a);
    bVal[1] = (byte) ceil(4 * (val - 64 * a));

    return byteArrayToUShort(bVal);
}


float CalculatedValues::to256APlusBDivided100(unsigned short val) {
    byte *bVal = ushortToByteArray(val);
    // (256A + B)/100
    return ((256.0f * (float) bVal[0] + (float) bVal[1]) / 100.0f);
}

unsigned short CalculatedValues::from256APlusBDivided100(float val) {
    // A = 1/256 (100 p - B)
    // B = 100 p - 256 A
    // A = B = 1/256 (100 p - B)=100 p - 256 A
    // Solve for B:
    // B = 65536 A - 25500 p
    // Insert in A:
    // A =  1/256 (100 p - (65536 A - 25500 p))
    // Solve for A:
    // A = (100 p)/257


    byte bVal[2];
    float a = ceil((100 * val) / 257);
    bVal[0] = (byte) (a);
    bVal[1] = (byte) ceil(100 * val - 256 * a);

    return byteArrayToUShort(bVal);
}

float CalculatedValues::toADivided2Minus64(byte val) {
    return (((float) val / 2.0f) - 64);
}

byte CalculatedValues::fromADivided2Minus64(float val) {
    return (byte) (2 * (val + 64));
}

float CalculatedValues::toADivided200(byte val) {
    return (float) val / 200.0f;
}

byte CalculatedValues::fromADivided200(float val) {
    return (byte) (200 * val);
}

float CalculatedValues::to0_079_Times256APlusB(unsigned short val) {
    // 0.079(256A+B)}
    byte *bVal = ushortToByteArray(val);
    return (float) 0.079 * (256 * (int) bVal[0] + (int) bVal[1]);
}

unsigned short CalculatedValues::from0_079_Times256APlusB(float val) {
    // A = (125 p)/2528 - B/256
    // B = (1000 p)/79 - 256 A
    // A = B:
    // (125 p)/2528 - B/256 = (1000 p)/79 - 256 A
    // Solve for B:
    // B = 65536 A - (255000 p)/79
    // Insert in A
    // A = (125 p)/2528 - ( 65536 A - (255000 p)/79)/256
    // Solve for A
    // A = (1000 p)/20303
    double a = ((1000.0 * val) / 20303);
    byte bVal[2];
    bVal[0] = (byte) (a);
    bVal[1] = (byte) ceil((1000.0f * val) / 79.0f - 256 * a);
    return byteArrayToUShort(bVal);
}

unsigned int CalculatedValues::toUShortTimes10(unsigned short val) {
   return (unsigned int)val*10;
}

unsigned short CalculatedValues::fromUShortTimes10(unsigned int val) {
    return (unsigned short)(val/10);
}

