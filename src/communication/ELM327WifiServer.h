//
// Created by me on 12/01/19.
//

#ifndef OPEN_OBD2_SIMULATEDELM327_H
#define OPEN_OBD2_SIMULATEDELM327_H

#include <string>
#include <thread>
#include "easylogging++.h"
#include "ICommunicationInterface.h"
#include "ISocketServerClientHandler.h"
#include "ISocketServer.h"
#include "ELMClient.h"
#include "../OBD/OBDHandler.h"

using namespace std;

class ELM327WifiServer : public ISocketServerClientHandler, public ICloseable {
private: // config
    bool sendHeaders = false;
    bool sendSpaces = false;
    // todo this should be configured.
    char supportedProtocol = '6';
private:
    bool exitRequested;
    int port;
    string interface;
    bool open;
    ICommunicationInterface *commInterface;
    ISocketServer *socketServer;
public:
    ELM327WifiServer(int port,
                     ICommunicationInterface *commInterface,
                     ISocketServer *socketServer);

    bool isOpen();

public: // ISocketServerClientHandler
    void handleClient(int clientSockFd) override;

public:
    int closeInterface() override;

    int openInterface() override;

private:

    int sendResponse(byte *buf, int bufSize, int &recvSize, int &clientSockFd);

    int sendDataAnswer(int clientSockFd, int dataSize, byte *cmdBuf, int bufSize) const;

    bool parseConfiguration(byte *buf, int &recvSize);

    int parseData(byte *data, int &size) const;

    int sendConfigurationAnswer(int clientSockFd, bool &success) const;

    int sendString(int clientSockFd, const string &st) const;

    string getHeader() const;
};


#endif //OPEN_OBD2_SIMULATEDELM327_H
