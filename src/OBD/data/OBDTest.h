//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_OBDTEST_H
#define OPEN_OBD2_OBDTEST_H

#include <string>
#include "DataObject.h"

using namespace std;


class OBDTest {
private:
    DataObject<bool>* available;
    DataObject<bool>* incomplete;
    string name;
public:
    OBDTest(string name,
            ByteIndex availableByte, byte availableIndex,
            ByteIndex  incompleteByte, byte incompleteIndex);


    void fromFrame(byte* frame);
};


#endif //OPEN_OBD2_OBDTEST_H
