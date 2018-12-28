//
// Created by me on 21/12/18.
//


#ifndef OPEN_OBD2_CONVERSION_H
#define OPEN_OBD2_CONVERSION_H

#include <cstddef>

using namespace std;

unsigned short byteArrayToUShort(byte *data);

byte *ushortToByteArray(unsigned short data);

byte *uintToByteArray(unsigned int data);

#endif //OPEN_OBD2_CONVERSION_H
