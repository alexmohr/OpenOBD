//
// Created by me on 23/12/18.
//

#ifndef OPEN_OBD2_CALCULATEDDATAOBJECT_H
#define OPEN_OBD2_CALCULATEDDATAOBJECT_H

#include "DataObject.h"
#include "CalculatedValues.h"
#include <functional>

template<typename S, typename T>
class CalculatedDataObject {
private:
    unique_ptr<DataObject<S>> dataObj;
    unique_ptr<DataObjectDescription<T>> description;
    function<T(S)> fromFrameFunction;
    function<S(T)> toFrameFunction;


public:

    CalculatedDataObject(ByteIndex startByte, unsigned int startIndex,
                         ByteIndex stopByte, unsigned stopIndex, function<T(S)> fromFrameFunction,
                         function<S(T)> toFrameFunction, const DataObjectUnit &unit, T min, T max)
            : CalculatedDataObject(startByte, startIndex, stopByte, stopIndex, fromFrameFunction, toFrameFunction,
                                   unit, min, max, "") {}


    CalculatedDataObject(ByteIndex startByte, unsigned int startIndex,
                         ByteIndex stopByte, unsigned stopIndex, function<T(S)> fromFrameFunction,
                         function<S(T)> toFrameFunction, const DataObjectUnit &unit, T min, T max,
                         const string &description) {
        this->dataObj = make_unique<DataObject<S>>(startByte, startIndex, stopByte, stopIndex);
        this->description = make_unique<DataObjectDescription<T>>(unit, min, max, description);
        this->toFrameFunction = toFrameFunction;
        this->fromFrameFunction = fromFrameFunction;
    }

    S getRawValue() {
        return dataObj->getValue();
    }

    T getValue() {
        auto val = dataObj->getValue();
        return fromFrameFunction(val);
    }

    void setValue(T value) {
        dataObj->setValue(toFrameFunction(value));
    }

    void fromFrame(byte *data, int size) {
        dataObj->fromFrame(data, size);
    }

    unsigned int toFrame(unsigned int &data) {
        return dataObj->toFrame(data);
    }

    DataObjectDescription<T> &getDescription() {
        return *description;
    }
};

#endif //OPEN_OBD2_CALCULATEDDATAOBJECT_H
