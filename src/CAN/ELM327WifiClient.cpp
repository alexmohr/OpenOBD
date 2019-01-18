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
#include <spqr.hpp>

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

void ELM327WifiClient::receive(byte *buf, int buffSize, int &readSize) {
    closeInterface();
    openInterface();
    bool successFullRead = readDeviceBuffer(buf, buffSize, readSize);
    if (!successFullRead) {
        LOG(ERROR) << "failed to retrieve data";
        readSize = -1;
        return;
    }

    parseData(buf, buffSize, readSize);
}

bool ELM327WifiClient::readDeviceBuffer(byte *buf, int buffSize, int &readSize) {
    auto t0 = chrono::high_resolution_clock::now();
    bool hasTimeout;

    byte *tempReadBuffer = (byte *) malloc(buffSize);
    memset(buf, 0, buffSize);
    memset(tempReadBuffer, 0, buffSize);

    int additionalReadSize;
    readSize = 0;
    do {
        SocketCommunicationBase::receive(tempReadBuffer, buffSize, additionalReadSize);
        if (additionalReadSize > 0) {
            if (readSize + readSize < buffSize) {
                // append the additional received data to our existing buf.
                memcpy(buf + readSize, tempReadBuffer, additionalReadSize);
                readSize += additionalReadSize;
            } else {
                LOG(ERROR) << "Appending to buf would lead to overflow. aborting read";
                readSize = -1;
                return false;
            }

        }

        hasTimeout = chrono::_V2::system_clock::now() - t0 > 500ms;
    } while ((char) buf[readSize - 1] != '\r' && !hasTimeout);

    delete tempReadBuffer;
    return readSize > 0;
}

void ELM327WifiClient::parseData(byte *buf, const int bufSize, int &readSize) {
    int startIndex = getDataStartIndex(buf, readSize);
    if (startIndex < 0 || readSize < 1) {
        readSize = -1;
        return;
    }

    if (usedProtocol > maxSaeIndex) {
        removeHeader(buf, bufSize, readSize, 5);
    } else {
        removeHeader(buf, bufSize, readSize, 6);
    }

    byte *bufCopy = (byte *) malloc(readSize);
    memcpy(bufCopy, buf, readSize);
    memset(buf, 0, bufSize);

    int bufIndex;
    int dataIndex = 0;
    byte byteValue;
    char tempCharBuf[2];


    for (bufIndex = 0; bufIndex <= readSize; bufIndex += 2) {
        memset(&tempCharBuf, 0, 2);
        memcpy(tempCharBuf, bufCopy + bufIndex, 2);

        byteValue = (byte) convertHexToInt(string(tempCharBuf));
        buf[dataIndex++] = byteValue;
    }

    delete bufCopy;
}

void ELM327WifiClient::removeHeader(byte *buf, const int bufSize, int &readSize, int byteCountToRemove) const {
    if (readSize < byteCountToRemove) {
        readSize = -1;
        return;
    }

    byte *tempCharBuf = (byte *) malloc(readSize);
    memcpy(tempCharBuf, buf + byteCountToRemove, readSize);
    memset(buf, 0, bufSize);
    memcpy(buf, tempCharBuf, readSize);
    readSize -= byteCountToRemove;
    delete tempCharBuf;
}

int ELM327WifiClient::getDataStartIndex(const byte *buf, const int recvSize) const {
    int startIndex = 0;
    while (((char) buf[startIndex] == '\r' || (char) buf[startIndex] == '>')
           && startIndex < recvSize) {
        startIndex++;
    }

    if (startIndex == recvSize || messageContains(buf, recvSize, "STOP")) {
        LOG(DEBUG) << "Failed to parse frame";
        return -1;
    }

    return startIndex;
}

int ELM327WifiClient::send(byte *buf, int buflen) {
    std::stringstream ss;
    for (int i(0); i < buflen; ++i) {
        ss << std::hex << std::setfill('0') << std::setw(2) << (int) buf[i];
    }

    string dataString = ss.str();
    dataString = dataString + '\r';
    return sendString(dataString);
}

