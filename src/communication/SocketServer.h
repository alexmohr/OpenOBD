//
// Created by me on 22/01/19.
//

#ifndef OPEN_OBD2_SOCKETSERVER_H
#define OPEN_OBD2_SOCKETSERVER_H

#include "SocketCommunicationBase.h"

class SocketServer : public SocketCommunicationBase {
private:
    int port;
    char *host;
public:
    SocketClient(int port, char *host);

public: // override ICommunicationInterface
    int openInterface() override;

};


#endif //OPEN_OBD2_SOCKETSERVER_H
