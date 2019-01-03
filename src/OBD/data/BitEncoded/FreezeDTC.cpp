//
// Created by me on 21/12/18.
//

#include "FreezeDTC.h"


FreezeDTC::FreezeDTC(shared_ptr<map<int, DataTroubleCode>> dtcMap) {
    this->dtcMap = dtcMap;
    this->dtc = nullptr;
    this->dataObj = make_unique<DataObject<unsigned short>>(A, 7, B, 0, unit_none, 0, 65535);
}

FreezeDTC::~FreezeDTC() {
    delete dtc;
}

unsigned int FreezeDTC::toFrame(unsigned int &data, unsigned int &size) {
    return dataObj->toFrame(data, size);
}

void FreezeDTC::fromFrame(byte *data, int size) {
    dataObj->fromFrame(data, size);
    dtc = &dtcMap->at(dataObj->getValue());
}

void FreezeDTC::setValue(unsigned short value) {
    dataObj->setValue(value);
    dtc = &dtcMap->at(dataObj->getValue());
}

DataTroubleCode FreezeDTC::getValue() {
    return *dtc;
}

string FreezeDTC::getPrintableData() {
    return "FreezeDTC :" + dataObj->getPrintableData();
}

void FreezeDTC::setValueFromString(string data) {
    auto parts = splitString(const_cast<char *>(data.c_str()));
    if (parts.empty()) {
        LOG(ERROR) << "Insufficient parameter count expected 1";
    }

    dataObj->setValueFromString(data);
}


