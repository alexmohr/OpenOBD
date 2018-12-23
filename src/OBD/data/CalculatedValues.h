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
};


#endif //OPEN_OBD2_CALCULATEDVALUES_H
