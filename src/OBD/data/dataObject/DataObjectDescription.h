//
// Created by me on 29/12/18.
//

#ifndef OPEN_OBD2_UNIT_H
#define OPEN_OBD2_UNIT_H

#include <string>
#include "DataObjectUnit.h"
#include "DataObjectDescriptionText.h"

using namespace std;


template<class T>
class DataObjectDescription {
private:
    const DataObjectUnit *unit;
    string description;
    T min;
    T max;

public:
    DataObjectDescription(const DataObjectUnit &unit, T min, T max, const string &description) {
        this->unit = &unit;
        this->min = min;
        this->max = max;
        this->description = description;
    }

    const DataObjectUnit &getUnit() {
        return *unit;
    }

    const string &getDescription() {
        return description;
    }

    T getMin() {
        return min;
    }

    T getMax() {
        return max;
    }
};


#endif //OPEN_OBD2_UNIT_H
