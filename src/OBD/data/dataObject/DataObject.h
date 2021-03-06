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
#include "DataObjectDescription.h"
#include "IFrameObject.h"
#include "../../../common/conversion.h"
#include "IDataObject.h"

using namespace std;


enum ByteIndex {
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






template<class T>
class DataObject : public IFrameObject, public IDataObject<T> {
private:
    ByteIndex startByte;
    unsigned int startIndex;
    ByteIndex stopByte;
    unsigned int stopIndex;
    T value;
    bool isBool = false;
    unique_ptr<DataObjectDescription> description;

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

    // boolean C'tor
    DataObject(ByteIndex startByte, unsigned int startIndex, const string description) :
            DataObject(startByte, startIndex, startByte, startIndex, unit_bool, false, true, description) {
    }

    // boolean C'tor
    DataObject(ByteIndex startByte, unsigned int startIndex, const DataObjectUnit &unit, const string description) :
            DataObject(startByte, startIndex, startByte, startIndex, unit, false, true, description) {

    }

    DataObject(ByteIndex startByte, unsigned int startIndex,
               ByteIndex stopByte, unsigned int stopIndex, const DataObjectUnit &unit, T min, T max) :
            DataObject(startByte, startIndex, stopByte, stopIndex) {
        this->description = make_unique<DataObjectDescription>(unit, (double) min, (double) max, "");
    }

    DataObject(ByteIndex startByte, unsigned int startIndex,
               ByteIndex stopByte, unsigned int stopIndex, const DataObjectUnit &unit, T min, T max,
               const string &description) :
            DataObject(startByte, startIndex, stopByte, stopIndex) {
        this->description = make_unique<DataObjectDescription>(unit, (double) min, (double) max, description);
    }

    // c'tors without description
public:
    // boolean C'tor
    DataObject(ByteIndex startByte, unsigned int startIndex) :
            DataObject(startByte, startIndex, startByte, startIndex) {
        this->description = make_unique<DataObjectDescription>(unit_none, 0, 1, "");
    }

    DataObject(ByteIndex startByte, unsigned int startIndex,
               ByteIndex stopByte, unsigned int stopIndex) {
        this->startByte = startByte;
        this->startIndex = startIndex;
        this->stopByte = stopByte;
        this->stopIndex = stopIndex;
        this->description = nullptr;

        if (startByte == stopByte && stopIndex == startIndex) {
            isBool = true;
        }

        value = static_cast<T>(0);
    }

public:
    T getValue() override {
        return value;
    }


    DataObjectState setValue(T value) override {
        DataObjectState i;
        if (nullptr != this->description) {
            i = description->checkBounds((double) value);
            if (i.type != SUCCESS) {
                return i;
            }
        }

        this->value = value;
        return i;
    }


    unsigned int toFrame(unsigned int &data, int &size) override {
        auto startByteValue = -BITS_PER_BYTE + ((startByte + 1) * BITS_PER_BYTE);
        auto stopByteValue = -BITS_PER_BYTE + ((stopByte + 1) * BITS_PER_BYTE);

        // bit index is the value below A1...D7 in the comment at the top of the fle
        int startBitIndex = getBitIndexRead(startByteValue, startIndex, startByte);
        int stopBitIndex = getBitIndexRead(stopByteValue, stopIndex, stopByte);
        unsigned int retVal;

        size_t targetSize = sizeof(retVal) * 8;
        auto bitSize = abs(stopBitIndex - startBitIndex);

        size_t shift = targetSize - bitSize - startBitIndex - 1;
        retVal = (unsigned int) value << (shift);
        if (0 == bitSize) {
            bitSize++;
        }
        size += bitSize;

        return retVal;
    }

    void fromFrame(byte *frame, int bufferSize) override {
        int i;
        unsigned int data = 0;
        const int size = stopByte - startByte + 1;
        if (size > bufferSize || stopByte > bufferSize) {
            throw std::invalid_argument("Prevented buffer overflow in DataObject.h");
        }

        auto dataBytes = new byte[size];
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
                value = (T) (((data << startBitIndex) - 1) & mask);
            }
        }

        delete[] dataBytes;
    }

    string getPrintableData() override {
        string unit;
        if (nullptr != description) {
            unit = description->getUnit().toShortString();
        }

        return to_string(getValue()) + unit;
    }


    DataObjectStateCollection setValueFromString(string data) override {
        DataObjectStateCollection rs = DataObjectStateCollection();
        DataObjectState i = description->checkBounds(strtod(data.c_str(), nullptr));
        if (i.type == SUCCESS) {
            i = setValue(convertStringToT<T>(data));
        }

        rs.resultSet.push_back(i);
        return rs;
    }

    vector<DataObjectDescription *> getDescriptions() override {
        return vector<DataObjectDescription *>{description.get()};
    }
};


#endif //OPEN_OBD2_DATAPOSITION_H
