//
// Created by me on 05/01/19.
//



#include <easylogging++.h>
#include "gtest/gtest.h"
#include "../src/Config.h"

INITIALIZE_EASYLOGGINGPP // NOLINT(cert-err58-cpp)

int main(int argc, char **argv) {
    Config::configureLogging(true, false);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}