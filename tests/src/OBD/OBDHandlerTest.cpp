//
// Created by me on 14/12/18.
//

#include "OBDHandlerTest.h"


OBDHandler *getHandler() {
    Config config = Config();

    auto pcMap = map<Service, PidCollection>();
    config.parseJson("../configuration/pidConfig.json", pcMap);

    auto dtcMap = map<int, DataTroubleCode>();
    config.parseJson("../configuration/dtcConfig.json", dtcMap);

    auto handler = new OBDHandler(make_unique<map<Service, PidCollection>>(pcMap), dtcMap);
    return handler;
}

void compareResponse(byte *expectedResponse, byte *actualResponse, int size) {
    int i;
    for (i = 0; i < size; i++) {
        EXPECT_EQ(actualResponse[i], expectedResponse[i]);
    }
}


void compareResponse(vector<byte> expectedResponse, byte *actualResponse) {
    compareResponse(expectedResponse.data(), actualResponse, static_cast<int>(expectedResponse.size()));
}


OBDHandler* doTest(vector<byte> request, vector<byte> response) {
    OBDHandler *handler = getHandler();

    // enable support for the requested pid.
    handler->getVehicle()->getPidSupport().setPidSupported((Service) request[0], (int) request[1], true);
    handler->updateFromFrame(response.data(), static_cast<int>(response.size()));

    int dataSize = static_cast<int>(request.size());
    byte *val = handler->createAnswerFrame(request.data(), dataSize);

    EXPECT_EQ(dataSize, response.size());

    compareResponse(response, val);

    return handler;
}


