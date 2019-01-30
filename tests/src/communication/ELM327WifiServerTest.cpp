//
// Created by me on 14/01/19.
//

#include <thread>
#include <gtest/gtest.h>
#include "../../../src/communication/ELM327WifiServer.h"
#include "../MockCommInterface.h"


const int port = 35000;

class MockSocketServer : public ISocketServer {
private:
    ISocketServerClientHandler *handler;

    byte *recvBuf = new byte[1024];
    int readSize;

    byte *sendBuf = new byte[1024];
    int sendSize;

public:
    bool hasSend = false;
    bool hasReceived = false;
public:
    ~MockSocketServer() {
        delete[] recvBuf;
        delete[] sendBuf;
    }

public:
    void setNextReceive(byte *buf, int readSize) {
        memcpy(recvBuf, buf, readSize);
        this->readSize = readSize;
        hasReceived = false;
    }

    void getLastSend(byte *buf, int &size) {
        memcpy(buf, sendBuf, sendSize);
        memset(sendBuf, 0, sendSize);
        size = sendSize;
        hasSend = false;
    }

    void serve() {
        handler->handleClient(0);
    }

public: // ISocketServer
    void setClientHandler(ISocketServerClientHandler *handler) override {
        this->handler = handler;
    }

    void receive(byte *buf, int bufSize, int &readSize, int socketHandle) override {
        if (hasReceived) {
            readSize = 0;
            return;
        }

        readSize = this->readSize;
        memcpy(buf, this->recvBuf, readSize);
        hasReceived = true;
    }

    int send(byte *buf, int bufSize, int socketHandle) override {
        if (hasSend) {
            return 0;
        }

        memcpy(sendBuf, buf, bufSize);
        hasSend = true;
        sendSize = bufSize;
        return bufSize;
    }

    int closeInterface() override {
        return 0;
    }

    int openInterface() override {
        return 0;
    }
};

const string CONFIG_OK = ELM_FLOW_OK + ELM_FLOW_NEWLINE_PROMPT;
const string CONFIG_NOT_OK = ELM_FLOW_ERROR + ELM_FLOW_NEWLINE_PROMPT;

void waitForData(shared_ptr<MockSocketServer> mockSocketServer) {
    while (!mockSocketServer->hasSend || !mockSocketServer->hasReceived) {
        usleep(100);
    }
}

void testResult(shared_ptr<MockSocketServer> mockSocketServer, byte *buf, const string &result) {
    waitForData(mockSocketServer);

    int recvSize;
    mockSocketServer->getLastSend(buf, recvSize);
    bool contains = messageContains(buf, recvSize, result);
    EXPECT_TRUE(contains);
}

void testConfiguredData(shared_ptr<MockSocketServer> mockSocketServer, byte *buf,
                        bool sendsSpaces, bool sendsHeader) {

    const string DATA_QUERY = "0100";
    string config = DATA_QUERY + ELM_FLOW_NEWLINE_PROMPT;
    int recvSize;
    mockSocketServer->setNextReceive((byte *) config.c_str(), static_cast<int>(config.size()));

    waitForData(mockSocketServer);

    mockSocketServer->getLastSend(buf, recvSize);
    bool hasHeader = messageContains(buf, recvSize, ELM_HEADER_CAN_11_BIT);
    bool hasSpaces = messageContains(buf, recvSize, " ");

    EXPECT_EQ(hasHeader, sendsHeader);
    EXPECT_EQ(hasSpaces, sendsSpaces);
}


void testSetConfig(shared_ptr<MockSocketServer> mockSocketServer, byte *buf, bool value,
                   const string &configOption, const string &result) {
    string config = getElmConfigString(configOption, value) + ELM_FLOW_NEWLINE;
    mockSocketServer->setNextReceive((byte *) config.c_str(), static_cast<int>(config.size()));
    testResult(mockSocketServer, buf, result);
}

void testProtocols(shared_ptr<MockSocketServer> mockSocketServer, byte *buf) {
    string config;
    for (auto &protocol: availableProtocols) {
        config = ELM_CONFIG_PROTOCOL + to_string(protocol.first) + ELM_FLOW_NEWLINE;
        mockSocketServer->setNextReceive((byte *) config.c_str(), static_cast<int>(config.size()));
        string result;
        if (protocol.first == 6) {
            result = CONFIG_OK;
        } else {
            result = CONFIG_NOT_OK;
        }

        testResult(mockSocketServer, buf, result);
    }
}


void testConfigWithData(shared_ptr<MockSocketServer> mockSocketServer, byte *buf, bool sendSpaces, bool sendHeader) {
    testSetConfig(mockSocketServer, buf, sendSpaces, ELM_CONFIG_SPACES, CONFIG_OK);
    testSetConfig(mockSocketServer, buf, sendHeader, ELM_CONFIG_HEADER, CONFIG_OK);
    testConfiguredData(mockSocketServer, buf, sendSpaces, sendHeader);
}

void testConfig(shared_ptr<MockSocketServer> mockSocketServer, byte *buf) {
    bool sendSpaces = false;
    bool sendHeader = false;
    testConfigWithData(mockSocketServer, buf, sendSpaces, sendHeader);

    sendSpaces = true;
    sendHeader = true;
    testConfigWithData(mockSocketServer, buf, sendSpaces, sendHeader);

    sendSpaces = false;
    sendHeader = true;
    testConfigWithData(mockSocketServer, buf, sendSpaces, sendHeader);

    sendSpaces = true;
    sendHeader = false;
    testConfigWithData(mockSocketServer, buf, sendSpaces, sendHeader);

    testProtocols(mockSocketServer, buf);
}

TEST(ELM327WifiServer, TestEverything) {
    shared_ptr<MockSocketServer> mockSocketServer = make_shared<MockSocketServer>();
    shared_ptr<MockCommInterface> mockComInterface = make_shared<MockCommInterface>();
    mockComInterface->supportEverything = true;

    auto elm = ELM327WifiServer(port, mockComInterface, mockSocketServer);
    elm.openInterface();
    while (!elm.isOpen()) {
        usleep(1000);
    }

    std::thread tServer = thread(&MockSocketServer::serve, mockSocketServer);

    int bufSize = 1024;

    byte *buf = new byte[bufSize];
    testConfig(mockSocketServer, buf);


    elm.closeInterface();
    while (elm.isOpen()) {
        usleep(1000);
    }

    tServer.join();
    delete[] buf;
}
