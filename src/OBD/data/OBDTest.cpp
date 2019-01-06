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

DataObjectStateCollection OBDTest::setValueFromString(string data) {
    vector<string> parts;
    auto rs = DataObjectStateFactory::boundCheck(2, data, parts);
    if (rs.resultSet.empty()) {
        DataObjectStateFactory::merge(rs, available->setValueFromString(parts.at(0)));
        DataObjectStateFactory::merge(rs, incomplete->setValueFromString(parts.at(1)));
    } else {
        rs.msg = "Expected 2 values. Available, Incomplete";
    }

    return rs;
}

vector<DataObjectDescription *> OBDTest::getDescriptions() {
    return vector<DataObjectDescription *>{available->getDescriptions().at(0), incomplete->getDescriptions().at(0)};
}

