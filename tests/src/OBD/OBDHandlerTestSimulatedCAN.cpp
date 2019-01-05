#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by me on 14/12/18.
//

#include "../../../src/Config.h"
#include "OBDHandlerTest.h"
#include "gtest/gtest.h"


TEST(OBDHandler, PIDSupported01_20_With_VirtualCAN) {
    // these data has uds structure removed because it is added by the kernel driver.
    vector<byte> request{(byte) 0x01, (byte) 0x00};
    vector<byte> response{(byte) 0x41, (byte) 0x00, (byte) 0xbe, (byte) 0x7e, (byte) 0xb8, (byte) 0x13};

    auto vehicleCAN = new CanIsoTP(TESTER_ID, VEHICLE_ID, const_cast<char *>(CAN_INTERFACE));
    auto testerCAN = new CanIsoTP(VEHICLE_ID, TESTER_ID, const_cast<char *>(CAN_INTERFACE));

    vehicleCAN->openInterface();
    testerCAN->openInterface();


    OBDHandler *handler = getHandler();
    byte *buf;
    int readSize;

    // setup vehicle
    buf = (byte *) malloc(response.size());
    vehicleCAN->send(response.data(), static_cast<int>(response.size()));
    testerCAN->receive(buf, static_cast<int>(response.size()), readSize);

    assert(readSize > 0);

    handler->updateFromFrame(buf, readSize);

    buf = (byte *) malloc(request.size());
    testerCAN->send(request.data(), static_cast<int>(request.size()));
    vehicleCAN->receive(buf, static_cast<int>(request.size()), readSize);

    int dataSize = 0;
    byte *val = handler->createAnswerFrame(buf, dataSize);
    EXPECT_EQ(dataSize, response.size());
    compareResponse(response, val);
}

TEST(OBDHandler, AmbientTemperature_46_With_VirtualCAN) {
    // these data has uds structure removed because it is added by the kernel driver.
    vector<byte> request{(byte) 0x01, (byte) AmbientAirTemperature};
    vector<byte> response{(byte) 0x41, (byte) (AmbientAirTemperature), (byte) 0xff};

    auto vehicleCAN = new CanIsoTP(TESTER_ID, VEHICLE_ID, const_cast<char *>(CAN_INTERFACE));
    auto testerCAN = new CanIsoTP(VEHICLE_ID, TESTER_ID, const_cast<char *>(CAN_INTERFACE));

    vehicleCAN->openInterface();
    testerCAN->openInterface();


    OBDHandler *handler = getHandler();
    byte *buf;
    int readSize;

    // setup vehicle
    buf = (byte *) malloc(response.size());
    vehicleCAN->send(response.data(), static_cast<int>(response.size()));
    testerCAN->receive(buf, static_cast<int>(response.size()), readSize);

    assert(readSize > 0);

    handler->updateFromFrame(buf, readSize);

    buf = (byte *) malloc(request.size());
    testerCAN->send(request.data(), static_cast<int>(request.size()));
    vehicleCAN->receive(buf, static_cast<int>(request.size()), readSize);

    int dataSize = 0;
    byte *val = handler->createAnswerFrame(buf, dataSize);
    vehicleCAN->send(val, dataSize);
    EXPECT_EQ(dataSize, response.size());
    compareResponse(response, val);
}



#pragma clang diagnostic pop