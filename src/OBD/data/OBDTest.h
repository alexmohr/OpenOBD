//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_OBDTEST_H
#define OPEN_OBD2_OBDTEST_H

#include <string>
#include "DataObject.h"

using namespace std;


class OBDTest {
public:
    DataObject<bool> Available;
    DataObject<bool> Incomplete;
    string name;

    OBDTest(string name,
            BYTE availableByte, BYTE availableIndex,
            BYTE incompleteByte, BYTE incompleteIndex);
};


#endif //OPEN_OBD2_OBDTEST_H
