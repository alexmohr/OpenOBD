//
// Created by me on 29/12/18.
//

#ifndef OPEN_OBD2_UNIT_H
#define OPEN_OBD2_UNIT_H

#include <string>
#include "DataObjectUnit.h"
#include "DataObjectDescriptionText.h"

using namespace std;


//template<class T>
class DataObjectDescription {
private:
    const DataObjectUnit *unit;
    string description;
    double min;
    double max;

public:
    DataObjectDescription(const DataObjectUnit &unit, double min, double max, const string &description) {
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

    double getMin() {
        return min;
    }

    double getMax() {
        return max;
    }
};


#endif //OPEN_OBD2_UNIT_H
