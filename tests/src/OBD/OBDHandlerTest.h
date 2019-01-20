//
// Created by me on 14/12/18.
//

#ifndef OPEN_OBD2_OBDHANDLERTEST_H
#define OPEN_OBD2_OBDHANDLERTEST_H

#define CAN_INTERFACE "vcan0"

#include "easylogging++.h"
#include "gtest/gtest.h"

#include "../../../src/Config.h"
#include "../../../src/OBD/OBDHandler.h"
#include "../../../src/communication/CanIsoTP.h"

const byte RequestServiceID = (byte) 0x01;
const byte ResponseServiceID = (byte) 0x41;


OBDHandler *getHandler();

void compareResponse(byte *expectedResponse, byte *actualResponse, int size);
void compareResponse(vector<byte> expectedResponse, byte *actualResponse);

OBDHandler *doTest(vector<byte> request, vector<byte> response);

#endif //OPEN_OBD2_OBDHANDLERTEST_H
