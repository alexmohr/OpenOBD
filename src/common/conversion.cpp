//
// Created by me on 21/12/18.
//
#include "conversion.h"

//byte *toByteArray(unsigned int data) {
//    byte *retVal = new byte[4];
//    retVal[0] = (byte) (data & 0xFF);
//    retVal[1] = (byte) ((data >> 8) & 0xFF);
//    retVal[2] = (byte) ((data >> 16) & 0xFF);
//    retVal[3] = (byte) ((data >> 24) & 0xFF);
//    return retVal;
//}

byte *toByteArray(unsigned int data) {
    byte *retVal = new byte[4];
    retVal[0] = (byte) ((data >> 24) & 0xFF);
    retVal[1] = (byte) ((data >> 16) & 0xFF);
    retVal[2] = (byte) ((data >> 8) & 0xFF);
    retVal[3] = (byte) (data & 0xFF);

    return retVal;
}


