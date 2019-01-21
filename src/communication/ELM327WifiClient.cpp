//
// Created by me on 03/01/19.
//

#include "ELM327WifiClient.h"
#include "easylogging++.h"
#include "../common/conversion.h"
#include <chrono>
#include <iomanip>
#include <thread>

using namespace std::chrono_literals;


ELM327WifiClient::ELM327WifiClient(ICommunicationInterface *socketClient) {
    this->socketClient = socketClient;

}

int ELM327WifiClient::openInterface() {
    return socketClient->openInterface();
}

int ELM327WifiClient::closeInterface() {
    return socketClient->closeInterface();
}

void ELM327WifiClient::receive(byte *buf, int bufSize, int &readSize) {
    bool successFullRead = readDeviceBuffer(buf, bufSize, readSize);
    if (!successFullRead) {
        LOG(ERROR) << "failed to retrieve data";
        readSize = -1;
    } else {
        parseData(buf, bufSize, readSize);
    }
}

bool ELM327WifiClient::readDeviceBuffer(byte *buf, int bufSize, int &readSize) {
    auto t0 = chrono::high_resolution_clock::now();
    bool hasTimeout;

    byte *tempReadBuffer = (byte *) malloc(bufSize);
    memset(buf, 0, bufSize);
    memset(tempReadBuffer, 0, bufSize);

    int additionalReadSize;
    readSize = 0;
    auto startTime = chrono::high_resolution_clock::now();
    do {
        socketClient->receive(tempReadBuffer, bufSize, additionalReadSize);
        if (additionalReadSize > 0) {
            if (readSize + readSize < bufSize) {
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
    } while ((char) buf[readSize - 1] != '>' && !hasTimeout);
    auto runTime = (chrono::high_resolution_clock::now() - startTime);
    LOG(DEBUG) << "Getting value from ecu took: " << chrono::duration_cast<chrono::milliseconds>(runTime).count()
               << "ms";
    delete tempReadBuffer;
    return readSize > 0;
}

void ELM327WifiClient::parseData(byte *buf, const int bufSize, int &readSize) {
    int startIndex = getDataStartIndex(buf, readSize);
    if (startIndex < 0 || readSize < 1) {
        readSize = -1;
        return;
    }

    if (usedProtocol->canIdBitLength == 0) {
        removeHeader(buf, bufSize, readSize, 6);
        removeFooter(buf, bufSize, readSize, 1);
    } else {
        if (usedProtocol->canIdBitLength == 11) {
            removeHeader(buf, bufSize, readSize, 5);
        } else {
            removeHeader(buf, bufSize, readSize, 10);
        }
    }
    if (readSize < 1) {
        return;
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
    readSize = dataIndex - 2;
    delete bufCopy;
}


void ELM327WifiClient::removeFooter(byte *buf, int bufSize, int &readSize, int byteCountToRemove) const {
    if (readSize < byteCountToRemove) {
        readSize = -1;
        return;
    }

    byte *tempCharBuf = (byte *) malloc(readSize);
    memcpy(tempCharBuf, buf, readSize - byteCountToRemove);
    memset(buf, 0, bufSize);
    memcpy(buf, tempCharBuf, readSize);
    readSize -= byteCountToRemove;
    delete tempCharBuf;
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
    while ((char) buf[startIndex] == '>'
           && startIndex < recvSize) {
        startIndex++;
    }

    if (messageContains(buf, recvSize, "STOP")) {
        LOG(DEBUG) << "Adapter received interrupt.";
        return -1;
    }

    if (startIndex == recvSize) {
        LOG(DEBUG) << "Failed to parse frame";
        return -1;
    }

    return startIndex;
}

int ELM327WifiClient::send(byte *buf, int bufSize) {
    std::stringstream ss;
    for (int i(0); i < bufSize; ++i) {
        ss << std::hex << std::setfill('0') << std::setw(2) << (int) buf[i];
    }

    string dataString = ss.str();
    dataString = dataString + '\r';
    return sendString(dataString);
}

int ELM327WifiClient::configureInterface() {
    int bufSize = 1024;
    byte *buf = (byte *) malloc(bufSize);

    // echo OFF
    string command = CONFIG_ECHO + "0";
    string log = "Did not receive positive response for command: ";
    if (!configurationCommandSendSuccessfully(buf, bufSize, command)) {
        LOG(ERROR) << log << command;
        return 1;
    }

    // headers ON
    command = CONFIG_HEADER + "1";
    if (!configurationCommandSendSuccessfully(buf, bufSize, command)) {
        LOG(ERROR) << log << command;
        return 1;
    }

    // spaces OFF
    command = CONFIG_SPACES + "0";
    if (!configurationCommandSendSuccessfully(buf, bufSize, command)) {
        LOG(ERROR) << log << command;
        return 1;
    }

    return findProtocol(bufSize, buf);
}

int ELM327WifiClient::findProtocol(int bufSize, byte *buf) {
    vector<char *> searchStrings{
            const_cast<char *>("SEARCHING"),
            const_cast<char *>("BUS INIT")
    };

    bool protocolFound = false;
    ElmProtocol *protocol = nullptr;
    for (auto &availableProtocol : ELM327WifiClient::availableProtocols) {
        protocol = &availableProtocol.second;
        protocolFound = isProtocolWorking(bufSize, buf, searchStrings, protocol->id);
        if (protocolFound) {
            break;
        }

        LOG(DEBUG) << "Protocol " << protocol->id << " failed: " << (char *) buf;
    }

    if (!protocolFound) {
        LOG(ERROR) << "Unable to find protocol";
        return 1;
    }

    LOG(DEBUG) << "Protocol can be used: " << protocol->name;
    usedProtocol = protocol;
    return 0;
}

bool ELM327WifiClient::isProtocolWorking(
        int bufSize, byte *buf, const vector<char *> &searchStrings, int protocolNumber) {
    bool searchRunning, readSuccess;
    int strCompRes = 0;
    const string protocolTestMessage = "0101\r";

    string id = convertIntToHex(protocolNumber);
    transform(id.begin(), id.end(), id.begin(), ::toupper);
    if (!configurationCommandSendSuccessfully(buf, bufSize, "ATSP" + id)) {
        return false;
    }

    // will trigger search.
    int recvSize = sendString(protocolTestMessage);
    auto t0 = chrono::high_resolution_clock::now();
    auto maxTime = 2s;
    do {
        std::this_thread::sleep_for(250ms);
        searchRunning = false;
        memset(buf, 0, bufSize);
        readSuccess = readDeviceBuffer(buf, bufSize, recvSize);
        if (0 == recvSize || !readSuccess) {
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
    } while (searchRunning && chrono::high_resolution_clock::now() - t0 < maxTime);

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
    bool success = readDeviceBuffer(buf, bufSize, recvSize);
    if (!success) {
        return false;
    }

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
    return socketClient->send((byte *) data.c_str(), static_cast<int>(data.size()));
}
