//
// Created by me on 31/12/18.
//

#ifndef OPEN_OBD2_IFRAMEOBJECT_H
#define OPEN_OBD2_IFRAMEOBJECT_H

#include <cstddef>

using namespace std;

class IFrameObject {
public:
    virtual unsigned int toFrame(unsigned int &data, unsigned int &size) = 0;

    virtual void fromFrame(byte *data, int size) = 0;

    virtual string getPrintableData() = 0;

    virtual void setValueFromString(string data) = 0;
};

#endif //OPEN_OBD2_IFRAMEOBJECT_H
