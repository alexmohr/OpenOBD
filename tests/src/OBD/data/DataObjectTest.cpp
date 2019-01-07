//
// Created by me on 16/12/18.
//

#include "gtest/gtest.h"
#include <vector>
#include "../../../../src/OBD/data/dataObject/DataObject.h"
#include "../../../../src/common/conversion.h"

using namespace std;

void byteTest(DataObject<byte> *obj, vector<byte> data) {
    obj->fromFrame(data.data(), data.size());
    EXPECT_EQ((byte) 0x42, obj->getValue());
}

void testBool(DataObject<bool> *obj, vector<byte> data, bool expected) {
    obj->fromFrame(data.data(), data.size());
    EXPECT_EQ(expected, obj->getValue());
}

void compareResponseBytes(byte *expectedResponse, byte *actualResponse, int actualSize, int expectedSize) {
    int i;
    // EXPECT_EQ(getBytes(actualSize), expectedSize);
    for (i = 0; i < expectedSize; i++) {
        EXPECT_EQ(actualResponse[i], expectedResponse[i]);
    }
}

void compareResponse(vector<byte> expectedResponse, unsigned int data, unsigned int size) {
    byte *retVal = uintToByteArray(data);
    compareResponseBytes(expectedResponse.data(), retVal, size, expectedResponse.size());
}

void compareResponseInt(vector<byte> expectedResponse, DataObject<unsigned int> *actualResponse) {
    unsigned int data = 0;
    int size = 0;
    data = actualResponse->toFrame(data, size);
    compareResponse(expectedResponse, data, size);
}


void compareResponse(vector<byte> expectedResponse, DataObject<unsigned short> *actualResponse) {
    unsigned int data = 0;
    int size = 0;
    data = actualResponse->toFrame(data, size);
    compareResponse(expectedResponse, data, size);
}



TEST(DataObjectTest, DecodeBoolA0) {
    auto *obj = new DataObject<bool>(A, 0);
    vector<byte> data{(byte) 0x01, (byte) 0xff, (byte) 0xff, (byte) 0x00};
    testBool(obj, data, true);
}


TEST(DataObjectTest, DecodeBoolA0_Negative) {
    auto *obj = new DataObject<bool>(A, 0);
    vector<byte> data{(byte) 0xfe, (byte) 0x00, (byte) 0x00, (byte) 0x00};
    testBool(obj, data, false);
}

TEST(DataObjectTest, DecodeBoolA4) {
    auto *obj = new DataObject<bool>(A, 4);
    vector<byte> data{(byte) 0x10, (byte) 0x00, (byte) 0x00, (byte) 0x00};
    testBool(obj, data, true);
}


TEST(DataObjectTest, DecodeBoolA7) {
    auto *obj = new DataObject<bool>(A, 7);
    vector<byte> data{(byte) 0x80, (byte) 0x00, (byte) 0x00, (byte) 0x00};
    testBool(obj, data, true);
}


TEST(DataObjectTest, DecodeBoolC2) {
    auto *obj = new DataObject<bool>(C, 2);
    vector<byte> data{(byte) 0x00, (byte) 0x00, (byte) 0x04, (byte) 0x00};
    testBool(obj, data, true);
}

TEST(DataObjectTest, DecodeBoolC3) {
    auto *obj = new DataObject<bool>(C, 4);
    vector<byte> data{(byte) 0x00, (byte) 0x00, (byte) 0x10, (byte) 0x00};
    testBool(obj, data, true);
}

TEST(DataObjectTest, DecodeBoolC6) {
    auto *obj = new DataObject<bool>(C, 6);
    // all 1 but 7 and 5
    vector<byte> data{(byte) 0x00, (byte) 0x00, (byte) 0x5f, (byte) 0x00};
    testBool(obj, data, true);
}

