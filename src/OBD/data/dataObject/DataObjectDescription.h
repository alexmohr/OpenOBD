//
// Created by me on 29/12/18.
//

#ifndef OPEN_OBD2_UNIT_H
#define OPEN_OBD2_UNIT_H

#include <string>
#include "DataObjectUnit.h"
#include "DataObjectDescriptionText.h"
#include "DataObjectState.h"

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

    const string &getDescriptionText() {
        return description;
    }

    void setDescription(string description) {
        this->description = move(description);
    }

    double getMin() {
        return min;
    }

    double getMax() {
        return max;
    }

    DataObjectState checkBounds(double value) {
        DataObjectState state = DataObjectState();
        if (value < getMin()) {
            state.min = getMin();
            state.value = value;
            state.type = TOO_SMALL;
        } else if (value > getMax()) {
            state.max = getMax();
            state.value = value;
            state.type = TOO_LARGE;
        }

        return state;
    }
};


#endif //OPEN_OBD2_UNIT_H
