//
// Created by me on 08/01/19.
//

#include "../../../../common/endian.h"
#include "SupportedPidCollection.h"

SupportedPidCollection::SupportedPidCollection() {
    supportedPids = make_unique<vector<DataObject<bool>>>();
    int i;
    for (i = 7; i >= 0; i--) {
        supportedPids->emplace_back(A, i, DataObjectDescriptionText::getPidSupported());
    }
    for (i = 7; i >= 0; i--) {
        supportedPids->emplace_back(B, i, DataObjectDescriptionText::getPidSupported());
    }
    for (i = 7; i >= 0; i--) {
        supportedPids->emplace_back(C, i, DataObjectDescriptionText::getPidSupported());
    }
    for (i = 7; i >= 0; i--) {
        supportedPids->emplace_back(D, i, DataObjectDescriptionText::getPidSupported());
    }
    for (auto &pid  : *supportedPids) {
        pid.setValue(false);
    }
}


vector<DataObject<bool>> &SupportedPidCollection::getSupportedPids() {
    return *supportedPids;
}


vector<DataObjectDescription *> SupportedPidCollection::getDescriptions() {
    auto desc = vector<DataObjectDescription *>();
    for (auto &dd : *supportedPids) {
        for (auto &d : dd.getDescriptions()) {
            desc.push_back(d);
        }
    }
    return desc;
}

unsigned int SupportedPidCollection::toFrame(unsigned int &data, int &size) {
    for (auto &pid : *supportedPids) {
        data |= pid.toFrame(data, size);
    }
    return data;
}

void SupportedPidCollection::fromFrame(byte *data, int size) {
    for (auto &pid: *supportedPids) {
        pid.fromFrame(data, size);
    }
}

shared_ptr<DataObjectValueCollection> SupportedPidCollection::getDataObjectValue() {
    auto valueCollection = make_shared<DataObjectValueCollection>();

    for (auto &pid : *supportedPids) {
        valueCollection->merge(pid.getDataObjectValue());
    }
    return valueCollection;
}

DataObjectStateCollection SupportedPidCollection::setValueFromString(string data) {
    vector<string> parts;
    auto rs = DataObjectStateFactory::boundCheck(32, data, parts);
    if (!rs.resultSet.empty()) {
        return rs;
    }

    int i;
    for (i = 0; i < (int) supportedPids->size(); i++) {
        DataObjectStateFactory::merge(rs, supportedPids->at(i).setValueFromString(parts.at(i)));
    }

    return rs;
}
