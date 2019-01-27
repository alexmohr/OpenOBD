//
// Created by me on 20/01/19.
//

#ifndef OPEN_OBD2_SOCKETCLIENT_H
#define OPEN_OBD2_SOCKETCLIENT_H


#include "SocketCommunicationBase.h"

class SocketClient : public SocketCommunicationBase {
private:
    int port;
    char *host;
public:
    SocketClient(int port, char *host);

    ~SocketClient() override;

public: // override ICommunicationInterface
    int openInterface() override;

};


#endif //OPEN_OBD2_SOCKETCLIENT_H
