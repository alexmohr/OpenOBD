//
// Created by me on 23/12/18.
//

#ifndef OPEN_OBD2_CALCULATEDVALUES_H
#define OPEN_OBD2_CALCULATEDVALUES_H

#include <cstddef>

using namespace std;

class CalculatedValues {
public:
    static float toPercent(byte val);

    static byte fromPercent(float val);

    static float toPercent128Minus100(byte val);

    static byte fromPercent128Minus100(float val);

    static short toAMinus40(byte val);

    static byte fromAMinus40(short val);

    static unsigned short to3A(byte val);

    static byte from3A(unsigned short val);

    static float to256APlusBDivided4(unsigned short val);

    static unsigned short from256APlusBDivided4(float val);

    static float to256APlusBDivided100(unsigned short val);

    static unsigned short from256APlusBDivided100(float val);

    static float toADivided2Minus64(byte val);

    static byte fromADivided2Minus64(float val);
};


#endif //OPEN_OBD2_CALCULATEDVALUES_H
