//
// Created by me on 22/01/19.
//

#include "easylogging++.h"
#include "SocketServer.h"
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>


SocketServer::SocketServer(int port) {
    this->port = port;
}

int SocketServer::openInterface() {
    int opt = 1;

    struct sockaddr_in address;
    // Creating socket file descriptor
    if ((socketHandle = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        PLOG(ERROR) << "socket failed";
        return -1;
    }

    // Forcefully attaching socket to the port
    if (setsockopt(socketHandle, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        PLOG(ERROR) << "setsockopt";
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(static_cast<uint16_t>(port));

    // Forcefully attaching socket to the port
    if (bind(socketHandle, (struct sockaddr *) &address,
             sizeof(address)) < 0) {
        PLOG(ERROR) << "bind failed";
        return -1;
    }

    if (listen(socketHandle, 3) < 0) {
        PLOG(ERROR) << "listen";
        return -1;
    }

    tServeThread = thread(&SocketServer::serve, this);
    exitRequested = false;
    isOpen = true;
    return 0;
}

int SocketServer::closeInterface() {
    if (!isOpen){
        return 0;
    }

    exitRequested = true;
    tServeThread.join();
    close(socketHandle);
    isOpen = false;
    return 0;
}

void SocketServer::setClientHandler(ISocketServerClientHandler *handler) {
    clientHandler = handler;
}

void SocketServer::serve() {
    int clientSockFd;

    struct sockaddr_in address;
    int addrlen = sizeof(address);
    while (!exitRequested) {

        if (SocketCommunicationBase::socketSelectTimeout(socketHandle) <= 0) {
            continue;
        }

        clientSockFd = accept(socketHandle, (struct sockaddr *) &address, (socklen_t *) &addrlen);
        if (clientSockFd < 0) {
            PLOG(ERROR) << "accept";
            continue;
        }

        if (nullptr == clientHandler) {
            LOG(ERROR) << "No client handler registered";
            close(clientSockFd);
        }

        clientHandler->handleClient(clientSockFd);
    }
}

int SocketServer::send(byte *buf, int buflen, int socketHandle) {
    return SocketCommunicationBase::send(buf, buflen, socketHandle);
}

void SocketServer::receive(byte *buf, int bufSize, int &readSize, int socketHandle) {
    SocketCommunicationBase::receive(buf, bufSize, readSize, socketHandle);
}
