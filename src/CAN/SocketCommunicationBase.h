//
// Created by me on 03/01/19.
//

#ifndef OPEN_OBD2_ICOMHANDLER_H
#define OPEN_OBD2_ICOMHANDLER_H

#include <cstddef>
#include "ICommunicationInterface.h"

using namespace std;

class SocketCommunicationBase : public ICommunicationInterface {
protected:
    int socketHandle = -1;
protected:
    SocketCommunicationBase() = default;

//    ~SocketCommunicationBase() override = default;

public: // ICommunicationInterface-
    int send(byte *buf, int buflen) override;

    void receive(byte *buffer, int buffSize, int &readSize) override;

    int closeInterface() override;
};

#endif //OPEN_OBD2_ICOMHANDLER_H
