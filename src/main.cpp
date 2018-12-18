#include <iostream>
#include <map>
#include <string>
#include "easylogging++.h"
#include "Config.h"
#include "CAN/CanIsoTP.h"

#include "OBD/OBDHandler.h"

INITIALIZE_EASYLOGGINGPP


int main() {
    Config p = Config();

    auto pcMap = map<Service, PidCollection>();
    p.parseJson("../configuration/pidConfig.json", pcMap);

    auto dtcMap = map<int, DataTroubleCode>();
    p.parseJson("../configuration/dtcConfig.json", pcMap);

/*
    <msg id="2024" pl="" t="00:00:16.665"/>
    <msg id="2024" pl="" t="00:00:16.668"/>
    <msg id="2024" pl="" t="00:00:16.678"/>
 */
    vector<byte> request  {(byte) 0x09 , (byte)0x02};
    vector<byte> response {(byte)0x10, (byte) 0x14 ,(byte)0x49,(byte) 0x02, (byte) 0x01,(byte) 0x57, (byte)0x4d, (byte)0x45,
            (byte)0x21, (byte) 0x34 ,(byte)0x35,(byte) 0x33, (byte) 0x30,(byte) 0x34, (byte)0x34, (byte)0x32,
            (byte)0x22, (byte) 0x59 ,(byte)0x30,(byte) 0x33, (byte) 0x33,(byte) 0x32, (byte)0x30, (byte)0x34
    };

    auto *vehicleCAN = new CanIsoTP();
    vehicleCAN->openIsoTp(TESTER_ID, VEHICLE_ID, const_cast<char *>("vcan0"));

    auto *testerCAN = new CanIsoTP();
    testerCAN->openIsoTp(VEHICLE_ID, TESTER_ID, const_cast<char *>("vcan0"));

    testerCAN->send(request.data(), static_cast<int>(request.size()));




    return 0;
}
