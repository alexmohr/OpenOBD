//
// Created by me on 14/12/18.
//

#include <vector>
#include <string>
#include "../../../src/Config.h"
#include "gtest/gtest.h"
#include "easylogging++.h"

using namespace std;

TEST(DataTroubleCode, SaeConversionTest) {
    // example for every id type.
    // mixed string case is on purpose to make sure case is ignored
    vector<string> saeIds{
            // Power train
            "p0CAFE", "P1BABE", "P2BEEF", "p3deAD",
            // Chasis
            "c0CAFE", "C1BABE", "C2BEEF", "c3DeAD",
            // Body
            "b0CAFE", "B1BABE", "B2BEEF", "b3DeAD",
            // Network
            "u0CAFE", "U1BABE", "U2BEEF", "u3DeAD",

            // some real codes.
            "P0013", "C1751", "B1408", "U1191"
    };

    vector<unsigned int> canIds{
            // Power train
            0x0CAFE, 0x1BABE, 0x2BEEF, 0x3deAD,
            // Chasis
            0x4CAFE, 0x5BABE, 0x6BEEF, 0x7DeAD,
            // Body
            0x8CAFE, 0x9BABE, 0xABEEF, 0xBDeAD,
            // Network
            0xCCAFE, 0xDBABE, 0xEBEEF, 0xFDeAD,

            // some real codes.
            0x0013, 0x5751, 0x9408, 0xD191
    };

    assert(canIds.size() == saeIds.size());
    DataTroubleCode code = DataTroubleCode();

    unsigned long i;
    for (i = 0; i < canIds.size(); i++) {
        code.setSaeId(saeIds.at(i));
        unsigned int canId = code.getCanId();
        EXPECT_EQ(canId, canIds.at(i));
    }
}

TEST(DataTroubleCode, SaeConversionTestInvalidIds) {
    DataTroubleCode code = DataTroubleCode();
    vector<string> invalidIds{
            "", "a", "p0", "-1", "42"
    };

    for (auto const &id: invalidIds) {
        code.setSaeId(id);
        EXPECT_GT(code.getCanId(), MAX_CAN_ID_EXTENDED);
    }
}