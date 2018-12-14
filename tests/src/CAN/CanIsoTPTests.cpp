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

TEST(CanIsoTp, SingleFrameMessage){
    vector<byte> request  {(byte) 0x09 , (byte)0x02};

    auto vehicleCAN = new CanIsoTP();
    auto testerCAN = new CanIsoTP();
    initIsoTp(vehicleCAN, testerCAN);
    testerCAN->send(request.data(), static_cast<int>(request.size()));

    byte* buf = (byte*)malloc(request.size());
    int readSize;
    vehicleCAN->receive(buf, static_cast<int>(request.size()), readSize);

    EXPECT_EQ(readSize, static_cast<int> (request.size()));

    long i;
    for (i = 0; i < request.size(); i++){
        EXPECT_EQ(request.at(i), buf[i]);
    }
}

TEST(CanIsoTp, MultiFrameMessage){
    vector<byte> request {(byte)0x49,(byte) 0x02, (byte) 0x01,(byte) 0x57, (byte)0x4d, (byte)0x45,
                           (byte)0x21, (byte) 0x34 ,(byte)0x35,(byte) 0x33, (byte) 0x30,(byte) 0x34, (byte)0x34, (byte)0x32,
                           (byte)0x22, (byte) 0x59 ,(byte)0x30,(byte) 0x33, (byte) 0x33,(byte) 0x32, (byte)0x30, (byte)0x34
    };

    auto vehicleCAN = new CanIsoTP();
    auto testerCAN = new CanIsoTP();
    initIsoTp(vehicleCAN, testerCAN);
    testerCAN->send(request.data(), static_cast<int>(request.size()));
}