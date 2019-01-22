//
// Created by me on 03/01/19.
//

#include "SocketCommunicationBase.h"
#include "easylogging++.h"
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <libnet.h>


int SocketCommunicationBase::send(byte *buf, int buflen) {
    if (-1 == socketHandle) {
        openInterface();
    }

    int sendBytes = 0;
    sendBytes = static_cast<int>(::send(socketHandle, buf, buflen, MSG_NOSIGNAL));
    if (sendBytes < 0) {
        PLOG(ERROR) << "Failed to write to socket";
        closeInterface();
        return sendBytes;
    }

    if (sendBytes != buflen) {
        el::Loggers::getLogger("default")->warn("wrote only %d from %d byte\n", sendBytes, buflen);
    }

    return sendBytes;
}

void SocketCommunicationBase::receive(byte *buffer, int buffSize, int &readSize) {
    SocketCommunicationBase::receive(buffer, buffSize, readSize, socketHandle);
}

void SocketCommunicationBase::receive(byte *buf, int bufSize, int &readSize, int socketHandle) {
    int t = socketSelectTimeout(socketHandle);
    if (t > 0) {
        readSize = static_cast<int>(read(socketHandle, buf, static_cast<size_t>(bufSize)));
    } else {
        readSize = 0;
    }
}

int SocketCommunicationBase::socketSelectTimeout(int socketHandle) {
    struct timeval timeout = {1, 0};
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(socketHandle, &readSet);
    int t = select((socketHandle + 1), &readSet, nullptr, nullptr, &timeout);
    return t;
}

int SocketCommunicationBase::closeInterface() {
    close(socketHandle);
    socketHandle = -1;
    return 0;
}
