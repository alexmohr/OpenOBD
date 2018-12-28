//
// Created by me on 21/12/18.
//
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

