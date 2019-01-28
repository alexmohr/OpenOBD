#include <utility>

//
// Created by me on 12/01/19.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

#include "ELM327WifiServer.h"

ELM327WifiServer::ELM327WifiServer(int port,
                                   ICommunicationInterface *commInterface,
                                   ISocketServer *socketServer) {

    this->commInterface = commInterface;
    this->socketServer = socketServer;
    this->port = port;
}


int ELM327WifiServer::openInterface() {
    LOG(INFO) << "Starting ELM Server";
    exitRequested = false;
    int com = commInterface->openInterface();
    if (com != 0) {
        return com;
    }

    socketServer->setClientHandler(this);
    com = socketServer->openInterface();
    if (com != 0) {
        return com;
    }

    open = true;
    return 0;
}

int ELM327WifiServer::closeInterface() {
    if (!open) {
        return 0;
    }
    LOG(INFO) << "Closing ELM Server";
    exitRequested = true;
    int result = commInterface->closeInterface();
    result &= socketServer->closeInterface();

    open = false;
    return result;
}


int ELM327WifiServer::sendResponse(byte *buf, int bufSize, int &recvSize, int &clientSockFd) {
    if (recvSize < 2) {
        recvSize = -1;
        return -1;
    }
    int result = 0;
    if (messageContains(buf, recvSize, ELM_CONFIG_PREFIX)) {
        bool success = parseConfiguration(buf, recvSize);
        return sendConfigurationAnswer(clientSockFd, success);
    } else {
        result = parseData(buf, recvSize);
        if (0 == result) {
            return sendDataAnswer(clientSockFd, recvSize, buf, bufSize);
        }
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
    byte *outBuf = new byte[size + 1];

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
    delete[] outBuf;
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

    char param = (char) buf[commandLength];

    bool result = true;
    if (ELM_CONFIG_HEADER == cmd) {
        sendHeaders = param == ELM_CONFIG_ENABLE[0];
    } else if (ELM_CONFIG_SPACES == cmd) {
        sendSpaces = param == ELM_CONFIG_ENABLE[0];
    } else if (ELM_CONFIG_PROTOCOL == cmd) {
        if (param != supportedProtocol) {
            result = false;
        }
    } else if (ELM_CONFIG_ECHO == cmd && param == ELM_CONFIG_ENABLE[0]) {
        // no echo support.
        result = false;
    }

    delete[] cmd;
    return result;
}


void ELM327WifiServer::handleClient(int clientSockFd) {
    int readSize;
    int bufSize = 1024;
    byte *inBuf = new byte[bufSize];
    byte *buf = new byte[bufSize];
    auto message = vector<byte>();

    int i;
    while (!exitRequested) {
        socketServer->receive(inBuf, bufSize, readSize, clientSockFd);
        if (readSize < 1) {
            continue;
        }

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
        int sendSize = sendResponse(buf, bufSize, msgSize, clientSockFd);
        if (sendSize < 1) {
            close(clientSockFd);
            break;
        }

        message.clear();
    }

    delete[] inBuf;
    delete[] buf;
}

int ELM327WifiServer::sendConfigurationAnswer(int clientSockFd, bool &success) const {
    string status;
    if (success) {
        status = ELM_FLOW_OK;
    } else {
        status = ELM_FLOW_ERROR;
    }

    status += ELM_FLOW_NEWLINE_PROMPT;
    return sendString(clientSockFd, status);
}

int ELM327WifiServer::sendDataAnswer(int clientSockFd, int dataSize, byte *cmdBuf, int bufSize) const {
    int readSize;
    byte service = (byte) ((int) cmdBuf[0] + ANSWER_OFFSET);
    byte pid = cmdBuf[1];
    readSize = commInterface->send(cmdBuf, dataSize);
    if (readSize != dataSize) {
        return readSize;
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
        string space = "";
        if (sendSpaces) {
            space = " ";
        }
        message = getHeader() + space + ss2.str() + space + message;
    }

    std::transform(message.begin(), message.end(), message.begin(), ::toupper);
    message += ELM_FLOW_NEWLINE_PROMPT;
    return sendString(clientSockFd, message);
}

int ELM327WifiServer::sendString(int clientSockFd, const string &st) const {
    int retVal = socketServer->send((byte *) st.c_str(), static_cast<int>(st.size()), clientSockFd);
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


