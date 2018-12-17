//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_DATAPOSITION_H
#define OPEN_OBD2_DATAPOSITION_H
#define BITS_PER_BYTE 8
#define MAX_BIT_INDEX 7

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
    byte *data;

    int getBitIndexRead(int byteVal, int idx, int sByte) const {
        if (sByte == A) {
            return MAX_BIT_INDEX - idx;
        } else {
            if (idx == 0) {
                return byteVal + MAX_BIT_INDEX;
            }

            if (idx == MAX_BIT_INDEX) {
                return byteVal;
            }

            return MAX_BIT_INDEX - (idx % MAX_BIT_INDEX) + byteVal;
        }
    }

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

    unsigned int toFrame(unsigned int &data) {
        auto startByteValue = -BITS_PER_BYTE + ((startByte + 1) * BITS_PER_BYTE);
        auto stopByteValue = -BITS_PER_BYTE + ((stopByte + 1) * BITS_PER_BYTE);

        // bit index is the value below A1...D7 in the comment at the top of the fle
        int startBitIndex = getBitIndexRead(startByteValue, startIndex, startByte);
        int stopBitIndex = getBitIndexRead(stopByteValue, stopIndex, stopByte);
        unsigned int retVal;

        if (isBool) {
            retVal = (unsigned int) value << (startByte * 8) + startIndex;
        } else {
            retVal = (unsigned int) value << (startIndex - stopBitIndex + 1);
        }

        return retVal;
        //auto retVal = abs(stopBitIndex - startBitIndex);
//
//        vector<byte> arrayOfByte(1);
//        for (int i = 0; i < bitSize; i++) {
//            arrayOfByte[bitSize - 1 - i] = (value >> (i * 8));
//        }

        return 0;
    }

    int fromFrame(byte *frame, int bufferSize) {
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
            auto startByteValue = -BITS_PER_BYTE + ((startByte + 1) * BITS_PER_BYTE);
            auto stopByteValue = -BITS_PER_BYTE + ((stopByte + 1) * BITS_PER_BYTE);

            // bit index is the value below A1...D7 in the comment at the top of the fle
            int startBitIndex = getBitIndexRead(startByteValue, startIndex, startByte);
            int stopBitIndex = getBitIndexRead(stopByteValue, stopIndex, stopByte);

            auto bitSize = abs(stopBitIndex - startBitIndex);

            unsigned int mask = 0;
            for (i = 0; i <= bitSize; i++) {
                mask |= 1 << i;
            }

            if (bitSize > 4) {
                value = (T) (mask & (data));
            } else {
                value = (T) ((data << startBitIndex) - 1 & mask);
            }
        }

        return 1;
    }
};


#endif //OPEN_OBD2_DATAPOSITION_H
