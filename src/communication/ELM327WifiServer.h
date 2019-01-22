//
// Created by me on 12/01/19.
//

#ifndef OPEN_OBD2_SIMULATEDELM327_H
#define OPEN_OBD2_SIMULATEDELM327_H

#include <string>
#include <thread>
#include "easylogging++.h"
#include "ICommunicationInterface.h"
#include "ELM327WifiClient.h"
#include "../OBD/OBDHandler.h"

using namespace std;

class ELM327WifiServer {
private: // config
    bool sendHeaders = false;
    bool sendSpaces = false;
    // todo this should be configured.
    const string supportedProtocol = "6";
private:
    int port;
    string interface;
    bool exitRequested;
    std::thread tServeThread;
    bool open;
    int socketHandle;
    ICommunicationInterface *commInterface;
public:
    ELM327WifiServer(int port, ICommunicationInterface *commInterface);

    bool isOpen();


public:
    int closeInterface();

    int openInterface();

private:

    int sendResponse(byte *buf, int bufSize, int &recvSize, int &clientSockFd);

    void serve();

    void sendDataAnswer(int clientSockFd, int dataSize, byte *cmdBuf, int bufSize) const;

    bool parseConfiguration(byte *buf, int &recvSize);

    int parseData(byte *data, int &size) const;

    void serveClient(int clientSockFd);

    void sendConfigurationAnswer(int clientSockFd, bool &success) const;

    int sendString(int clientSockFd, const string &st) const;

    string getHeader() const;
};


#endif //OPEN_OBD2_SIMULATEDELM327_H
