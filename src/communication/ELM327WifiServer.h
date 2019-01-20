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


public: // ELM327WifiClient
    int closeInterface();

    int openInterface();

    int parseMessage(byte *data, int &size);

private:
    void serve();

    void sendDataAnswer(int clientSockFd, int dataSize, byte *cmdBuf, int bufSize) const;

    int parseConfiguration(byte *data, int &size);

    int parseData(byte *data, int &size) const;

    void serveClient(int clientSockFd);

    void sendConfigurationAnswer(int clientSockFd, const byte *cmdBuf, int rs) const;

    void sendString(int clientSockFd, const string &st) const;
};


#endif //OPEN_OBD2_SIMULATEDELM327_H
