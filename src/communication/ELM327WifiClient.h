//
// Created by me on 03/01/19.
//

#ifndef OPEN_OBD2_ELM327_H
#define OPEN_OBD2_ELM327_H

#include "SocketClient.h"

#include <string>
#include <vector>
#include <map>

struct ElmProtocol {
    ElmProtocol(string name, int id, int canIdLength) {
        this->name = name;
        this->canIdBitLength = canIdLength;
        this->id = id;
    }

    string name;
    int canIdBitLength;
    int id;
};

class ELM327WifiClient : public ICommunicationInterface {
private:
    ICommunicationInterface *socketClient;

    ElmProtocol *usedProtocol;
private:
    const string CONFIG_PREFIX = "AT";
    const string CONFIG_SPACES = CONFIG_PREFIX + "S";
    const string CONFIG_HEADER = CONFIG_PREFIX + "H";
    const string CONFIG_ECHO = CONFIG_PREFIX + "E";
public:

    static inline map<int, ElmProtocol> availableProtocols = {
            {1,  ElmProtocol("SAE_J1850_PWM", 1, 0)},
            {2,  ElmProtocol("SAE_J1850_VPW", 2, 0)},
            {3,  ElmProtocol("ISO_9141_2", 3, 0)},
            {4,  ElmProtocol("ISO_14230_4_5baud", 4, 0)},
            {5,  ElmProtocol("ISO_14230_4_fast", 5, 0)},
            {6,  ElmProtocol("ISO_15765_4_11bit_500k", 6, 11)},
            {7,  ElmProtocol("ISO_15765_4_29bit_500k", 7, 29)},
            {8,  ElmProtocol("ISO_15765_4_11bit_250k", 8, 11)},
            {9,  ElmProtocol("ISO_15765_4_29bit_250k", 9, 29)},
            {10, ElmProtocol("SAE_J1939", 10, 11)}
    };

public:
    explicit ELM327WifiClient(ICommunicationInterface *socketClient);

//    ~ELM327WifiClient() override = default;

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

    bool messageContains(const byte *buf, int recvSize, string data) const;

    void removeHeader(byte *buf, int bufSize, int &readSize, int byteCountToRemove) const;

    void removeFooter(byte *buf, int bufSize, int &readSize, int byteCountToRemove) const;
};


#endif //OPEN_OBD2_ELM327_H
