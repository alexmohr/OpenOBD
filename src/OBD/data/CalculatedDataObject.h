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
    function<T(S)> fromFrameFunction;
    function<S(T)> toFrameFunction;


public:


    CalculatedDataObject(ByteIndex startByte, unsigned int startIndex,
                         ByteIndex stopByte, unsigned stopIndex, function<T(S)> fromFrameFunction,
                         function<S(T)> toFrameFunction) {
        dataObj = make_unique<DataObject<S>>(startByte, startIndex, stopByte, stopIndex);
        this->toFrameFunction = toFrameFunction;
        this->fromFrameFunction = fromFrameFunction;
    }

    T getValue() {
        auto val = dataObj->getValue();
        return fromFrameFunction(val);
    }

    void setValue(T value) {
        dataObj->setValue(toFrameFunction(value));
    }
// todo remove this
//    void setValue(S val) {
//        dataObj->setValue(val);
//    }

    void fromFrame(byte *data, int size) {
        dataObj->fromFrame(data, size);
    }

    unsigned int toFrame(unsigned int &data) {
        return dataObj->toFrame(data);
    }
};

#endif //OPEN_OBD2_CALCULATEDDATAOBJECT_H
