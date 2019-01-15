//
// Created by me on 04/01/19.
//

#ifndef OPEN_OBD2_ICOMMUNICATIONINTERFACE_H
#define OPEN_OBD2_ICOMMUNICATIONINTERFACE_H

#include <cstddef>

using namespace std;

class ICommunicationInterface {
public:
    virtual int send(byte *buf, int buflen) = 0;

    virtual void receive(byte *buffer, int buffSize, int &readSize) = 0;

    virtual int closeInterface() = 0;

    virtual int openInterface() = 0;

    virtual int configureInterface() = 0;

   // virtual ~ICommunicationInterface() = 0;

};

#endif //OPEN_OBD2_ICOMMUNICATIONINTERFACE_H