int ELM327WifiClient::configureInterface() {
    int bufSize = 1024;
    bool configSuccess = true;

    byte *buf = (byte *) malloc(bufSize);

    // echo OFF
    configSuccess &= configurationCommandSendSuccessfully(buf, bufSize, "ATE0");

    // headers ON
    configSuccess &= configurationCommandSendSuccessfully(buf, bufSize, "ATH1");

    // spaces OFF
    configSuccess &= configurationCommandSendSuccessfully(buf, bufSize, "ATS0");

    if (!configSuccess) {
        LOG(ERROR) << "Configuration of interface failed.";
        return 1;
    }

    return findProtocol(bufSize, buf);
}

int ELM327WifiClient::findProtocol(int bufSize, byte *buf) {
    vector<char *> searchStrings{
            const_cast<char *>("SEARCHING"),
            const_cast<char *>("BUS INIT")
    };

    const int protocolCount = 10;
    int protocolNumber;

    bool protocolFound = false;
    for (protocolNumber = 1; protocolNumber <= protocolCount; protocolNumber++) {
        protocolFound = isProtocolWorking(bufSize, buf, searchStrings, protocolNumber);
        if (protocolFound) {
            break;
        }

        LOG(DEBUG) << "Protocol " << protocolNumber << " failed: " << (char *) buf;
    }

    if (!protocolFound) {
        LOG(ERROR) << "Unable to find protocol";
        return 1;
    }

    LOG(DEBUG) << "Protocol can be used: " << protocolNumber;
    usedProtocol = protocolNumber;
    return 0;
}

bool ELM327WifiClient::isProtocolWorking(
        int bufSize, byte *buf, const vector<char *> &searchStrings, int protocolNumber) {
    bool searchRunning;
    int strCompRes = 0;
    const string protocolTestMessage = "0101\r";

    if (!configurationCommandSendSuccessfully(buf, bufSize, "ATSP" + to_string(protocolNumber))) {
        return false;
    }

    // will trigger search.
    int recvSize = sendString(protocolTestMessage);
    do {
        std::this_thread::sleep_for(150ms);
        searchRunning = false;
        memset(buf, 0, bufSize);
        SocketCommunicationBase::receive(buf, bufSize, recvSize);

        if (0 == recvSize) {
            LOG(DEBUG) << "Did not receive an answer from device";
            searchRunning = true;
            this_thread::sleep_for(150ms);
        }

        for (const auto &searchString : searchStrings) {
            strCompRes = strncmp(searchString, (char *) buf, sizeof(&searchString - 1));
            if (0 == strCompRes) {
                searchRunning = true;
                break;
            }
        }
    } while (searchRunning);

    return isNumber(buf[0]) || isNumber(buf[1]);
}

bool ELM327WifiClient::configurationCommandSendSuccessfully(byte *buf, int bufSize, string data) {
    int recvSize = 0;
    data += '\r';

    closeInterface();
    openInterface();

    LOG(DEBUG) << "Sending configuration command: " << data;
    sendString(data);
    this_thread::sleep_for(150ms);
    SocketCommunicationBase::receive(buf, bufSize, recvSize);

    return messageContains(buf, recvSize, "OK");
}

bool ELM327WifiClient::messageContains(const byte *buf, int recvSize, string data) const {
    if (recvSize < (int) data.size()) {
        return false;
    }

    int i;
    for (i = 0; i < (int) (recvSize - data.size()); i++) {
        if (0 == strncmp(data.c_str(), (char *) buf + i, data.size())) {
            return true;
        }
    }
    return false;
}

int ELM327WifiClient::sendString(const string &data) {
    LOG(DEBUG) << "Sending: " << data;
    return SocketCommunicationBase::send((byte *) data.c_str(), static_cast<int>(data.size()));
}
