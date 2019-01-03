//
// Created by me on 23/12/18.
//

#ifndef OPEN_OBD2_CALCULATEDDATAOBJECT_H
#define OPEN_OBD2_CALCULATEDDATAOBJECT_H

#include "DataObject.h"
#include "CalculatedValues.h"
#include <functional>

class CalculatedDataObjectFactory;

template<typename S, typename T>
class CalculatedDataObject : public IFrameObject {
private:

    unique_ptr<DataObject<S>> dataObj;
    unique_ptr<DataObjectDescription<T>> description;
    function<T(S)> fromFrameFunction;
    function<S(T)> toFrameFunction;


public: // todo refactor this to private;
    friend class CalculatedDataObjectFactory;
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


public:
    S getRawValue() {
        return dataObj->getValue();
    }

    T getValue() {
        auto val = dataObj->getValue();
        return fromFrameFunction(val);
    }

    void setValue(T value) {
        if (value < description->getMin() || value > description->getMax()) {
            string msg = "Value: " + to_string((long) value) + " is out of bounds.";
            throw std::invalid_argument(msg.c_str());
        }

        dataObj->setValue(toFrameFunction(value));
    }

    void fromFrame(byte *data, int size) override {
        dataObj->fromFrame(data, size);
    }

    unsigned int toFrame(unsigned int &data, unsigned int &size) override {
        return dataObj->toFrame(data, size);
    }

    string getPrintableData() override {
        string unit = "";
        if (nullptr != description) {
            unit = description->getUnit().toShortString();
        }

        return to_string(getValue()) + unit;
    }

    DataObjectDescription<T> &getDescription() {
        return *description;
    }

    void setValueFromString(string data) override {
        if (std::is_same<T, double>::value ||
            std::is_same<T, float>::value) {
            setValue((T) strtod(data.c_str(), nullptr));
        } else if (std::is_same<T, short>::value ||
                   std::is_same<T, int>::value ||
                   std::is_same<T, long>::value) {
            setValue((T) strtol(data.c_str(), nullptr, 0));
        } else {
            setValue((T) strtoul(data.c_str(), nullptr, 0));
        }
    }
};


#endif //OPEN_OBD2_CALCULATEDDATAOBJECT_H
