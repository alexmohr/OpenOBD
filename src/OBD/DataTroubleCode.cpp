#include <utility>

//
// Created by me on 18/12/18.
//


#include <algorithm>
#include <string>
#include <sstream>
#include "DataTroubleCode.h"


DataTroubleCode::DataTroubleCode() {
    canId = 0;
}


unsigned int DataTroubleCode::getCanId() {
    if (0 == canId) {
        canId = convertSaeIdToCan(saeId);
    }

    return canId;
}

unsigned int DataTroubleCode::convertSaeIdToCan(string id) {

    if (3 > id.size()) {
        return MAX_CAN_ID_EXTENDED + 1;
    }

    // convert to upper case
    transform(id.begin(), id.end(), id.begin(), ::toupper);

    const char system = id[0];
    unsigned int offset = convertHexToInt(id.substr(1, 1));

    if (PREFIX_POWERTRAIN == system) {
        offset += CAN_OFFSET_POWERTRAIN;
    } else if (PREFIX_CHASIS == system) {
        offset += CAN_OFFSET_CHASIS;
    } else if (PREFIX_BODY == system) {
        offset += CAN_OFFSET_BODY;
    } else if (PREFIX_NETWORK == system) {
        offset += CAN_OFFSET_NETWORK;
    } else {
        // invalid id
        return MAX_CAN_ID_EXTENDED + 1;
    }

    string hexId = convertIntToHex(offset) + id.substr(2, id.size() - 1);
    unsigned int canId = convertHexToInt(hexId);
    return canId;
}

string DataTroubleCode::convertIntToHex(unsigned int n) {
    stringstream stream;
    stream << hex << n;
    string result = stream.str();
    return result;
}

unsigned int DataTroubleCode::convertHexToInt(string hex) {
    return static_cast<unsigned int>(strtoul(hex.c_str(), nullptr, 16));
}

void DataTroubleCode::setSaeId(string saeId) {
    canId = 0;
    this->saeId = std::move(saeId);
}

void DataTroubleCode::setDescription(string description) {
    this->description = std::move(description);
}

string DataTroubleCode::getSaeId() {
    return saeId;
}

string DataTroubleCode::getDescription() {
    return description;
}

