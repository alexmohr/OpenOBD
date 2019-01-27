//
// Created by me on 03/01/19.
//

#ifndef OPEN_OBD2_ELM327_CLIENT_H
#define OPEN_OBD2_ELM327_CLIENT_H

#include "SocketClient.h"
#include "ELM327.h"

#include <string>
#include <vector>
#include <map>


class ELMClient : public ICommunicationInterface {
private:
    ICommunicationInterface *elmInterface;

    ElmProtocol *usedProtocol;


public:
    explicit ELMClient(ICommunicationInterface *socketClient);


public: // override ICommunicationInterface
    void receive(byte *buf, int bufSize, int &readSize) override;

    int send(byte *buf, int bufSize) override;

    int openInterface() override;

    int closeInterface() override;

    int configureInterface() override;

private:
    bool configurationCommandSendSuccessfully(byte *buf, int bufSize, string data);

    void parseData(byte *buf, int bufSize, int &readSize);

    int findProtocol(int bufSize, byte *buf);

    int sendString(const string &data);

    bool
    isProtocolWorking(int bufSize, byte *buf, const vector<char *> &searchStrings, int protocolNumber);

    bool readDeviceBuffer(byte *buf, int bufSize, int &readSize);

    int getDataStartIndex(const byte *buf, int recvSize) const;

    void removeHeader(byte *buf, int bufSize, int &readSize, int byteCountToRemove) const;

    void removeFooter(byte *buf, int bufSize, int &readSize, int byteCountToRemove) const;
};


#endif //OPEN_OBD2_ELM327_CLIENT_H
