//
// Created by me on 21/12/18.
//
#include <sstream>
#include <iterator>
#include <cstring>
#include "conversion.h"

unsigned short byteArrayToUShort(byte *data) {
    // casting individual elements is necessary otherwise we would get max 0xff
    auto retVal = ((unsigned short) data[1] << 8) | (unsigned short) data[0];
    return retVal;
}


byte *ushortToByteArray(unsigned short data) {
    byte *retVal = new byte[2];
    retVal[0] = (byte) ((data >> 8) & 0xFF);
    retVal[1] = (byte) (data & 0xFF);
    return retVal;
}

byte *uintToByteArray(unsigned int data) {
    byte *retVal = new byte[4];
    retVal[0] = (byte) ((data >> 24) & 0xFF);
    retVal[1] = (byte) ((data >> 16) & 0xFF);
    retVal[2] = (byte) ((data >> 8) & 0xFF);
    retVal[3] = (byte) (data & 0xFF);

    return retVal;
}

int getTwoComplement(unsigned short val) {
    /*
     * if first bit is 1, it is a negative number with all other bits in 2's complement
     * extract negative part by subtracting off the 0x8000
     * otherwise the lower bits are just the positive integer value
     */
    return (0x8000 & val ? (int) (0x7FFF & val) - 0x8000 : val);
}

string to_string(std::byte val){
    return to_string((unsigned short)val);
}


unsigned int getBytes(int bits) {
    if (bits <= 8) {
        return 1;
    } else if (bits <= 16) {
        return 2;
    } else if (bits <= 32) {
        return 4;
    }

    return 8;
}



vector<string> splitString(char *input) {
    std::istringstream iss(input);
    std::vector<std::string> cmd(std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>());
    return cmd;
}


string convertIntToHex(int n) {
    stringstream stream;
    stream << hex << n;
    string result = stream.str();
    return result;
}

unsigned int convertHexToInt(string hex) {
    unsigned int x;
    std::stringstream ss;
    ss << std::hex << hex;
    ss >> x;
    return x;
}

bool isNumber(byte b) {
    return isNumber((char) b);
}

bool isNumber(char c) {
    return c >= '0' && c <= '9';
}

bool messageContains(const byte *buf, int recvSize, string data) {
    if (recvSize < (int) data.size()) {
        return false;
    }

    int i;
    for (i = 0; i < (int) (recvSize - data.size()+1); i++) {
        if (0 == strncmp(data.c_str(), (char *) buf + i, data.size())) {
            return true;
        }
    }
    return false;
}

string convertCharToString(char c) {
    char* cc = new char[1]{c};
    string value = string(cc);
    delete[] cc;
    return value;
}


