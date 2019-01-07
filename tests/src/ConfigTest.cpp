
//
// Created by me on 18/12/18.
//

#include <gtest/gtest.h>
#include <vector>
#include "../../src/Config.h"

using namespace std;


TEST(Config, ParseDtcConfig) {
    Config cfg = Config();
    auto dtcMap = map<int, DataTroubleCode>();
    cfg.parseJson("../configuration/dtcConfig.json", dtcMap);

    // check size
    EXPECT_EQ(3607, dtcMap.size());

    // check a random element
    auto dtc = DataTroubleCode();
    dtc.setSaeId("U2500");

    auto d = dtcMap.at(dtc.getCanId());
    EXPECT_EQ(dtc.getSaeId(), d.getSaeId());
}