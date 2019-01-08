#//
// Created by me on 05/01/19.
//

#ifndef OPEN_OBD2_STRINGSETRESULT_H
#define OPEN_OBD2_STRINGSETRESULT_H

#include <vector>
#include <string>

using namespace std;

enum ErrorType {
    SUCCESS = 0,
    TOO_LARGE = 2,
    TOO_SMALL = 4,
    INVALID_NUMBER = 8,
    MISSING_ARGUMENTS = 16,
    NOT_SUPPORTED = 32,
    DATA_ERROR = 64,
    TIMEOUT = 128,
};


struct DataObjectState {
    ErrorType type;
    double min;
    double max;
    double count;
    double expectedCount;
    double value;

    DataObjectState() {
        this->type = SUCCESS;
        this->min = 0;
        this->max = 0;
        this->count = 0;
        this->expectedCount = 0;
    }

    DataObjectState(ErrorType type) : DataObjectState() {
        this->type = type;
    }

    DataObjectState(ErrorType type, double d1, double d2) : DataObjectState() {
        this->type = type;
        if (type == MISSING_ARGUMENTS) {
            this->expectedCount = d1;
            this->count = d2;
        } else if (type == TOO_LARGE) {
            this->max = d1;
            this->value = d2;
        } else if (type == TOO_SMALL) {
            this->min = d1;
            this->value = d2;
        }
    }

};

class DataObjectStateCollection {

public:
    DataObjectStateCollection() {
        resultSet = vector<DataObjectState>();
    }

public:
    vector<DataObjectState> resultSet;
    string msg;
};


#endif //OPEN_OBD2_STRINGSETRESULT_H
