//
// Created by me on 03/01/19.
//

#ifndef OPEN_OBD2_ICOMHANDLER_H
#define OPEN_OBD2_ICOMHANDLER_H

#include <cstddef>

using namespace std;

class ComHandler {
protected:
    int socketHandle = -1;
public:
    virtual int send(byte *buf, int buflen);

    virtual void receive(byte *buffer, int buffSize, int &readSize);

    void closeHandler();
};

#endif //OPEN_OBD2_ICOMHANDLER_H
