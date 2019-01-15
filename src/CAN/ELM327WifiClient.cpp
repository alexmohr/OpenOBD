//
// Created by me on 03/01/19.
//

#include "ELM327WifiClient.h"
#include "easylogging++.h"
#include "../common/conversion.h"
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <libnet.h>
#include <chrono>
#include <iomanip>
#include <thread>

using namespace std::chrono_literals;

ELM327WifiClient::ELM327WifiClient(int port, char *host) {
    this->port = port;
    this->host = host;
}


int ELM327WifiClient::openInterface() {
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
void ELM327WifiClient::receive(byte *buffer, int buffSize, int &readSize) {
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
    bool hasTimeout = false;
    byte *nbuf = (byte *) malloc(buffSize);
    while ((char) buffer[readSize - 1] != '\r'
           && (char) buffer[readSize - 2] != '\r'
           && !hasTimeout) {
        int newSize = 0;
        SocketCommunicationBase::receive(nbuf, buffSize, newSize);
        if (newSize > 0) {
            if (readSize + newSize < buffSize) {
                // append the additional received data to our existing buffer.
                memcpy(buffer + readSize, nbuf, newSize);
                readSize += newSize;
            } else {
                LOG(ERROR) << "Appending to buffer would lead to overflow. aborting read";
                readSize = -1;
                return;
            }

        }

        hasTimeout = chrono::high_resolution_clock::now() - t0 > 500ms;
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

    //   closeInterface();
}

void ELM327WifiClient::parseData(byte *buffer, int &readSize) {
    // copy data into temporary buffer.
    char *cbuf = (char *) malloc(readSize);
    memcpy(cbuf, buffer, readSize);
    memset(buffer, 0, readSize);

    // used as temporary value for parsing data
    unsigned int value;

    // first 3 bytes are id.
    int j = 0;
    int i = 3;
    char tbuf[2];
    memcpy(tbuf, cbuf + i, 2);
    string sData = string(tbuf);
    
    // todo add support for multi frame messages.
    auto remaining = convertHexToInt(sData);

    int offset = 5;
    for (i = offset; i <= remaining * 2 + offset; i += 2) {
        memset(&tbuf, 0, 2);
        memcpy(tbuf, cbuf + i, 2);
        stringstream ss;
        ss << hex << tbuf;

        ss >> value;
        buffer[j++] = (byte) value;
    }
    readSize = --j;
    delete cbuf;
}

int ELM327WifiClient::send(byte *buf, int buflen) {
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
    return SocketCommunicationBase::send((byte *) st.c_str(), static_cast<int>(st.size()));
}

int ELM327WifiClient::configureInterface() {
    int bufSize = 1024;
    int result = 0;
    int recvSize;

    byte *buf = (byte *) malloc(bufSize);

    // echo OFF
    result += isOkay(buf, bufSize, "ATE0");

    // headers ON
    result += isOkay(buf, bufSize, "ATH1");

    // spaces OFF
    result += isOkay(buf, bufSize, "ATS0");

    // try auto protocol
    result += isOkay(buf, bufSize, "ATSP0");

    // will trigger search.
    // wait until device is done.
    isOkay(buf, bufSize, "0101");
    do {
        std::this_thread::sleep_for(1000ms);
        SocketCommunicationBase::receive(buf, bufSize, recvSize);
    } while (recvSize != 0);


    return result;
}

int ELM327WifiClient::isOkay(byte *buf, int bufSize, string data) {
    const string ok = "OK";
    int recvSize = 0;
    data += '\r';

    SocketCommunicationBase::send((byte *) data.c_str(), static_cast<int>(data.size()));
    std::this_thread::sleep_for(250ms);
    SocketCommunicationBase::receive(buf, bufSize, recvSize);
    if (recvSize < 2) {
        return 1;
    }

    int i;
    for (i = 0; i < recvSize - 1; i++) {
        if ((char) buf[i] == 'O' && (char) buf[i + 1] == 'K') {
            return 0;
        }
    }
    return 1;
}
