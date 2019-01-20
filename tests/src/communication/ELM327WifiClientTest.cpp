//
// Created by me on 20/01/19.
//



#include <gtest/gtest.h>
#include "../../../src/communication/ELM327WifiClient.h"
#include "../MockCommInterface.h"

const int port = 35000;
string selectedProtocol = "1";
char lastRequestedProtocol = '0';

string canHeader = "7E8";
string canHeader29Bit = "000007E8";
string saeHeader = "486B10";


void protocolRequest(string &result) {
    const string successCan = canHeader + "064100FFFFFFFF00";
    const string successCan29Bit = canHeader29Bit + "064100FFFFFFFF00";
    const string successSae = saeHeader + "4100FFFFFFFFXX";

    if (lastRequestedProtocol != selectedProtocol.c_str()[0]) {
        result = "ERROR";
        return;
    }

    int protocol = convertHexToInt(selectedProtocol);
    ElmProtocol &elmProtocol = ELM327WifiClient::availableProtocols.at(protocol);
    if (elmProtocol.canIdBitLength == 0) {
        result = successSae;
    } else {
        if (elmProtocol.canIdBitLength > 11) {
            result = successCan29Bit;
        } else {
            result = successCan;
        }
    }
}


function<void(byte *, int, byte *, int &)> cb =
        [](byte *inBuf, int inBufSize, byte *outBuf, int &outBufSize) {

            const string ok = "OK";
            // config command
            string result;
            if ((byte) 'A' == inBuf[0] && (byte) 'T' == inBuf[1]) {
                result = ok;
                if ((byte) 'S' == inBuf[2] && (byte) 'P' == inBuf[3]) {
                    lastRequestedProtocol = (char) inBuf[4];
                }
            } else if ((byte) '0' == inBuf[0]) {
                if ((byte) '1' == inBuf[1]) {
                    protocolRequest(result);
                }
            }
            result += "\r>";
            memcpy(outBuf, (byte *) result.c_str(), result.size());
            outBufSize = static_cast<int>(result.size());
        };

string createResponse(const string &data, int &dataLength) {
    string response;
    dataLength = static_cast<int>(data.size() / 2);
    if (selectedProtocol.c_str()[0] < '6') {
        string suffix = "XX";
        response = saeHeader + data + "XX";
    } else {
        string header;
        if (selectedProtocol.c_str()[0] == '7' || selectedProtocol.c_str()[0] == '9') {
            header = canHeader29Bit;
        } else {
            header = canHeader;
        }
        string prefix = header + "0" + to_string(dataLength);
        response = prefix + data;
    }
    string prompt = "\r>";
    response += prompt;
    return response;
}


void recvData(ELM327WifiClient &elm, int &readSize, byte *&buf) {
    int bufSize = 255;
    buf = (byte *) malloc(bufSize);
    elm.receive(buf, bufSize, readSize);
}

void testVehicleSpeed(MockCommInterface *mockInterface, ELM327WifiClient &elm) {
    byte request[2] = {(byte) 0x01, (byte) VehicleSpeed};
    mockInterface->setDataReceivedCallback(nullptr, false);

    int expectedSize;
    string response = createResponse("410D7F", expectedSize);

    mockInterface->setDataForNextReceiveCall((byte *) response.c_str(), static_cast<int>(response.size()));
    EXPECT_EQ(elm.send(request, 2), 5);

    int readSize;
    byte *buf;
    recvData(elm, readSize, buf);

    EXPECT_EQ(readSize, expectedSize);
    EXPECT_EQ(buf[0], (byte) 0x41);
    EXPECT_EQ(buf[1], (byte) Service1Pids::VehicleSpeed);
    EXPECT_EQ(buf[2], (byte) 0x7F);
    delete buf;
}

void testSupportedPids(MockCommInterface *mockInterface, ELM327WifiClient &elm) {
    byte request[2] = {(byte) 0x01, (byte) VehicleSpeed};
    mockInterface->setDataReceivedCallback(nullptr, false);

    string responseData = "4100FFFFFFFF";
    int expectedSize;
    string response = createResponse(responseData, expectedSize);

    mockInterface->setDataForNextReceiveCall((byte *) response.c_str(), static_cast<int>(response.size()));
    EXPECT_EQ(elm.send(request, 2), 5);


    int readSize;
    byte *buf;
    recvData(elm, readSize, buf);

    EXPECT_EQ(readSize, expectedSize);
    EXPECT_EQ(buf[0], (byte) 0x41);
    EXPECT_EQ(buf[1], (byte) Service1Pids::SupportedPid01_20);
    int i;
    for (i = 2; i < 6; i++) {
        EXPECT_EQ(buf[i], (byte) 0xFF);
    }

    delete buf;
}

void testProtocol(char protocol) {
    selectedProtocol = protocol;
    auto mockInterface = new MockCommInterface();
    auto elm = ELM327WifiClient(mockInterface);
    int result = elm.openInterface();
    EXPECT_EQ(result, 0);


    mockInterface->setDataReceivedCallback(cb, true);
    result = elm.configureInterface();
    EXPECT_EQ(result, 0);

    testVehicleSpeed(mockInterface, elm);
    testSupportedPids(mockInterface, elm);

    EXPECT_EQ(0, elm.closeInterface());
    delete mockInterface;

}

TEST(ELM327WifiClient, TestConfigurationProtocol1) {
    testProtocol('1');
}

TEST(ELM327WifiClient, TestConfigurationProtocol2) {
    testProtocol('2');
}

TEST(ELM327WifiClient, TestConfigurationProtocol3) {
    testProtocol('3');
}

TEST(ELM327WifiClient, TestConfigurationProtocol4) {
    testProtocol('4');
}

TEST(ELM327WifiClient, TestConfigurationProtocol5) {
    testProtocol('5');
}

TEST(ELM327WifiClient, TestConfigurationProtocol6) {
    testProtocol('6');
}

TEST(ELM327WifiClient, TestConfigurationProtocol7) {
    testProtocol('7');
}

TEST(ELM327WifiClient, TestConfigurationProtocol8) {
    testProtocol('8');
}

TEST(ELM327WifiClient, TestConfigurationProtocol9) {
    testProtocol('9');
}

TEST(ELM327WifiClient, TestConfigurationProtocolA) {
    testProtocol('A');
}
