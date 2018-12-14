//
// Created by me on 14/12/18.
//


#include "../src/Config.h"
#include "../src/OBD/OBDHandler.h"
#include "gtest/gtest.h"

INITIALIZE_EASYLOGGINGPP



TEST(OBDHandler, updateFromFrame){

    Config p = Config();

    auto pcMap = map<Service, PidCollection>();
    p.parseJson("../configuration/pidConfig.json", pcMap);

    vector<byte> request  {(byte)0x02, (byte)0x01, (byte)0x00, (byte)0x00, (byte)0x00, (byte)0x00, (byte)0x00, (byte)0x00};
    vector<byte> response {(byte)0x06, (byte)0x41,(byte) 0x00, (byte)0xbe, (byte)0x7e, (byte)0xb8, (byte)0x13, (byte)0x00};

    Engine *engine = new Diesel();
    auto *vehicle = new Vehicle(engine);
    auto handler = OBDHandler(vehicle, &(pcMap));
    handler.updateFromFrame(response.data());

    byte *val = handler.createAnswerFrame(request.data());
    int i;
    string log;
    for (i = 0; i< 8;i++){
        log += to_string((int)val[i]) + " ";
    }
    LOG(INFO) << log;
    log = "";
    for (i = 0; i< 8;i++){
        log += to_string((int)response[i]) + " ";
    }
    LOG(INFO) << log;

    //LOG(INFO) << response[0] ;
    EXPECT_EQ(0, 1);

    EXPECT_EQ(val, response.data());
    //assert(val == response.data());
    //assert(val == response.data());
}
