#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by me on 16/12/18.
//

#include "gtest/gtest.h"
#include <vector>
#include "../../../../src/OBD/data/DataObject.h"
#include "../../../../src/common/conversion.h"

using namespace std;

void byteTest(DataObject<byte> *obj, vector<byte> data) {
    EXPECT_EQ(1, obj->fromFrame(data.data(), data.size()));
    EXPECT_EQ((byte) 0x42, obj->getValue());
}

void testBool(DataObject<bool> *obj, vector<byte> data, bool expected) {
    EXPECT_EQ(1, obj->fromFrame(data.data(), data.size()));
    EXPECT_EQ(expected, obj->getValue());
}

void compareResponseBytes(byte *expectedResponse, byte *actualResponse, int size) {
    int i;
    for (i = 0; i < size; i++) {
        EXPECT_EQ(actualResponse[i], expectedResponse[i]);
    }
}

void compareResponse(vector<byte> expectedResponse, unsigned int data) {
    byte *retVal = toByteArray(data);
    compareResponseBytes(expectedResponse.data(), retVal, expectedResponse.size());
}

void compareResponseInt(vector<byte> expectedResponse, DataObject<unsigned int> *actualResponse) {
    unsigned int data = 0;
    data = actualResponse->toFrame(data);
    compareResponse(expectedResponse, data);
}


void compareResponse(vector<byte> expectedResponse, DataObject<unsigned short> *actualResponse) {
    unsigned int data = 0;
    data = actualResponse->toFrame(data);
    compareResponse(expectedResponse, data);
}



TEST(DataObjectTest, DecodeBoolA0) {
    auto *obj = new DataObject<bool>(A, (byte) 0);
    vector<byte> data{(byte) 0x01, (byte) 0xff, (byte) 0xff, (byte) 0x00};
    testBool(obj, data, true);
}


TEST(DataObjectTest, DecodeBoolA0_Negative) {
    auto *obj = new DataObject<bool>(A, (byte) 0);
    vector<byte> data{(byte) 0xfe, (byte) 0x00, (byte) 0x00, (byte) 0x00};
    testBool(obj, data, false);
}

TEST(DataObjectTest, DecodeBoolA4) {
    auto *obj = new DataObject<bool>(A, (byte) 4);
    vector<byte> data{(byte) 0x10, (byte) 0x00, (byte) 0x00, (byte) 0x00};
    testBool(obj, data, true);
}


TEST(DataObjectTest, DecodeBoolA7) {
    auto *obj = new DataObject<bool>(A, (byte) 7);
    vector<byte> data{(byte) 0x80, (byte) 0x00, (byte) 0x00, (byte) 0x00};
    testBool(obj, data, true);
}


TEST(DataObjectTest, DecodeBoolC2) {
    auto *obj = new DataObject<bool>(C, (byte) 2);
    vector<byte> data{(byte) 0x00, (byte) 0x00, (byte) 0x04, (byte) 0x00};
    testBool(obj, data, true);
}

TEST(DataObjectTest, DecodeBoolC3) {
    auto *obj = new DataObject<bool>(C, (byte) 4);
    vector<byte> data{(byte) 0x00, (byte) 0x00, (byte) 0x10, (byte) 0x00};
    testBool(obj, data, true);
}

TEST(DataObjectTest, DecodeBoolC6) {
    auto *obj = new DataObject<bool>(C, (byte) 6);
    // all 1 but 7 and 5
    vector<byte> data{(byte) 0x00, (byte) 0x00, (byte) 0x5f, (byte) 0x00};
    testBool(obj, data, true);
}

