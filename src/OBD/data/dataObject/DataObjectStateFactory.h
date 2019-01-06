//
// Created by me on 05/01/19.
//

#ifndef OPEN_OBD2_DATAOBJECTERRORFACTORY_H
#define OPEN_OBD2_DATAOBJECTERRORFACTORY_H


#include "DataObjectState.h"
#include <string>
#include <vector>

class DataObjectStateFactory {
public:
    static DataObjectStateCollection boundCheck(int expected, string data, vector<string> &parts);

    static void merge(DataObjectStateCollection &a, const DataObjectStateCollection &b);

    static void success(DataObjectStateCollection &dosc);

};


#endif //OPEN_OBD2_DATAOBJECTERRORFACTORY_H
