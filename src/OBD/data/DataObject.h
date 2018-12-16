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
    A = 0,
    B = 1,
    C = 2,
    D = 3,
    E = 4,
};

template <class T>
class DataObject {
private:
    ByteIndex startByte;
    unsigned int startIndex;
    ByteIndex  stopByte;
    unsigned int stopIndex;
    T value;
    bool isBool;
public:

    DataObject(ByteIndex startByte, byte startIndex) : DataObject(startByte, startIndex,
                                                                  startByte, startIndex) {

    }


    DataObject(ByteIndex startByte, byte startIndex,
            ByteIndex stopByte, byte stopIndex) {
        this->startByte = startByte;
        this->startIndex = (unsigned int) startIndex;
        this->stopByte= stopByte;
        int offset = (stopByte - startByte + 1);
        this->stopIndex = (unsigned int) stopIndex;

        if (startByte == stopByte && stopIndex == startIndex) {
            isBool = true;
        }
    }

    T getValue() {
        return value;
    }

    void setValue(T val) {
        value = val;
    }

    int setValue(byte *frame, int bufferSize) {
        int i;
        unsigned int data = 0;
        const int size = stopByte - startByte + 1;
        if (size > bufferSize || stopByte > bufferSize) {
            return -1;
        }

        auto dataBytes = (byte *) malloc((size_t) size);
        memset(dataBytes, 0, size);
        memcpy(dataBytes, frame, size);

        for (i = startByte; i <= stopByte; i++) {
            data <<= 8;
            data |= (unsigned int) frame[i];
        }

        if (isBool) {
            value = (T) (data & (1 << startIndex));
        } else {
            unsigned int mask = 0;
            const unsigned int end = (stopByte - startByte + 1) * stopIndex;
            for (i = 0; i <= end + 1; i++) {
                mask |= 1 << i;
            }

            value = (T) (mask & data);
        }
////
//
//        auto s1 = ((*data >> startIndex));
//        auto s2 = ((1UL << (stopIndex - startIndex) - 1));
//        auto s3 = s2 - 1;
//
//        value = (T) ((*data >> (startIndex - 1)) & ((1UL << (stopIndex - startIndex))));
        // auto foo = BitExtract(data, startIndex, stopIndex - startIndex);
        //LOG(DEBUG) << "Updated value of data object, new value:" << to_string(fooo);

        return 1;

    }
};


#endif //OPEN_OBD2_DATAPOSITION_H
