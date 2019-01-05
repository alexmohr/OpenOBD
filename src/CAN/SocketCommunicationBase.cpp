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
    int retval = 0;

    retval = static_cast<int>(write(socketHandle, buf, buflen));
    if (retval < 0) {
        LOG(ERROR) << "Failed to write to socket";
        perror("write");
        return retval;
    }

    if (retval != buflen) {
        fprintf(stderr, "wrote only %d from %d byte\n", retval, buflen);
    }

    return retval;
}

void SocketCommunicationBase::receive(byte *buffer, int buffSize, int &readSize) {
    struct timeval timeout = {1, 0};
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(socketHandle, &readSet);
    int t = select((socketHandle + 1), &readSet, nullptr, nullptr, &timeout);
    if (t > 0) {
        readSize = static_cast<int>(read(socketHandle, buffer, static_cast<size_t>(buffSize)));
    } else {
        readSize = 0;
    }
}


int SocketCommunicationBase::closeInterface() {
    close(socketHandle);
    socketHandle = -1;
    return 0;
}
