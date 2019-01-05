//
// Created by me on 29/12/18.
//

#ifndef OPEN_OBD2_UNIT_H
#define OPEN_OBD2_UNIT_H

#include <string>
#include "DataObjectUnit.h"
#include "DataObjectDescriptionText.h"

using namespace std;

enum DataObjectDescriptionErrors {
    TOO_LARGE = 1,
    TOO_SMALL = 2
};


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

    int checkBounds(double value) {
        if (value < getMin()) {
            LOG(ERROR) << "value is too small: " << value << ", min value is: " << min;
            return TOO_SMALL;
        } else if (value > getMax()) {
            LOG(ERROR) << "value is too large: " << value << ", max value is: " << max;
            return TOO_LARGE;
        }

        return 0;
    }
};


#endif //OPEN_OBD2_UNIT_H
