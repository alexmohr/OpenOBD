//
// Created by me on 03/01/19.
//

#include "ELM327.h"
#include "easylogging++.h"
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <libnet.h>
#include <chrono>
#include <iomanip>

using namespace std::chrono_literals;

ELM327::ELM327(int port, char *host) {
    this->port = port;
    this->host = host;
}


int ELM327::openInterface() {
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
            if (select(socketHandle + 1, NULL, &myset, NULL, &tv) > 0) {
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

/*
// Prints the content to std out
void printDebugInfo(int readSize, byte *buffer) {
    for (int i = 0; i < readSize; i++) {
        printf("%c", buffer[i]);
    }

    printf("\n");
    for (int i = 0; i < readSize; i++) {
        printf(" %i ", buffer[i]);
    }

    printf("\n");
}
*/
void ELM327::receive(byte *buffer, int buffSize, int &readSize) {
    // hack because elm closes connection after command has been sent.
    if (socketHandle == -1) {
        this->openInterface();
    }

    SocketCommunicationBase::receive(buffer, buffSize, readSize);
    if (readSize <= 0) {
        closeInterface();
        return;
    }

    // part of frame received.
    auto t0 = chrono::high_resolution_clock::now();

    // get the rest of the frame.
    // abort after 500 ms.
    char frameEnd = '>';
    bool hasTimeout = false;
    byte *nbuf = (byte *) malloc(buffSize);
    while ((char) buffer[readSize - 1] != frameEnd
           && (char) buffer[readSize - 2] != frameEnd
           && !hasTimeout) {
        int newSize = 0;
        SocketCommunicationBase::receive(nbuf, buffSize, newSize);
        if (newSize > 0) {
            // append the additional received data to our existing buffer.
            memcpy(buffer + readSize, nbuf, newSize);
            readSize += newSize;
        }

        hasTimeout = chrono::high_resolution_clock::now() - t0 > 600ms;
    }

    delete nbuf;

    if (hasTimeout) {
        LOG(ERROR) << "failed to retrieve complete frame";
        readSize = -1;
        closeInterface();
        return;
    }

    if (readSize > buffSize) {
        // received garbage from interface
        LOG(ERROR) << "Data does not fit into buffer.";
        readSize = -1;
    } else {
        // printDebugInfo(readSize, buffer);
        parseData(buffer, readSize);
    }

    closeInterface();
}

void ELM327::parseData(byte *buffer, int &readSize) {
    // copy data into temporary buffer.
    char *cbuf = (char *) malloc(readSize);
    memcpy(cbuf, buffer, readSize);


    // data is received as string.
    // parse the string by taking 2 chars and combining them into byte
    readSize /= 2;

    // reset the buffer with is given back to the caller
    memset(buffer, 0, readSize);

    // used as temporary value for parsing data
    unsigned int value;

    char tbuf[2];
    int rs = readSize;
    int i, j = 0;

    // find start
    for (i = 0; i <= readSize; i++) {
        // skip the value if it is not data
        if (cbuf[i] != '\r') {
            rs--; // byte is not relevant for read size
            continue;
        }
        break;
    }
    i++;

    for (; i <= readSize + 2; i += 2) {
        if (cbuf[i] <= ' ') {
            rs--; // byte is not relevant for read size
            i--;
            continue;
        }

        // copy the data into the new buffer and parse it to hex
        // there is a potenial bug when i+1 does not match the condition above
        // it has not yet seen in praxis because the condition above only checks where the message starts
        memset(&tbuf, 0, 2);
        memcpy(tbuf, cbuf + i, 2);
        stringstream ss;
        ss << hex << tbuf;

        ss >> value;
        buffer[j++] = (byte) value;
    }

    readSize = rs;
    delete cbuf;
}

int ELM327::send(byte *buf, int buflen) {
    // hack because elm closes connection after command has been sent.
    if (socketHandle == -1) {
        this->openInterface();
    }

    std::stringstream ss;
    for (int i(0); i < buflen; ++i) {
        ss << std::hex << std::setfill('0') << std::setw(2) << (int) buf[i];
    }

    string st = ss.str();
    st += '\r';
    return SocketCommunicationBase::send((byte *) st.c_str(), st.size());
}
