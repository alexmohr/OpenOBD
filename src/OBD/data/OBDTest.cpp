#include <utility>

//
// Created by me on 13/12/18.
//

#include "OBDTest.h"


OBDTest::OBDTest(string name, ByteIndex availableByte, unsigned int availableIndex, ByteIndex incompleteByte,
                 unsigned int incompleteIndex) {
    this->name = std::move(name);
    string description = DataObjectDescriptionText::OBDTest + this->name;
    this->available = make_unique<DataObject<bool>>(availableByte, availableIndex,
                                                    description + DataObjectDescriptionText::OBDTestAvailable);
    this->incomplete = make_unique<DataObject<bool>>(incompleteByte, incompleteIndex,
                                                     DataObjectDescriptionText::OBDTestIncomplete);
    available->setValue(false);
}


OBDTest::~OBDTest() = default;


void OBDTest::fromFrame(byte *frame, int size) {
    available->fromFrame(frame, size);
    incomplete->fromFrame(frame, size);
}

unsigned int OBDTest::toFrame(unsigned int &data, int &size) {
    return data |= available->toFrame(data, size) |
                   incomplete->toFrame(data, size);
}

void OBDTest::setName(string name) {
    this->name = name;
}

DataObject<bool> &OBDTest::getAvailable() {
    return *available;
}

DataObject<bool> &OBDTest::getIncomplete() {
    return *incomplete;
}

string OBDTest::getPrintableData() {
    return "OBDTest: " + name +
           "\nAvailable: " + available->getPrintableData() +
           "\nIncomplete: " + incomplete->getPrintableData();
}

void OBDTest::setValueFromString(string data) {
    auto parts = splitString(const_cast<char *>(data.c_str()));
    if (2 > parts.size()) {
        LOG(ERROR) << "Insufficient parameter count";
    }

    available->setValueFromString(parts.at(0));
    incomplete->setValueFromString(parts.at(1));
}

