//
// Created by me on 03/01/19.
//

#include "ELMClient.h"
#include "easylogging++.h"
#include "../common/conversion.h"
#include <chrono>
#include <iomanip>
#include <thread>

using namespace std::chrono_literals;


ELMClient::ELMClient(ICommunicationInterface *socketClient) {
    this->elmInterface = socketClient;

}

int ELMClient::openInterface() {
    return elmInterface->openInterface();
}

int ELMClient::closeInterface() {
    return elmInterface->closeInterface();
}

void ELMClient::receive(byte *buf, int bufSize, int &readSize) {
    bool successFullRead = readDeviceBuffer(buf, bufSize, readSize);
    if (successFullRead) {
        parseData(buf, bufSize, readSize);
    }
}

bool ELMClient::readDeviceBuffer(byte *buf, int bufSize, int &readSize) {
    auto t0 = chrono::high_resolution_clock::now();
    bool hasTimeout;

    byte *tempReadBuffer = new byte[bufSize];
    memset(buf, 0, bufSize);
    memset(tempReadBuffer, 0, bufSize);

    int additionalReadSize;
    readSize = 0;
    auto startTime = chrono::high_resolution_clock::now();
    bool hasPrompt;
    do {
        elmInterface->receive(tempReadBuffer, bufSize, additionalReadSize);
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
        hasPrompt = readSize > 0 && (char) buf[readSize - 1] == ELM_FLOW_PROMPT;
    } while (!hasPrompt && !hasTimeout);

    if (Config::isDebugLogEnabled()) {
        auto runTime = (chrono::high_resolution_clock::now() - startTime);
        LOG(DEBUG) << "Getting value from ecu took: "
                   << chrono::duration_cast<chrono::milliseconds>(runTime).count() << "ms\n"
                   << "Received the following data: " << (char *) buf;
    }


    delete[] tempReadBuffer;
    if (readSize < 1) {
        // reset interface
        closeInterface();
        openInterface();
        return false;
    }
    return true;
}

void ELMClient::parseData(byte *buf, const int bufSize, int &readSize) {
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

    byte *bufCopy = new byte[readSize];
    memcpy(bufCopy, buf, readSize);
    memset(buf, 0, bufSize);

    int bufIndex;
    int dataIndex = 0;
    byte byteValue;
    char tempCharBuf[2];

    for (bufIndex = 0; bufIndex < readSize - 1; bufIndex += 2) {
        memset(&tempCharBuf, 0, 2);
        memcpy(tempCharBuf, bufCopy + bufIndex, 2);

        byteValue = (byte) convertHexToInt(string(tempCharBuf));
        buf[dataIndex++] = byteValue;
    }
    readSize = dataIndex - 1;
    delete[] bufCopy;
}


void ELMClient::removeFooter(byte *buf, int bufSize, int &readSize, int byteCountToRemove) const {
    if (readSize < byteCountToRemove) {
        readSize = -1;
        return;
    }

    byte *tempCharBuf = new byte[readSize];
    memcpy(tempCharBuf, buf, readSize - byteCountToRemove);
    memset(buf, 0, bufSize);
    memcpy(buf, tempCharBuf, readSize);
    readSize -= byteCountToRemove;
    delete[] tempCharBuf;
}

void ELMClient::removeHeader(byte *buf, const int bufSize, int &readSize, int byteCountToRemove) const {
    if (readSize < byteCountToRemove) {
        readSize = -1;
        return;
    }

    byte *tempCharBuf = new byte[readSize];
    memcpy(tempCharBuf, buf + byteCountToRemove, readSize);
    memset(buf, 0, bufSize);
    memcpy(buf, tempCharBuf, readSize);
    readSize -= byteCountToRemove;
    delete[] tempCharBuf;
}

