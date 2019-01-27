//
// Created by me on 26/01/19.
//

#ifndef OPEN_OBD2_SERIALCLIENT_H
#define OPEN_OBD2_SERIALCLIENT_H


#include "SocketCommunicationBase.h"
#include "../common/conversion.h"
#include "ELM327.h"
#include <vector>

class SerialClient : public ICommunicationInterface {
private:
    int baudrate;
    char *ttyDevice;
    int ttyFd;
public:
    SerialClient(int baudrate, char *ttyDevice);

public: // override ICloseable
    int closeInterface() override;

    int openInterface() override;

public: // override ICommunicationInterface
    int send(byte *buf, int buflen) override;

    void receive(byte *buffer, int buffSize, int &readSize) override;

    int configureInterface() override;

public:
    const static inline vector<int> POSSILBE_BAUDRATES{38400, 9600, 230400, 115200, 57600, 19200};

    int openSerialPortAutoBaud();

    int openSerialPort();
};

#endif //OPEN_OBD2_SERIALCLIENT_H
