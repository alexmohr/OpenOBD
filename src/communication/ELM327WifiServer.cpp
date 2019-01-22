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
    LOG(INFO) << "Starting ELM server";

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


int ELM327WifiServer::sendResponse(byte *buf, int bufSize, int &recvSize, int &clientSockFd) {
    if (recvSize < 2) {
        recvSize = -1;
        return -1;
    }
    int result = 0;
    if (messageContains(buf, recvSize, ELM_CONFIG_PREFIX)) {
        bool success = parseConfiguration(buf, recvSize);
        if (!success) {
            return 1;
        }
        sendConfigurationAnswer(clientSockFd, success);

    } else {
        result = parseData(buf, recvSize);
        sendDataAnswer(clientSockFd, recvSize, buf, bufSize);
    }

    return result;
}

int ELM327WifiServer::parseData(byte *data, int &size) const {
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
    for (i = 0; i <= size; i += 2) {
        memcpy(charBuf, data + i, 2);
        stringstream ss;
        ss << hex << charBuf;
        ss >> value;

        outBuf[j++] = (byte) value;
    }

    outBuf[j] = (byte) ELM_FLOW_PROMPT;
    memcpy(data, outBuf, size);

    return 0;
}

bool ELM327WifiServer::parseConfiguration(byte *buf, int &recvSize) {
    int commandLength;
    for (commandLength = 0; commandLength < recvSize; commandLength++) {
        if (isNumber(buf[commandLength])) {
            break;
        }
    }

    if (commandLength == recvSize) {
        return false;
    }

    char *cmd = new char[commandLength + 1];
    memset(cmd, 0, commandLength + 1);
    memcpy(cmd, buf, commandLength);
    cmd[commandLength + 1] = '\0';

    string param = convertCharToString((char) buf[commandLength]);

    bool result = true;
    if (ELM_CONFIG_HEADER == cmd) {
        sendHeaders = param == ELM_CONFIG_ENABLE;
    } else if (ELM_CONFIG_SPACES == cmd) {
        sendSpaces = param == ELM_CONFIG_ENABLE;
    } else if (ELM_CONFIG_PROTOCOL == cmd) {
        if (param != supportedProtocol) {
            result = false;
        }
    }

    delete[] cmd;
    return result;
}


void ELM327WifiServer::serve() {
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
        serveClient(clientSockFd);
    }
}

void ELM327WifiServer::serveClient(int clientSockFd) {

    int readSize;
    int bufSize = 1024;
    byte *inBuf = (byte *) malloc(bufSize);
    byte *buf = (byte *) malloc(bufSize);
    auto message = vector<byte>();

    int i;
    while (!exitRequested) {
        readSize = static_cast<int>(read(clientSockFd, inBuf, bufSize));
        for (i = 0; i < readSize; i++) {
            if (inBuf[i] == (byte) '\n') {
                continue;
            }

            if (inBuf[i] == (byte) ELM_FLOW_PROMPT) {
                break;
            }

            message.push_back(inBuf[i]);
        }


        int msgSize = static_cast<int>(message.size());
        memcpy(buf, message.data(), msgSize);
        if (sendResponse(buf, bufSize, msgSize, clientSockFd) != 0) {
            close(clientSockFd);
            break;
        }
        message.clear();
    }

    delete inBuf;
    delete buf;

}

void ELM327WifiServer::sendConfigurationAnswer(int clientSockFd, bool &success) const {
    string status;
    if (success) {
        status = ELM_FLOW_OK;
    } else {
        status = ELM_FLOW_ERROR;
    }

    status += ELM_FLOW_NEWLINE_PROMPT;
    sendString(clientSockFd, status);
}

void ELM327WifiServer::sendDataAnswer(int clientSockFd, int dataSize, byte *cmdBuf, int bufSize) const {
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

    string message = ss.str();
    if (sendHeaders) {
        std::stringstream ss2;
        ss2 << std::hex << std::setfill('0') << std::setw(2) << j;
        message = getHeader() + ss2.str() + message;
    }

    std::transform(message.begin(), message.end(), message.begin(), ::toupper);
    message += ELM_FLOW_NEWLINE_PROMPT;
    sendString(clientSockFd, message);
}

int ELM327WifiServer::sendString(int clientSockFd, const string &st) const {
    int retVal;
    retVal = static_cast<int>(send(clientSockFd, st.c_str(), st.size(), MSG_NOSIGNAL));
    if (retVal < 0) {
        PLOG(ERROR) << "Failed to send frame to elm client";
    }
    LOG(DEBUG) << "WifiServer sending: \"" << st << "\"";
    return retVal;
}

bool ELM327WifiServer::isOpen() {
    return open;
}

string ELM327WifiServer::getHeader() const {
    // todo maybe implement this.
    return ELM_HEADER_CAN_11_BIT;
}
