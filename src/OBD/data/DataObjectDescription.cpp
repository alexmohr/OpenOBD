#include <utility>

#include <utility>

//
// Created by me on 29/12/18.
//

#include "DataObjectDescription.h"

DataObjectDescription::DataObjectDescription(string unit, string desc) {
    this->unit = std::move(unit);
    this->description = std::move(desc);
}

string DataObjectDescription::getUnit() {
    return unit;
}

string DataObjectDescription::getDescription() {
    return description;
}
