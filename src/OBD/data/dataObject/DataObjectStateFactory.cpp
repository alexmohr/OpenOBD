//
// Created by me on 05/01/19.
//

#include "DataObjectStateFactory.h"
#include "../../../common/conversion.h"

DataObjectStateCollection DataObjectStateFactory::boundCheck(
        int expected, string data, vector<string> &parts) {

    parts = splitString(const_cast<char *>(data.c_str()));
    DataObjectStateCollection rs = DataObjectStateCollection();
    if (expected > parts.size()) {
        rs.resultSet.emplace_back(ErrorType::MISSING_ARGUMENTS, expected, parts.size());
    }

    return rs;
}

void DataObjectStateFactory::merge(DataObjectStateCollection &a, const DataObjectStateCollection &b) {
    a.resultSet.insert(a.resultSet.end(), b.resultSet.begin(), b.resultSet.end());
}

void DataObjectStateFactory::success(DataObjectStateCollection &dosc) {
    dosc.resultSet.emplace_back();
}

