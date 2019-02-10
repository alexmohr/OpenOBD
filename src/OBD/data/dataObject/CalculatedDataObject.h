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
class CalculatedDataObject : public IFrameObject, public IDataObject<T> {
private:

    unique_ptr<DataObject<S>> dataObj;
    shared_ptr<DataObjectDescription> description;
    function<T(S)> fromFrameFunction;
    function<S(T)> toFrameFunction;


public: // todo refactor this to private;
    friend class CalculatedDataObjectFactory;

/*
    CalculatedDataObject(ByteIndex startByte, unsigned int startIndex,
                         ByteIndex stopByte, unsigned stopIndex, function<T(S)> fromFrameFunction,
                         function<S(T)> toFrameFunction, const DataObjectUnit &unit, T min, T max)
            : CalculatedDataObject(startByte, startIndex, stopByte, stopIndex, fromFrameFunction, toFrameFunction,
                                   unit, min, max, "") {}
*/

    CalculatedDataObject(ByteIndex startByte, unsigned int startIndex,
                         ByteIndex stopByte, unsigned stopIndex, function<T(S)> fromFrameFunction,
                         function<S(T)> toFrameFunction, const DataObjectUnit &unit, T min, T max,
                         const string &descriptionText) {
        this->description = make_unique<DataObjectDescription>(unit, (double) min, (double) max, descriptionText);
        this->dataObj = make_unique<DataObject<S>>(startByte, startIndex, stopByte, stopIndex, description);
        this->toFrameFunction = toFrameFunction;
        this->fromFrameFunction = fromFrameFunction;
    }


public:
    S getRawValue() {
        return dataObj->getValue();
    }

    T getValue() override {
        auto val = dataObj->getValue();
        return fromFrameFunction(val);
    }

    DataObjectState setValue(T value) override {
        DataObjectState i;
        if (nullptr != this->description) {
            i = description->checkBounds((double) value);
            if (i.type != SUCCESS) {
                return i;
            }
        }

        i = dataObj->setValueWithoutBoundCheck(toFrameFunction(value));
        return i;
    }

    void fromFrame(byte *data, int size) override {
        dataObj->fromFrame(data, size);
    }

    unsigned int toFrame(unsigned int &data, int &size) override {
        return dataObj->toFrame(data, size);
    }

    shared_ptr<DataObjectValueCollection> getDataObjectValue() override {
        auto ptr = make_shared<DataObjectValue>((double) getValue(), description);
        return make_shared<DataObjectValueCollection>(ptr);
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


#endif //OPEN_OBD2_CALCULATEDDATAOBJECT_H
