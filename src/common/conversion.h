//
// Created by me on 21/12/18.
//


#ifndef OPEN_OBD2_CONVERSION_H
#define OPEN_OBD2_CONVERSION_H

#include <cstddef>
#include <string>
#include <type_traits>


using namespace std;

unsigned short byteArrayToUShort(byte *data);

byte *ushortToByteArray(unsigned short data);

byte *uintToByteArray(unsigned int data);

int getTwoComplement(unsigned short val);

string to_string(byte val);

unsigned int getBytes(int bits);


#endif //OPEN_OBD2_CONVERSION_H
