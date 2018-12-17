//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_DATAPOSITION_H
#define OPEN_OBD2_DATAPOSITION_H

#include <stdio.h>
#include <cstddef>
#include <cmath>
#include "easylogging++.h"

using namespace std;


enum ByteIndex{
    A = 0,
    B = 1,
    C = 2,
    D = 3,
    E = 4,
};

/*
    A7	A6	A5	A4	A3	A2	A1	A0	B7	B6	B5	B4	B3	B2	B1	B0	C7	C6	C5	C4	C3	C2	C1	C0	D7	D6	D5	D4	D3	D2	D1	D0
    00  01  02  03  04  05  06  07  08  09  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31
 7=0
 6=1
 5=2
 4=3
 3=4
 0=7

 */

template <class T>
class DataObject {
private:
    ByteIndex startByte;
    unsigned int startIndex;
    ByteIndex  stopByte;
    unsigned int stopIndex;
    T value;
    bool isBool = false;
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

    int getBitIndex(int byteVal, int idx, int sByte) const {
        int bitIndex;
        if (sByte == A) {
            bitIndex = 7 - idx;
        } else {
            bitIndex = 0 == idx ? byteVal + 7 : byteVal + (idx % 7);
        }

        return bitIndex;
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
            auto startByteValue = -8 + ((startByte + 1) * 8);
            auto stopByteValue = -8 + ((stopByte + 1) * 8);

            // bit index is the value below A1...D7 in the comment at the top of the fle
            int startBitIndex = getBitIndex(startByteValue, startIndex, startByte);
            int stopBitIndex = getBitIndex(stopByteValue, stopIndex, stopByte);


            auto bitSize = abs(stopBitIndex - startBitIndex);

            unsigned int mask = 0;
            for (i = 0; i <= bitSize; i++) {
                mask |= 1 << i;
            }

            if (bitSize > 4) {
                value = (T) (mask & (data));
            } else {
                value = (T) ((1 << startBitIndex) - 1 & mask);
            }

        }

        return 1;
    }
};


#endif //OPEN_OBD2_DATAPOSITION_H
