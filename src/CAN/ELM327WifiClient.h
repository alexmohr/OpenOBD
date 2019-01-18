//
// Created by me on 03/01/19.
//

#ifndef OPEN_OBD2_ELM327_H
#define OPEN_OBD2_ELM327_H

#include "SocketCommunicationBase.h"
#include <string>
#include <vector>

class ELM327WifiClient : public SocketCommunicationBase {
private:
    int port;
    char *host;
    int usedProtocol;
    const int maxSaeIndex = 5;
public:
    ELM327WifiClient(int port, char *host);



public: // override SocketCommunicationBase
    void receive(byte *buf, int buffSize, int &readSize) override;
    int send(byte *buf, int buflen) override;

    int openInterface() override;

    int configureInterface() override;
private:
    bool configurationCommandSendSuccessfully(byte *buf, int bufSize, string data);

    void parseData(byte *buf, const int bufSize, int &readSize);

    int findProtocol(int bufSize, byte *buf);

    int sendString(const string &data);

    bool
    isProtocolWorking(int bufSize, byte *buf, const vector<char *> &searchStrings, int protocolNumber);

    bool readDeviceBuffer(byte *buf, int buffSize, int &readSize);

    int getDataStartIndex(const byte *buf, int recvSize) const;

    bool messageContains(const byte *buf, int recvSize, string data) const;

    void removeHeader(byte *buf, const int bufSize, int &readSize, int byteCountToRemove) const;
};


#endif //OPEN_OBD2_ELM327_H
