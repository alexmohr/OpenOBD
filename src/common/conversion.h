//
// Created by me on 21/12/18.
//


#ifndef OPEN_OBD2_CONVERSION_H
#define OPEN_OBD2_CONVERSION_H

#include <cstddef>
#include <string>
#include <type_traits>
#include <vector>

using namespace std;

unsigned short byteArrayToUShort(byte *data);

byte *ushortToByteArray(unsigned short data);

byte *uintToByteArray(unsigned int data);

int getTwoComplement(unsigned short val);

string to_string(byte val);

unsigned int getBytes(int bits);

vector<string> splitString(char *input);

string convertIntToHex(int n);

unsigned int convertHexToInt(string hex);


template<typename T>
T convertStringToT(const string &value) {
    if (std::is_same<T, double>::value ||
        std::is_same<T, float>::value) {
        return ((T) strtod(value.c_str(), nullptr));
    } else if (std::is_same<T, short>::value ||
               std::is_same<T, int>::value ||
               std::is_same<T, long>::value) {
        return ((T) strtol(value.c_str(), nullptr, 0));
    } else {
        return ((T) strtoul(value.c_str(), nullptr, 0));
    }
}

#endif //OPEN_OBD2_CONVERSION_H
