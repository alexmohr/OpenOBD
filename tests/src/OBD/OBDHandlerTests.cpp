//
// Created by me on 14/12/18.
//


#include "../../../src/Config.h"
#include "../../../src/OBD/OBDHandler.h"
#include "gtest/gtest.h"
#include "../../../src/CAN/CanIsoTP.h"

INITIALIZE_EASYLOGGINGPP


#define CAN_INTERFACE "vcan0"

OBDHandler* getHandler(){

    Config p = Config();

    auto pcMap = map<Service, PidCollection>();
    p.parseJson("../configuration/pidConfig.json", pcMap);

    Engine *engine = new Diesel();
    auto *vehicle = new Vehicle(engine);
    auto handler = new OBDHandler(vehicle, new map<Service, PidCollection>((pcMap)));
    return handler;
}

TEST(OBDHandler, PIDSupported01_20){

    vector<byte> request  {(byte)0x01, (byte)0x00};
    vector<byte> response {(byte)0x41,(byte) 0x00, (byte)0xbe, (byte)0x7e, (byte)0xb8, (byte)0x13};

    OBDHandler *handler = getHandler();
    handler->updateFromFrame(response.data(), response.size());
    byte *val = handler->createAnswerFrame(request.data());
    int i;
    for (i = 0; i< 8;i++){
        EXPECT_EQ(val[i], response[i]);
    }
}

TEST(OBDHandler, PIDSupported01_20_With_Simulated_CAN){

    // these data has uds structure removed because it is added by the kernel driver.
    vector<byte> request  {(byte)0x01, (byte)0x00};
    vector<byte> response {(byte)0x41,(byte) 0x00, (byte)0xbe, (byte)0x7e, (byte)0xb8, (byte)0x13};

    auto vehicleCAN = new CanIsoTP();
    auto testerCAN = new CanIsoTP();

    vehicleCAN->openIsoTp(TESTER_ID, VEHICLE_ID, const_cast<char *>(CAN_INTERFACE));
    testerCAN->openIsoTp(VEHICLE_ID, TESTER_ID, const_cast<char *>(CAN_INTERFACE));


    OBDHandler *handler = getHandler();
    byte* buf;
    int readSize;

    // setup vehicle
    buf = (byte*)malloc(response.size());
    vehicleCAN->send(response.data(), static_cast<int>(response.size()));
    testerCAN->receive(buf, static_cast<int>(response.size()), readSize);
    handler->updateFromFrame(buf, readSize);

    buf = (byte*)malloc(request.size());
    testerCAN->send(request.data(), static_cast<int>(request.size()));
    vehicleCAN->receive(buf, static_cast<int>(request.size()), readSize);

    byte *val = handler->createAnswerFrame(buf);
    int i;
    string log;
    for (i = 0; i< 8;i++){
        EXPECT_EQ(val[i], response[i]);
    }
}

