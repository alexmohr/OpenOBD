//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_OBDTEST_H
#define OPEN_OBD2_OBDTEST_H

#include <string>
#include "dataObject/DataObject.h"

using namespace std;


class OBDTest : IFrameObject {
private:
    unique_ptr<DataObject<bool>> available;
    unique_ptr<DataObject<bool>> incomplete;
    string name;
public:
    OBDTest(string name,
            ByteIndex availableByte, unsigned int availableIndex,
            ByteIndex incompleteByte, unsigned int incompleteIndex);

    ~OBDTest();

    void fromFrame(byte *frame, int size) override;

    unsigned int toFrame(unsigned int &data, unsigned int &size) override;

    string getPrintableData() override;

    void setName(string name);

    DataObject<bool> &getAvailable();

    DataObject<bool> &getIncomplete();
};


#endif //OPEN_OBD2_OBDTEST_H
