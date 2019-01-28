#include <utility>

//
// Created by me on 14/01/19.
//

#include "MockCommInterface.h"


MockCommInterface::MockCommInterface() {
    dataForNextRecv = new byte[255];
    dataFromLastSend = new byte[255];
    dataForNextRecvSize = 0;
    dataForNextRecvSize = 0;
}

MockCommInterface::~MockCommInterface() {
    delete[] dataForNextRecv;
    delete[] dataFromLastSend;
}

int MockCommInterface::send(byte *buf, int bufSize) {
    if (supportEverything && bufSize >= 2) {
        if (buf[1] == (byte) SupportedPid01_20) {
            setDataForNextReceiveCall(responseSupportedPid01_20, 6);
        } else if (buf[1] == (byte) SupportedPid21_40) {
            setDataForNextReceiveCall(responseSupportedPid21_40, 6);
        } else if (buf[1] == (byte) SupportedPid41_60) {
            setDataForNextReceiveCall(responseSupportedPid41_60, 6);
        } else if (buf[1] == (byte) SupportedPid61_80) {
            setDataForNextReceiveCall(responseSupportedPid61_80, 6);
        } else if (buf[1] == (byte) SupportedPid81_A0) {
            setDataForNextReceiveCall(responseSupportedPid81_A0, 6);
        } else if (buf[1] == (byte) SupportedPidA1_C0) {
            setDataForNextReceiveCall(responseSupportedPidA1_C0, 6);
        } else if (buf[1] == (byte) SupportedPidC1_E0) {
            setDataForNextReceiveCall(responseSupportedPidC1_E0, 6);
        }
    }

    if (recvCallbackSet) {
        recvCallback(buf, bufSize, dataForNextRecv, dataForNextRecvSize);
    }

    memcpy(dataFromLastSend, buf, bufSize);
    return bufSize;
}

int MockCommInterface::closeInterface() {
    return 0;
}

int MockCommInterface::openInterface() {
    return 0;
}


void MockCommInterface::receive(byte *buf, int bufSize, int &readSize) {
    if (dataForNextRecvSize > bufSize) {
        LOG(ERROR) << "BUFFER TOO SMALL";
        return;
    }

    memcpy(buf, dataForNextRecv, dataForNextRecvSize);
    readSize = dataForNextRecvSize;
}

void MockCommInterface::setDataForNextReceiveCall(byte *data, int size) {
    memcpy(this->dataForNextRecv, data, size);
    this->dataForNextRecvSize = size;
}

void MockCommInterface::getDataFromLastSend(byte *buf, int bufSize, int &recvSize) {
    if (dataFromLastSendSize > bufSize) {
        recvSize = -1;
        return;
    }

    memcpy(buf, dataFromLastSend, dataFromLastSendSize);
    recvSize = dataFromLastSendSize;
}

void MockCommInterface::setDataReceivedCallback(
        function<void(byte *inBuf, int inBufSize, byte *outBuf, int &outBufSize)> callBack, bool enable) {
    recvCallbackSet = enable;
    if (enable) {
        recvCallback = std::move(callBack);
    }


}

