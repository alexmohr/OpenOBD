//
// Created by me on 14/01/19.
//

#include "MockCommInterface.h"

int MockCommInterface::send(byte *buf, int buflen) {
    if (supportEverything && buflen >= 2) {

        if (buf[1] == (byte) SupportedPid01_20) {
            setNextReceive(responseSupportedPid01_20, 6);
        } else if (buf[1] == (byte) SupportedPid21_40) {
            setNextReceive(responseSupportedPid21_40, 6);
        } else if (buf[1] == (byte) SupportedPid41_60) {
            setNextReceive(responseSupportedPid41_60, 6);
        } else if (buf[1] == (byte) SupportedPid61_80) {
            setNextReceive(responseSupportedPid61_80, 6);
        } else if (buf[1] == (byte) SupportedPid81_A0) {
            setNextReceive(responseSupportedPid81_A0, 6);
        } else if (buf[1] == (byte) SupportedPidA1_C0) {
            setNextReceive(responseSupportedPidA1_C0, 6);
        } else if (buf[1] == (byte) SupportedPidC1_E0) {
            setNextReceive(responseSupportedPidC1_E0, 6);
        }

    }

    return buflen;
}

int MockCommInterface::closeInterface() {
    return 0;
}

int MockCommInterface::openInterface() {
    return 0;
};


void MockCommInterface::receive(byte *buffer, int buffSize, int &readSize) {
    memcpy(buffer, data, size);
    readSize = size;
}

void MockCommInterface::setNextReceive(byte *data, int size) {
    memcpy(this->data, data, size);
    this->size = size;
}
