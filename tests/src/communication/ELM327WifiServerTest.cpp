//
// Created by me on 14/01/19.
//

#include <gtest/gtest.h>
#include "../../../src/communication/ELM327WifiServer.h"
#include "../MockCommInterface.h"

const int port = 35000;


TEST(ELM327WifiServer, TestConfigurationTelegram) {
//    auto mockInterface = new MockCommInterface();
//    auto elm = ELM327WifiServer(port, mockInterface);
//    elm.openInterface();
//    while (!elm.isOpen()) {
//        usleep(1000);
//    }
//
//    string data = getElmConfigString(ELM_CONFIG_SPACES, true);
//    mockInterface->send((byte *) data.c_str(), static_cast<int>(data.size()));
//
//    int bufSize = 255;
//    byte *buf = new byte[255];
//    int recvSize;
//    mockInterface->receive(buf, bufSize, recvSize);
//
//    LOG(ERROR) << "FOO";

//    ELM_CONFIG_SPACES
//    ELM_CONFIG_HEADER
//    ELM_CONFIG_ECHO
//    ELM_CONFIG_PROTOCOL
//    ELM_HEADER_SAE
//
//    byte buf[5];
//    buf[0] = (byte) 'A';
//    buf[1] = (byte) 'T';
//    buf[2] = (byte) 'S';
//    buf[3] = (byte) '0';
//    buf[4] = (byte) '\r';
//    int rawSize = 5;
//    int dataSize = rawSize;
//
//    elm.sendResponse(buf, 5, dataSize, fakeSockFd);
//
//    EXPECT_EQ(dataSize, 3);
//    EXPECT_EQ(buf[0], (byte) 'O');
//    EXPECT_EQ(buf[1], (byte) 'K');
//    EXPECT_EQ(buf[2], (byte) '\r');
}

TEST(ELM327WifiServer, TestDataTelegram) {
//    auto mockInterface = new MockCommInterface();
//    auto elm = ELM327WifiServer(port, mockInterface);
//
//    byte data[5];
//    data[0] = (byte) '0';
//    data[1] = (byte) '1';
//    data[2] = (byte) '0';
//    data[3] = (byte) 'a';
//    data[4] = (byte) '\r';
//    int rawSize = 5;
//    int dataSize = rawSize;
//
//    elm.sendResponse(data, rawSize, dataSize, fakeSockFd);
//
//    EXPECT_EQ(dataSize, 2);
//    EXPECT_EQ(data[0], (byte) 0x01);
//    EXPECT_EQ(data[1], (byte) 0x0A);
//
//    data[0] = (byte) '0';
//    data[1] = (byte) '1';
//    data[2] = (byte) '0';
//    data[3] = (byte) 'A';
//    data[4] = (byte) '\r';
//    dataSize = rawSize;
//    elm.sendResponse(data, rawSize, dataSize, fakeSockFd);
//
//    EXPECT_EQ(dataSize, 2);
//    EXPECT_EQ(data[0], (byte) 0x01);
//    EXPECT_EQ(data[1], (byte) 0x0A);
//
//    data[0] = (byte) '0';
//    data[1] = (byte) '1';
//    data[2] = (byte) '0';
//    data[3] = (byte) '1';
//    data[4] = (byte) '\r';
//    dataSize = rawSize;
//    elm.sendResponse(data, rawSize, dataSize, fakeSockFd);
//
//    EXPECT_EQ(dataSize, 2);
//    EXPECT_EQ(data[0], (byte) 0x01);
//    EXPECT_EQ(data[1], (byte) 0x01);

}