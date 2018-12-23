//
// Created by me on 14/12/18.
//

#include "OBDHandlerTest.h"

INITIALIZE_EASYLOGGINGPP // NOLINT(cert-err58-cpp)

OBDHandler *getHandler() {
    Config config = Config();

    auto pcMap = map<Service, PidCollection>();
    config.parseJson("../configuration/pidConfig.json", pcMap);

    auto dtcMap = map<int, DataTroubleCode>();
    config.parseJson("../configuration/dtcConfig.json", dtcMap);

    auto *vehicle = new Vehicle(make_unique<map<int, DataTroubleCode>>(dtcMap));

    auto handler = new OBDHandler(vehicle, make_unique<map<Service, PidCollection>>(pcMap));
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
    handler->updateFromFrame(response.data(), static_cast<int>(response.size()));
    byte *val = handler->createAnswerFrame(request.data());

    compareResponse(response, val);

    return handler;
}


