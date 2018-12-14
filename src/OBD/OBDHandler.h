//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_OBDHANDLER_H
#define OPEN_OBD2_OBDHANDLER_H

#include "Config.h"


class OBDCommand {
private:
    Service srv;
};


class OBDHandler{
    byte* encodeFrame(Service srv, byte payload[]);
    void decodeFrame(byte* canFrame, Service* srv);
};

#endif //OPEN_OBD2_OBDHANDLER_H
