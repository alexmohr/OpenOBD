//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_DATAPOSITION_H
#define OPEN_OBD2_DATAPOSITION_H

#include "types.h"

enum ByteIndex{
    A = 1,
    B = 2,
    C = 3,
    D = 4,
    E = 5,
};

template <typename T>
class DataObject {
public:
    ByteIndex startByte;
    BYTE startIndex;
    ByteIndex  stopByte;
    BYTE stopIndex;
    DataObject();

    DataObject(ByteIndex startByte, BYTE startIndex);

    DataObject(ByteIndex startByte, BYTE startIndex,
            ByteIndex stopByte, BYTE stopIndex);
    DataObject(BYTE *frame);

    void getValue(BYTE* src, BYTE* value);
};


#endif //OPEN_OBD2_DATAPOSITION_H
