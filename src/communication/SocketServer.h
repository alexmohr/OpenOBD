//
// Created by me on 22/01/19.
//

#ifndef OPEN_OBD2_SOCKETSERVER_H
#define OPEN_OBD2_SOCKETSERVER_H

#include "SocketCommunicationBase.h"
#include "ISocketServer.h"
#include <thread>

class SocketServer : public ISocketServer {
private:
    int port;
    int socketHandle;
    std::thread tServeThread;
    ISocketServerClientHandler *clientHandler;
    bool exitRequested;
    bool isOpen;
public:

    explicit SocketServer(int port);

public: // override ICommunicationInterface
    int openInterface() override;

    int closeInterface() override;

public: // override ISocketServer
    void setClientHandler(ISocketServerClientHandler *handler) override;

    void receive(byte *buf, int bufSize, int &readSize, int socketHandle) override;

    int send(byte *buf, int buflen, int socketHandle) override;

private:
    void serve();
};


#endif //OPEN_OBD2_SOCKETSERVER_H