int ELMClient::getDataStartIndex(const byte *buf, const int recvSize) const {
    int startIndex = 0;
    while ((char) buf[startIndex] == ELM_FLOW_PROMPT && startIndex < recvSize) {
        startIndex++;
    }

    if (messageContains(buf, recvSize, ELM_FLOW_STOP)) {
        LOG(DEBUG) << "Adapter received interrupt.";
        return -1;
    }

    if (startIndex == recvSize) {
        LOG(DEBUG) << "Failed to parse frame";
        return -1;
    }

    return startIndex;
}

int ELMClient::send(byte *buf, int bufSize) {
    std::stringstream ss;
    for (int i(0); i < bufSize; ++i) {
        ss << std::hex << std::setfill('0') << std::setw(2) << (int) buf[i];
    }

    string dataString = ss.str();
    dataString = dataString + ELM_FLOW_NEWLINE;
    return sendString(dataString);
}

int ELMClient::configureInterface() {
    int bufSize = 1024;
    byte *buf = new byte[bufSize];

    elmInterface->configureInterface();

    // echo OFF
    string command = getElmConfigString(ELM_CONFIG_ECHO, false);
    string log = "Did not receive positive response for command: ";
    if (!configurationCommandSendSuccessfully(buf, bufSize, command)) {
        LOG(ERROR) << log << command;
        delete[] buf;
        return 1;
    }

    // headers ON
    command = getElmConfigString(ELM_CONFIG_HEADER, true);
    if (!configurationCommandSendSuccessfully(buf, bufSize, command)) {
        LOG(ERROR) << log << command;
        delete[] buf;
        return 1;
    }

    // spaces OFF
    command = getElmConfigString(ELM_CONFIG_SPACES, false);
    if (!configurationCommandSendSuccessfully(buf, bufSize, command)) {
        LOG(ERROR) << log << command;
        delete[] buf;
        return 1;
    }

    return findProtocol(bufSize, buf);
}

int ELMClient::findProtocol(int bufSize, byte *buf) {
    LOG(INFO) << "Search ELM protocol";
    vector<char *> searchStrings{
            const_cast<char *>("SEARCHING"),
            const_cast<char *>("BUS INIT")
    };

    bool protocolFound = false;
    ElmProtocol *protocol = nullptr;
    for (auto &availableProtocol : availableProtocols) {
        protocol = &availableProtocol.second;
        protocolFound = isProtocolWorking(bufSize, buf, searchStrings, protocol->id);
        if (protocolFound) {
            break;
        }

        LOG(DEBUG) << "Protocol " << protocol->id << " failed: " << (char *) buf;
    }

    if (!protocolFound) {
        LOG(ERROR) << "Unable to find protocol";
        delete[] buf;
        return 1;
    }

    LOG(DEBUG) << "Protocol can be used: " << protocol->name;
    usedProtocol = protocol;
    delete[] buf;
    return 0;
}

bool ELMClient::isProtocolWorking(
        int bufSize, byte *buf, const vector<char *> &searchStrings, int protocolNumber) {
    bool searchRunning, readSuccess;
    int strCompRes = 0;

    string id = convertIntToHex(protocolNumber);
    transform(id.begin(), id.end(), id.begin(), ::toupper);
    if (!configurationCommandSendSuccessfully(buf, bufSize, ELM_CONFIG_PROTOCOL + id)) {
        return false;
    }

    // will trigger search.
    int recvSize = sendString(ELM_PROTOCOL_TEST_MESSAGE);
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

bool ELMClient::configurationCommandSendSuccessfully(byte *buf, int bufSize, string data) {
    int recvSize = 0;
    data += ELM_FLOW_NEWLINE;

    LOG(DEBUG) << "Sending configuration command: " << data;
    sendString(data);
    this_thread::sleep_for(150ms);
    bool success = readDeviceBuffer(buf, bufSize, recvSize);
    if (!success) {
        return false;
    }

    return messageContains(buf, recvSize, ELM_FLOW_OK);
}

int ELMClient::sendString(const string &data) {
    LOG(DEBUG) << "Sending: " << data;
    return elmInterface->send((byte *) data.c_str(), static_cast<int>(data.size()));
}

bool ELMClient::isOpen() {
    return elmInterface->isOpen();
}
