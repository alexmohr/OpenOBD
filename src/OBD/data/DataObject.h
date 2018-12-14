//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_DATAPOSITION_H
#define OPEN_OBD2_DATAPOSITION_H

#include <stdio.h>
#include <cstddef>
#include "easylogging++.h"

using namespace std;


enum ByteIndex{
    A = 1,
    B = 2,
    C = 3,
    D = 4,
    E = 5,
};

template <class T>
class DataObject {
private:
    ByteIndex startByte;
    byte startIndex;
    ByteIndex  stopByte;
    byte stopIndex;
public:

    DataObject(ByteIndex startByte, byte startIndex) : DataObject(startByte, startIndex,
                                                                  startByte, startIndex) {

    }


    DataObject(ByteIndex startByte, byte startIndex,
            ByteIndex stopByte, byte stopIndex) {
        this->startByte = startByte;
        this->startIndex= startIndex;
        this->stopByte= stopByte;
        this->stopIndex = stopIndex;
    }

    T getValue() {

    }

    void setValue(byte* frame){
        auto dataSize= (stopByte-startByte)+1;
        byte* data = (byte*)malloc(sizeof(byte)*dataSize);
        memcpy(data, frame+startByte, dataSize);

        LOG(ERROR) << dataSize;

    }
};


#endif //OPEN_OBD2_DATAPOSITION_H
