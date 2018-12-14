//
// Created by me on 14/12/18.
//

#include "OBDHandlerTest.h"

INITIALIZE_EASYLOGGINGPP // NOLINT(cert-err58-cpp)


OBDHandler *getHandler() {

    Config p = Config();

    auto pcMap = map<Service, PidCollection>();
    p.parseJson("../configuration/pidConfig.json", pcMap);

    Engine *engine = new Diesel();
    auto *vehicle = new Vehicle(engine);
    auto handler = new OBDHandler(vehicle, new map<Service, PidCollection>((pcMap)));
    return handler;
}

void compareResponse(vector<byte> expectedResponse, byte *actualResponse) {
    int i;
    for (i = 0; i < expectedResponse.size(); i++) {
        EXPECT_EQ(actualResponse[i], expectedResponse[i]);
    }
}

void doTest(vector<byte> request, vector<byte> response) {
    OBDHandler *handler = getHandler();
    handler->updateFromFrame(response.data(), static_cast<int>(response.size()));
    byte *val = handler->createAnswerFrame(request.data());
    compareResponse(response, val);
}



