//
// Created by me on 01/01/19.
//

#include "FuelSystemStates.h"


FuelSystemStates::FuelSystemStates() {
    fuelSystem1 = make_unique<DataObject<StateOfFuelSystem>>(A, 7, A, 0);
    fuelSystem2 = make_unique<DataObject<StateOfFuelSystem>>(B, 7, B, 0);
}

DataObject<StateOfFuelSystem> &FuelSystemStates::getFuelSystem1() {
    return *fuelSystem1;
}

DataObject<StateOfFuelSystem> &FuelSystemStates::getFuelSystem2() {
    return *fuelSystem2;
}

unsigned int FuelSystemStates::toFrame(unsigned int &data, unsigned int &size) {
    data = fuelSystem1->toFrame(data, size) |
           fuelSystem2->toFrame(data, size);
    return data;
}

void FuelSystemStates::fromFrame(byte *frame, int size) {
    fuelSystem1->fromFrame(frame, size);
    fuelSystem2->fromFrame(frame, size);
}

string FuelSystemStates::getPrintableData() {
    return "fuelSystem1: " + fuelSystem1->getPrintableData() +
            "\nfuelSystem2: " + fuelSystem2->getPrintableData();

}

void FuelSystemStates::setValueFromString(string data) {
    auto parts = splitString(const_cast<char *>(data.c_str()));
    if (2 > parts.size()) {
        LOG(ERROR) << "Insufficient parameter count expected 2";
    }

    fuelSystem1->setValueFromString(parts.at(0));
    fuelSystem2->setValueFromString(parts.at(1));
}

