//
// Created by me on 14/12/18.
//


#include <gtest/gtest.h>
#include <vector>
#include "../../../src/CAN/CanIsoTP.h"
#include "../../../src/Config.h"

using namespace std;

#define CAN_INTERFACE "vcan0"

void initIsoTp(CanIsoTP* vehicleCAN, CanIsoTP* testerCAN){
    vehicleCAN->openIsoTp(TESTER_ID, VEHICLE_ID, const_cast<char *>(CAN_INTERFACE));
    testerCAN->openIsoTp(VEHICLE_ID, TESTER_ID, const_cast<char *>(CAN_INTERFACE));
}

void doTest(vector<byte> &request) {
    auto vehicleCAN = new CanIsoTP();
    auto testerCAN = new CanIsoTP();
    initIsoTp(vehicleCAN, testerCAN);
    testerCAN->send(request.data(), static_cast<int>(request.size()));

    auto buf = (byte *) malloc(request.size());
    int readSize;
    vehicleCAN->receive(buf, static_cast<int>(request.size()), readSize);

    EXPECT_EQ(readSize, static_cast<int> (request.size()));

    long i;
    for (i = 0; i < request.size(); i++) {
        EXPECT_EQ(request.at(i), buf[i]);
    }
}

TEST(CanIsoTp, SingleFrameMessage) { // NOLINT(cert-err58-cpp)
    vector<byte> request  {(byte) 0x09 , (byte)0x02};

    doTest(request);
}

TEST(CanIsoTp, MultiFrameMessage) { // NOLINT(cert-err58-cpp)
    // Request: 0x02 0x09 0x02 0x00 0x00 0x00 0x00 0x00
    // Response: flow control has been removed because it will be added by kernel driver.
    // 0x10 0x14 0x49 0x02 0x01 0x57 0x4d 0x45
    //0x21 0x34 0x35 0x33 0x30 0x34 0x34 0x32
    //0x22 0x59 0x30 0x33 0x33 0x32 0x30 0x34
    vector<byte> request{
            (byte) 0x49, (byte) 0x02, (byte) 0x01, (byte) 0x57, (byte) 0x4d, (byte) 0x45,
            (byte) 0x21, (byte) 0x34, (byte) 0x35, (byte) 0x33, (byte) 0x30, (byte) 0x34, (byte) 0x34, (byte) 0x32,
            (byte) 0x22, (byte) 0x59, (byte) 0x30, (byte) 0x33, (byte) 0x33, (byte) 0x32, (byte) 0x30, (byte) 0x34
    };

    doTest(request);
}
