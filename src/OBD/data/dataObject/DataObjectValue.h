#include <utility>

#include <utility>

#include <utility>

//
// Created by me on 09/02/19.
//

#ifndef OPEN_OBD2_DATAOBJECTVALUE_H
#define OPEN_OBD2_DATAOBJECTVALUE_H

#include <vector>
#include <memory>
#include <map>
#include "DataObjectDescription.h"

using namespace std;

class DataObjectValue {
private:
    double value;
    shared_ptr<DataObjectDescription> description;
    shared_ptr<map<string, string>> details;
public:
    DataObjectValue(double value, shared_ptr<DataObjectDescription> description) {
        this->description = std::move(description);
        this->value = value;
        details = make_shared<map<string, string>>();
    }

    double getValue() {
        return value;
    }

    shared_ptr<map<string, string>> getDetails() {
        return details;
    }

    const shared_ptr<DataObjectDescription> getDescription() {
        return description;
    };
};

class DataObjectValueCollection {
private:
    shared_ptr<vector<shared_ptr<DataObjectValue>>> values;

public:
    DataObjectValueCollection() {
        this->values = make_shared<vector<shared_ptr<DataObjectValue>>>();
    }

    DataObjectValueCollection(shared_ptr<DataObjectValue> description) : DataObjectValueCollection() {
        values->push_back(description);
    }

public:
    shared_ptr<vector<shared_ptr<DataObjectValue>>> getValues() {
        return values;
    }

    void merge(shared_ptr<DataObjectValueCollection> valueCollection) {
        for (const auto &value : *valueCollection->getValues()) {
            this->values->push_back(value);
        }
    }

    string to_string() {
        return "";
    }

};


#endif //OPEN_OBD2_DATAOBJECTVALUE_H
