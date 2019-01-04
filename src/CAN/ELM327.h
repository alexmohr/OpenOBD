//
// Created by me on 03/01/19.
//

#ifndef OPEN_OBD2_ELM327_H
#define OPEN_OBD2_ELM327_H

#include "ComHandler.h"

class ELM327 : public ComHandler {
private:
    int port;
    char *host;
public:
    ELM327(int port, char *host);

    int openElm();

public: // override ComHandler
    void receive(byte *buffer, int buffSize, int &readSize) override;

    int send(byte *buf, int buflen) override;

private:
    void parseData(byte *buffer, int &readSize);

};


#endif //OPEN_OBD2_ELM327_H
