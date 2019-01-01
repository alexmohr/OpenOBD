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

unsigned int FuelSystemStates::toFrame(unsigned int &data) {
    data = fuelSystem1->toFrame(data) |
           fuelSystem2->toFrame(data);
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

