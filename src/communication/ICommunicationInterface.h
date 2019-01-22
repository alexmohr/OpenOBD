//
// Created by me on 04/01/19.
//

#ifndef OPEN_OBD2_ICOMMUNICATIONINTERFACE_H
#define OPEN_OBD2_ICOMMUNICATIONINTERFACE_H

#include <cstddef>
#include "ICloseable.h"

using namespace std;

class ICommunicationInterface : public ICloseable {
public:
    virtual int send(byte *buf, int buflen) = 0;

    virtual void receive(byte *buffer, int buffSize, int &readSize) = 0;

    virtual int configureInterface() = 0;

    virtual ~ICommunicationInterface() = default;

};

#endif //OPEN_OBD2_ICOMMUNICATIONINTERFACE_H
