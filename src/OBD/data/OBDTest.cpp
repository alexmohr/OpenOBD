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
}

void OBDTest::fromFrame(byte *frame) {
    available->setValue(frame);
    incomplete->setValue(frame);
}
