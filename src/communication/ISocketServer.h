//
// Created by me on 22/01/19.
//

#ifndef OPEN_OBD2_ISOCKETSERVER_H
#define OPEN_OBD2_ISOCKETSERVER_H

#include "ICommunicationInterface.h"
#include "ISocketServerClientHandler.h"
#include "ICloseable.h"
#include <functional>

class ISocketServer : public ICloseable {
public:
    virtual void setClientHandler(ISocketServerClientHandler *handler) = 0;

    virtual void receive(byte *buf, int bufSize, int &readSize, int socketHandle) = 0;

    virtual int send(byte *buf, int buflen, int socketHandle) = 0;
};

#endif //OPEN_OBD2_ISOCKETSERVER_H
