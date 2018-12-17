//
// Created by me on 14/12/18.
//

#ifndef OPEN_OBD2_OBDHANDLERTEST_H
#define OPEN_OBD2_OBDHANDLERTEST_H

#define CAN_INTERFACE "vcan0"

#include "../../../src/Config.h"
#include "../../../src/OBD/OBDHandler.h"
#include "easylogging++.h"
#include "../../../src/CAN/CanIsoTP.h"
#include "gtest/gtest.h"


OBDHandler *getHandler();

void compareResponse(vector<byte> expectedResponse, byte *actualResponse);

OBDHandler *doTest(vector<byte> request, vector<byte> response);

#endif //OPEN_OBD2_OBDHANDLERTEST_H
