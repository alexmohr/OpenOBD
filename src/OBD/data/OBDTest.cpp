#include <utility>

//
// Created by me on 13/12/18.
//

#include "OBDTest.h"


OBDTest::OBDTest(string name, ByteIndex availableByte, byte availableIndex, ByteIndex incompleteByte,
                 byte incompleteIndex) {
    this->name = std::move(name);
    this->available = new DataObject<bool>(availableByte, availableIndex);
    this->incomplete = new DataObject<bool>(incompleteByte, incompleteIndex);
    available->setValue(false);
}


OBDTest::~OBDTest() {
    delete available;
    delete incomplete;
}


void OBDTest::fromFrame(byte *frame, int size) {
    available->fromFrame(frame, size);
    incomplete->fromFrame(frame, size);
}

unsigned int OBDTest::toFrame(unsigned int &data) {
    return data |= available->toFrame(data) |
                   incomplete->toFrame(data);
}

void OBDTest::setName(string name) {
    this->name = name;
}

DataObject<bool> *OBDTest::getAvailable() {
    return available;
}

DataObject<bool> *OBDTest::getIncomplete() {
    return incomplete;
}
