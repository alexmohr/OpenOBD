#include <utility>

//
// Created by me on 12/01/19.
//

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>

#include "ELM327WifiServer.h"
#include <iomanip>

ELM327WifiServer::ELM327WifiServer(int port, ICommunicationInterface *commInterface) {
    this->commInterface = commInterface;
    this->port = port;
}


int ELM327WifiServer::openInterface() {
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

    int com = commInterface->openInterface();
    if (com != 0) {
        return com;
    }
    exitRequested = false;
    tServeThread = thread(&ELM327WifiServer::serve, this);
    open = true;
    return 0;
}

int ELM327WifiServer::closeInterface() {
    exitRequested = true;
    tServeThread.join();
    open = false;
    return 0;
}


int ELM327WifiServer::parseData(byte *data, int &size) {
    string ok = "OK\r";
    if (size < 2) {
        size = -1;
        return -1;
    }
    // AT* command for config...
    if ((char) data[0] == 'A' && (char) data[1] == 'T') {

        char cmd = (char) data[2];
        if (cmd == 'H') {
            int val = (char) data[3] - '0';
            sendHeaders = val > 0;
        } else if (cmd == 'S' && (char) data[3] - '0' == 0) {
            sendSpaces = false;
        } else if (cmd == 'S' && (char) data[3] - '1' == 0) {
            sendSpaces = true;
        }

        size = static_cast<int>(ok.size());
        memcpy(data, ok.c_str(), ok.size());
        return 1;
    }

    if ((size + 1) % 2 != 0) {
        size = -1;
        return -1;
    }

    size /= 2;
    int i, j = 0;
    char charBuf[2];
    byte *outBuf = (byte *) malloc(size + 1);
// used as temporary value for parsing data
    unsigned int value;

    for (
            i = 0;
            i <=
            size;
            i += 2) {
        memcpy(charBuf, data
                        + i, 2);
        stringstream ss;
        ss << hex <<
           charBuf;
        ss >>
           value;

        outBuf[j++] = (byte)
                value;
    }
    outBuf[j] = (byte) '\r';

    memcpy(data, outBuf, size
    );
    return 0;
}


void ELM327WifiServer::serve() {
    int clientSockFd;
    size_t readSize;
    int buffSize = 1024;
    auto data = vector<byte>();
    byte *inBuf = (byte *) malloc(buffSize);
    byte *cmdBuf = (byte *) malloc(buffSize);
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    size_t i;
    int j;

    string hello = "\r>";
    struct timeval tv;

    fd_set myset;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    FD_ZERO(&myset);
    FD_SET(socketHandle, &myset);

    while (!exitRequested) {

        if (select(socketHandle + 1, nullptr, &myset, nullptr, &tv) < 0) {
            continue;
        }
        if ((clientSockFd = accept(socketHandle, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
            PLOG(ERROR) << "accept";
            continue;
        }


        while (!exitRequested) {
            // send hello string
            if (send(clientSockFd, hello.c_str(), hello.size(), MSG_NOSIGNAL) < 0) {
                PLOG(ERROR) << "Failed to write to socket";
                break;
            }
            // read data from input
            readSize = read(clientSockFd, inBuf, buffSize);
            for (i = 0; i < readSize; i++) {
                data.push_back(inBuf[i]);
            }

            for (i = 0; i < data.size(); i++) {
                // command not read completely
                if ('\r' != (char) data.at(i)) {
                    continue;
                }

                int rs = static_cast<int>(i + 1);
                memcpy(cmdBuf, data.data(), rs);
                j = parseData(cmdBuf, rs);
                if (rs < 0) {
                    continue;
                }

                if (0 == j) { // data command
                    handleDataCommand(clientSockFd, rs, cmdBuf, buffSize);
                } else if (j > 0) { // config command
                    if (send(clientSockFd, cmdBuf, rs, MSG_NOSIGNAL) < 0) {
                        PLOG(ERROR) << "failed sending data";
                        break;
                    }
                } else { // error
                    LOG(ERROR) << "failed parsing data";
                }

                data.erase(data.begin(), data.begin() + i + 1);
                i = 0;
            }

        }
    }


    delete inBuf;
    delete cmdBuf;

}

void ELM327WifiServer::handleDataCommand(int clientSockFd, int dataSize, byte *cmdBuf, int bufSize) const {
    int readSize;
    byte service = (byte) ((int) cmdBuf[0] + ANSWER_OFFSET);
    byte pid = cmdBuf[1];
    readSize = commInterface->send(cmdBuf, dataSize);
    if (readSize != dataSize) {
        return;
    }


    auto t0 = chrono::high_resolution_clock::now();
    auto timeout = 1000ms;
    while ((cmdBuf[0] != service || cmdBuf[1] != pid)
           && (chrono::high_resolution_clock::now() - t0) < timeout) {
        commInterface->receive(cmdBuf, bufSize, readSize);
    }


    std::stringstream ss;
    int i, j = 0;
    for (i = 0; i < readSize; i++) {

        ss << std::hex << std::setfill('0') << std::setw(2) << (unsigned short) (cmdBuf[i]);
        j++;
        if (sendSpaces) {
            ss << " ";
        }
    }

    string st = ss.str();
    if (sendHeaders) {
        std::stringstream ss2;
        ss2 << std::hex << std::setfill('0') << std::setw(2) << j;
        st = "7E8" + ss2.str() + st + "\r";
    }

    std::transform(st.begin(), st.end(), st.begin(), ::toupper);


    if (write(clientSockFd, st.c_str(), st.size()) < 0) {
        PLOG(ERROR) << "Failed to send frame to elm client";
    }
}

bool ELM327WifiServer::isOpen() {
    return open;
}
