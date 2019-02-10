//
// Created by me on 23/12/18.
//

#include "CalculatedValues.h"
#include "DataObject.h"
#include "../../../common/conversion.h"

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
    return (float) val / 4.0f;
}

unsigned short CalculatedValues::from256APlusBDivided4(float val) {
    return (unsigned short) (val * 4);
}


float CalculatedValues::to256APlusBDivided100(unsigned short val) {
    // (256A + B)/100
    return ((float) val / 100.0f);
}

unsigned short CalculatedValues::from256APlusBDivided100(float val) {
    return (unsigned short) (val * 100);
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
    auto retVal = (float) (0.079 * (256 * (int) bVal[0] + (int) bVal[1]));
    delete[] bVal;
    return retVal;
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
    bVal[1] = (byte) ((1000.0f * val) / 79.0f - 256 * a);
    return byteArrayToUShort(bVal);
}

unsigned int CalculatedValues::toUShortTimes10(unsigned short val) {
    return (unsigned int) val * 10;
}

unsigned short CalculatedValues::fromUShortTimes10(unsigned int val) {
    return (unsigned short) (val / 10);
}


float CalculatedValues::to2Divided65536Times256PlusB(unsigned short val) {
    return 2.0f / 65536 * (val);
}


unsigned short CalculatedValues::from2Divided65536Times256PlusB(float val) {
    return (unsigned short) (32768 * val);
}

float CalculatedValues::to8Divided65536Times256PlusB(unsigned short val) {
    return 8.0f / 65536 * (val);
}

unsigned short CalculatedValues::from8Divided65536Times256PlusB(float val) {
    return (unsigned short) (8192 * val);
}


float CalculatedValues::to256APlusBDivided4TwoComplement(unsigned short val) {
    return getTwoComplement(val) / 4.0f;
}

unsigned short CalculatedValues::from256APlusBDivided4TwoComplement(float val) {
    auto ival = (unsigned short) (val * 4);
    return static_cast<unsigned short>(getTwoComplement(ival));
}

float CalculatedValues::toAPlusBDivided256Minus128(unsigned short val) {
    byte *bVal = ushortToByteArray(val);
    float value = (float) (bVal[0]) + ((float) bVal[1] / 256) - 128;
    delete[] bVal;
    return value;

}

unsigned short CalculatedValues::fromAPlusBDivided256Minus128(float val) {
    // p=A+(B/256)-128
    // A = -B/256 + p + 128
    // B = -256 (A - p - 128)
    // A = B
    // -B/256 + p + 128= -256 (A - p - 128)
    // Solve for B
    // B = 256 (256 A - 255 (p + 128))
    // Insert into A
    // A = -(256 (256 A - 255 (p + 128)))/256 + p + 128
    // A = (256 (p + 128))/257
    // B = -256 (((256 (p + 128))/257) - p - 128)
    // B = (256 (p + 128))/257
    byte bVal[2];
    bVal[0] = (byte) ((256 * (val + 128)) / 257);
    bVal[1] = (byte) ((256 * (val + 128)) / 257);
    return byteArrayToUShort(bVal);
}


float CalculatedValues::to256APlusBDivided10Minus40(unsigned short val) {
    return ((float) val / 10) - 40;
}


unsigned short CalculatedValues::from256APlusBDivided10Minus40(float val) {
    return static_cast<unsigned short>(10 * (val + 40));

}

float CalculatedValues::to256APlusBDivided1000(unsigned short val) {
    return (float) val / 1000;
}

unsigned short CalculatedValues::from256APlusBDivided1000(float val) {
    return (unsigned short) (val * 1000);
}

unsigned short CalculatedValues::to100Divided255Times256APlusB(unsigned short val) {
    return static_cast<unsigned short>(val * (100.0f / 255.0f));
}

unsigned short CalculatedValues::from100Divided255Times256APlusB(unsigned short val) {
    return static_cast<unsigned short>((51 * val) / 20.0f);

}