TEST(DataObjectTest, DecodeBoolD7) {
    auto *obj = new DataObject<bool>(D, 7);
    vector<byte> data{(byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x80};
    testBool(obj, data, true);
}

TEST(DataObjectTest, DecodeBoolD7Negative) {
    auto *obj = new DataObject<bool>(D, 7);
    vector<byte> data{(byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x7f};
    testBool(obj, data, false);
}

TEST(DataObjectTest, DecodeBoolD2_Negative) {
    auto *obj = new DataObject<bool>(D, 2);
    // every bit expect D2 is true
    vector<byte> data{(byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0xFB};
    testBool(obj, data, false);
}


TEST(DataObjectTest, DecodeBoolC7) {
    auto *obj = new DataObject<bool>(C, 7, C, 7);
    vector<byte> data{(byte) 0x01, (byte) 0xff, (byte) 0xff, (byte) 0xff};
    testBool(obj, data, true);
}


TEST(DataObjectTest, TestDecodeByteA) {
    auto *obj = new DataObject<byte>(A, 7, A, 0);
    vector<byte> data{(byte) 0x42, (byte) 0xff, (byte) 0xff, (byte) 0xff};
    byteTest(obj, data);
}

TEST(DataObjectTest, TestDecodeByteB) {
    auto *obj = new DataObject<byte>(B, 7, B, 0);
    vector<byte> data{(byte) 0xff, (byte) 0x42, (byte) 0xff, (byte) 0xff};
    byteTest(obj, data);
}


TEST(DataObjectTest, TestDecodeByteC) {
    auto *obj = new DataObject<byte>(C, 7, C, 0);
    vector<byte> data{(byte) 0xff, (byte) 0xff, (byte) 0x42, (byte) 0xff};
    byteTest(obj, data);
}


TEST(DataObjectTest, TestDecodeByteD) {
    auto *obj = new DataObject<byte>(D, 7, D, 0);
    vector<byte> data{(byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0x42};
    byteTest(obj, data);
}

TEST(DataObjectTest, TestDecodeShortLeft) {
    auto *obj = new DataObject<unsigned short>(A, 7, B, 0);
    vector<byte> data{(byte) 0xca, (byte) 0xfe};
    obj->fromFrame(data.data(), data.size());
    EXPECT_EQ(0xcafe, obj->getValue());
    compareResponse(data, obj);
}


TEST(DataObjectTest, TestDecodeShortMiddle) {
    auto *obj = new DataObject<unsigned short>(B, 7, C, 0);
    vector<byte> data{(byte) 0x00, (byte) 0xca, (byte) 0xfe};
    obj->fromFrame(data.data(), data.size());
    EXPECT_EQ(0xcafe, obj->getValue());
    compareResponse(data, obj);
}


TEST(DataObjectTest, TestDecodeShortRight) {
    auto *obj = new DataObject<unsigned short>(C, 7, D, 0);
    vector<byte> data{(byte) 0x00, (byte) 0x00, (byte) 0xca, (byte) 0xfe};
    obj->fromFrame(data.data(), data.size());
    EXPECT_EQ(0xcafe, obj->getValue());
    compareResponse(data, obj);
}

TEST(DataObjectTest, TestDecodeShortOdd) {
    auto *obj = new DataObject<unsigned short>(A, 6, A, 0);
    vector<byte> data{(byte) 0xf1, (byte) 0x00, (byte) 0x00, (byte) 0x00};
    obj->fromFrame(data.data(), data.size());
    EXPECT_EQ(0x71, obj->getValue());

    vector<byte> response{(byte) 0x71, (byte) 0x00, (byte) 0x00, (byte) 0x00};
    compareResponse(response, obj);
}

TEST(DataObjectTest, TestDecodeShortOverlap) {
    auto *obj = new DataObject<unsigned short>(A, 1, B, 6);
    vector<byte> data{(byte) 0x3c, (byte) 0x00, (byte) 0x00, (byte) 0x00};
    obj->fromFrame(data.data(), data.size());
    EXPECT_EQ(0x0f, obj->getValue());
    vector<byte> response{(byte) 0x03, (byte) 0xc0};
    compareResponse(response, obj);
}



TEST(DataObjectTest, TestDecode2BitAsShortBorder) {
    // A7	A6	A5	A4	A3	A2	A1	A0	B7
    // 00  01  02  03  04  05  06  07  08
    auto *obj = new DataObject<unsigned short>(A, 0, B, 7);

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
    auto *obj = new DataObject<unsigned short>(A, 5, A, 4);

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
    auto *obj = new DataObject<unsigned short>(A, 3, A, 2);

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
    auto *obj = new DataObject<unsigned short>(A, 4, A, 2);

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
    auto *obj = new DataObject<unsigned short>(A, 7, A, 6);

    vector<byte> data{(byte) 0xC0};
    obj->fromFrame(data.data(), data.size());
    EXPECT_EQ(0x03, obj->getValue());
    compareResponse(data, obj);
}



TEST(DataObjectTest, TestDecodeInt) {
    auto *obj = new DataObject<unsigned int>(A, 7, D, 0);
    vector<byte> data{(byte) 0xca, (byte) 0xfe, (byte) 0xba, (byte) 0xbe,};
    obj->fromFrame(data.data(), data.size());
    EXPECT_EQ(0xcafebabe, obj->getValue());
    compareResponseInt(data, obj);
}