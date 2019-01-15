//
// Created by me on 14/01/19.
//

#include <gtest/gtest.h>
#include "../../../src/CAN/ELM327WifiServer.h"
#include "../MockCommInterface.h"

const int port = 35000;


TEST(ELM327WifiServer, TestDataTelegram) {
    auto mockInterface = new MockCommInterface();
    auto elm = ELM327WifiServer(port, mockInterface);

    byte data[5];
    data[0] = (byte) '0';
    data[1] = (byte) '1';
    data[2] = (byte) '0';
    data[3] = (byte) 'a';
    data[4] = (byte) '\r';
    int rawSize = 5;
    int dataSize = rawSize;

    elm.parseData(data, dataSize);

    EXPECT_EQ(dataSize, 2);
    EXPECT_EQ(data[0], (byte) 0x01);
    EXPECT_EQ(data[1], (byte) 0x0A);

    data[0] = (byte) '0';
    data[1] = (byte) '1';
    data[2] = (byte) '0';
    data[3] = (byte) 'A';
    data[4] = (byte) '\r';
    dataSize = rawSize;
    elm.parseData(data, dataSize);

    EXPECT_EQ(dataSize, 2);
    EXPECT_EQ(data[0], (byte) 0x01);
    EXPECT_EQ(data[1], (byte) 0x0A);

    data[0] = (byte) '0';
    data[1] = (byte) '1';
    data[2] = (byte) '0';
    data[3] = (byte) '1';
    data[4] = (byte) '\r';
    dataSize = rawSize;
    elm.parseData(data, dataSize);

    EXPECT_EQ(dataSize, 2);
    EXPECT_EQ(data[0], (byte) 0x01);
    EXPECT_EQ(data[1], (byte) 0x01);

}