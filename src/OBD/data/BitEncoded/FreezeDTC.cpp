//
// Created by me on 21/12/18.
//

#include "FreezeDTC.h"


FreezeDTC::FreezeDTC(shared_ptr<map<int, DataTroubleCode>> dtcMap) {
    this->dtcMap = dtcMap;
    this->dataObj = make_unique<DataObject<unsigned short>>(A, 7, B, 0, unit_none, 0, 65535);

    dtcId = -1;
    fallbackDTC = make_unique<DataTroubleCode>();
    fallbackDTC->setDescription("Unknown DTC");
}

FreezeDTC::~FreezeDTC() {
    
}



unsigned int FreezeDTC::toFrame(unsigned int &data, int &size) {
    return dataObj->toFrame(data, size);
}

void FreezeDTC::fromFrame(byte *data, int size) {
    dataObj->fromFrame(data, size);
    setTroubleCode(dataObj->getValue());
}

void FreezeDTC::setValue(unsigned short value) {
    dataObj->setValue(value);
    setTroubleCode(dataObj->getValue());
}

void FreezeDTC::setTroubleCode(unsigned short val) {
    if (dtcMap->find(dataObj->getValue()) != dtcMap->end()) {
        dtcId = val;
    } else {
        fallbackDTC->setSaeId("0x" + to_string(val));
        dtcId = -1;
    }
}

DataTroubleCode FreezeDTC::getValue() {
    if (dtcId >= 0) {
        return dtcMap->at(dtcId);
    }
    return *fallbackDTC;
}

string FreezeDTC::getPrintableData() {
    DataTroubleCode dtc = getValue();

    return "FreezeDTC: " + dtc.getSaeId() +
           "\nDescription: " + dtc.getDescription();
}

DataObjectStateCollection FreezeDTC::setValueFromString(string data) {
    vector<string> parts;
    auto rs = DataObjectStateFactory::boundCheck(1, data, parts);
    if (rs.resultSet.empty()) {
        return rs;
    }

    DataTroubleCode dtc = getValue();

    bool found = false;
    // is it sae?
    if (data[0] == DataTroubleCode::DTC_PREFIX_POWERTRAIN ||
        data[0] == DataTroubleCode::DTC_PREFIX_CHASIS ||
        data[0] == DataTroubleCode::DTC_PREFIX_BODY ||
        data[0] == DataTroubleCode::DTC_PREFIX_NETWORK) {
        for (auto &d: *dtcMap) {
            if (d.second.getSaeId() == data) {
                dtcId = d.first;
                dataObj->setValue(d.first);
                found = true;
                break;
            }
        }
        if (!found) {
            dtcId = -1;
        }
    } else {
        dataObj->setValueFromString(data);
    }

    setTroubleCode(dataObj->getValue());
    DataObjectStateFactory::success(rs);
    return rs;
}

vector<DataObjectDescription *> FreezeDTC::getDescriptions() {
    return dataObj->getDescriptions();
}