TEST(DataObjectTest, DecodeBoolD7) {
    auto *obj = new DataObject<bool>(D, (byte) 7);
    vector<byte> data{(byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x80};
    testBool(obj, data, true);
}

TEST(DataObjectTest, DecodeBoolD7Negative) {
    auto *obj = new DataObject<bool>(D, (byte) 7);
    vector<byte> data{(byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x7f};
    testBool(obj, data, false);
}

TEST(DataObjectTest, DecodeBoolD2_Negative) {
    auto *obj = new DataObject<bool>(D, (byte) 2);
    // every bit expect D2 is true
    vector<byte> data{(byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0xFB};
    testBool(obj, data, false);
}


TEST(DataObjectTest, DecodeBoolC7) {
    auto *obj = new DataObject<bool>(C, (byte) 7, C, (byte) 7);
    vector<byte> data{(byte) 0x01, (byte) 0xff, (byte) 0xff, (byte) 0xff};
    testBool(obj, data, true);
}


TEST(DataObjectTest, TestDecodeByteA) {
    auto *obj = new DataObject<byte>(A, (byte) 7, A, (byte) 0);
    vector<byte> data{(byte) 0x42, (byte) 0xff, (byte) 0xff, (byte) 0xff};
    byteTest(obj, data);
}

TEST(DataObjectTest, TestDecodeByteB) {
    auto *obj = new DataObject<byte>(B, (byte) 7, B, (byte) 0);
    vector<byte> data{(byte) 0xff, (byte) 0x42, (byte) 0xff, (byte) 0xff};
    byteTest(obj, data);
}


TEST(DataObjectTest, TestDecodeByteC) {
    auto *obj = new DataObject<byte>(C, (byte) 7, C, (byte) 0);
    vector<byte> data{(byte) 0xff, (byte) 0xff, (byte) 0x42, (byte) 0xff};
    byteTest(obj, data);
}


TEST(DataObjectTest, TestDecodeByteD) {
    auto *obj = new DataObject<byte>(D, (byte) 7, D, (byte) 0);
    vector<byte> data{(byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0x42};
    byteTest(obj, data);
}

TEST(DataObjectTest, TestDecodeShortLeft) {
    auto *obj = new DataObject<unsigned short>(A, (byte) 7, B, (byte) 0);
    vector<byte> data{(byte) 0xca, (byte) 0xfe};
    obj->fromFrame(data.data(), data.size());
    EXPECT_EQ(0xcafe, obj->getValue());
    compareResponse(data, obj);
}


TEST(DataObjectTest, TestDecodeShortMiddle) {
    auto *obj = new DataObject<unsigned short>(B, (byte) 7, C, (byte) 0);
    vector<byte> data{(byte) 0x00, (byte) 0xca, (byte) 0xfe, (byte) 0x00};
    EXPECT_EQ(1, obj->fromFrame(data.data(), data.size()));
    EXPECT_EQ(0xcafe, obj->getValue());
    compareResponse(data, obj);
}


TEST(DataObjectTest, TestDecodeShortRight) {
    auto *obj = new DataObject<unsigned short>(C, (byte) 7, D, (byte) 0);
    vector<byte> data{(byte) 0x00, (byte) 0x00, (byte) 0xca, (byte) 0xfe};
    EXPECT_EQ(1, obj->fromFrame(data.data(), data.size()));
    EXPECT_EQ(0xcafe, obj->getValue());
    compareResponse(data, obj);
}

TEST(DataObjectTest, TestDecodeShortOdd) {
    auto *obj = new DataObject<unsigned short>(A, (byte) 6, A, (byte) 0);
    vector<byte> data{(byte) 0xf1, (byte) 0x00, (byte) 0x00, (byte) 0x00};
    EXPECT_EQ(1, obj->fromFrame(data.data(), data.size()));
    EXPECT_EQ(0x71, obj->getValue());

    vector<byte> response{(byte) 0x71, (byte) 0x00, (byte) 0x00, (byte) 0x00};
    compareResponse(response, obj);
}

TEST(DataObjectTest, TestDecodeShortOverlap) {
    auto *obj = new DataObject<unsigned short>(A, (byte) 1, B, (byte) 6);
    vector<byte> data{(byte) 0x3c, (byte) 0x00, (byte) 0x00, (byte) 0x00};
    obj->fromFrame(data.data(), data.size());
    EXPECT_EQ(0x0f, obj->getValue());
    vector<byte> response{(byte) 0x03, (byte) 0xc0};
    compareResponse(response, obj);
}



TEST(DataObjectTest, TestDecode2BitAsShortBorder) {
    // A7	A6	A5	A4	A3	A2	A1	A0	B7
    // 00  01  02  03  04  05  06  07  08
    auto *obj = new DataObject<unsigned short>(A, (byte) 0, B, (byte) 7);

    // data in binary
    // 0000 0001 1000 0000
    vector<byte> data{(byte) 0x01, (byte) 0x80};
    obj->fromFrame(data.data(), data.size());
    EXPECT_EQ(0x03, obj->getValue());
    compareResponse(data, obj);
}


TEST(DataObjectTest, TestDecode2BitAsShortMiddle) {
    // A7	A6	A5	A4	A3	A2	A1	A0	B7
    // 00  01  02  03  04  05  06  07  08
    auto *obj = new DataObject<unsigned short>(A, (byte) 5, A, (byte) 4);

    // data in binary
    // 7654 3210
    // 0011 0000
    vector<byte> data{(byte) 0x30};
    obj->fromFrame(data.data(), data.size());
    EXPECT_EQ(0x03, obj->getValue());
    compareResponse(data, obj);
}


TEST(DataObjectTest, TestDecode2BitAsShortMiddle2) {
    // A7	A6	A5	A4	A3	A2	A1	A0	B7
    // 00  01  02  03  04  05  06  07  08
    auto *obj = new DataObject<unsigned short>(A, (byte) 3, A, (byte) 2);

    // data in binary
    // 7654 3210
    // 0011 0000
    vector<byte> data{(byte) 0xC};
    obj->fromFrame(data.data(), data.size());
    EXPECT_EQ(0x03, obj->getValue());
    compareResponse(data, obj);
}


TEST(DataObjectTest, TestDecode3BitAsShortMiddle2) {
    // A7	A6	A5	A4	A3	A2	A1	A0	B7
    // 00  01  02  03  04  05  06  07  08
    auto *obj = new DataObject<unsigned short>(A, (byte) 4, A, (byte) 2);

    // data in binary
    // 7654 3210
    // 0011 0000
    vector<byte> data{(byte) 0x1C};
    obj->fromFrame(data.data(), data.size());
    EXPECT_EQ(0x07, obj->getValue());
    compareResponse(data, obj);
}

TEST(DataObjectTest, TestDecode2BitMSB) {
    // A7	A6	A5	A4	A3	A2	A1	A0	B7
    // 00  01  02  03  04  05  06  07  08
    auto *obj = new DataObject<unsigned short>(A, (byte) 7, A, (byte) 6);

    vector<byte> data{(byte) 0xC0};
    obj->fromFrame(data.data(), data.size());
    EXPECT_EQ(0x03, obj->getValue());
    compareResponse(data, obj);
}



TEST(DataObjectTest, TestDecodeInt) {
    auto *obj = new DataObject<unsigned int>(A, (byte) 7, D, (byte) 0);
    vector<byte> data{(byte) 0xca, (byte) 0xfe, (byte) 0xba, (byte) 0xbe,};
    EXPECT_EQ(1, obj->fromFrame(data.data(), data.size()));
    EXPECT_EQ(0xcafebabe, obj->getValue());
    compareResponseInt(data, obj);
}

#pragma clang diagnostic pop