//
// Created by me on 20/01/19.
//

#include "SocketClient.h"
#include "easylogging++.h"
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <libnet.h>

SocketClient::SocketClient(int port, char *host) {
    this->port = port;
    this->host = host;
}


int SocketClient::openInterface() {
    int res, valopt;
    struct sockaddr_in addr;
    long arg;
    fd_set myset;
    struct timeval tv;
    socklen_t lon;

    // Create socket
    socketHandle = socket(AF_INET, SOCK_STREAM, 0);

    // Set non-blocking
    arg = fcntl(socketHandle, F_GETFL, NULL);
    arg |= O_NONBLOCK;
    fcntl(socketHandle, F_SETFL, arg);

    // Trying to connect with timeout
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(host);
    res = connect(socketHandle, (struct sockaddr *) &addr, sizeof(addr));
    if (res < 0) {
        if (errno == EINPROGRESS) {
            tv.tv_sec = 15;
            tv.tv_usec = 0;
            FD_ZERO(&myset);
            FD_SET(socketHandle, &myset);
            if (select(socketHandle + 1, nullptr, &myset, nullptr, &tv) > 0) {
                lon = sizeof(int);
                getsockopt(socketHandle, SOL_SOCKET, SO_ERROR, (void *) (&valopt), &lon);
                if (valopt) {
                    LOG(ERROR) << "Error in connection() " << valopt << " - " << strerror(valopt);
                    return 1;
                }
            } else {
                LOG(ERROR) << "Timeout or error() " << valopt << " - " << strerror(valopt);
                return 1;
            }
        } else {
            LOG(ERROR) << "Error on connection" << errno << ": " << strerror(errno);
            return 1;
        }
    }

    // Set to blocking mode again...
    arg = fcntl(socketHandle, F_GETFL, NULL);
    arg &= (~O_NONBLOCK);
    fcntl(socketHandle, F_SETFL, arg);

    return 0;
}
