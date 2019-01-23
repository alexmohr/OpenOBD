//
// Created by me on 14/01/19.
//

#ifndef OPEN_OBD2_MOCKCOMMINTERFACE_H
#define OPEN_OBD2_MOCKCOMMINTERFACE_H

#include <cstddef>
#include <cstdlib>
#include "../../src/communication/ICommunicationInterface.h"
#include "../../src/OBD/Pid.h"

using namespace std;

class MockCommInterface : public ICommunicationInterface {
    byte *dataForNextRecv;
    int dataForNextRecvSize;

    byte *dataFromLastSend;
    int dataFromLastSendSize;

    function<void(byte *inBuf, int inBufSize, byte *outBuf, int &outBufSize)> recvCallback;
    bool recvCallbackSet = false;
public:

    MockCommInterface();

    ~MockCommInterface() override;

    bool supportEverything = false;

    byte responseSupportedPid01_20[6] =
            {(byte) 0x41, (byte) SupportedPid01_20, (byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0xff};
    byte responseSupportedPid21_40[6] =
            {(byte) 0x41, (byte) SupportedPid21_40, (byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0xff};
    byte responseSupportedPid41_60[6] =
            {(byte) 0x41, (byte) SupportedPid41_60, (byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0xff};
    byte responseSupportedPid61_80[6] =
            {(byte) 0x41, (byte) SupportedPid61_80, (byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0xff};
    byte responseSupportedPid81_A0[6] =
            {(byte) 0x41, (byte) SupportedPid81_A0, (byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0xff};
    byte responseSupportedPidA1_C0[6] =
            {(byte) 0x41, (byte) SupportedPidA1_C0, (byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0xff};
    byte responseSupportedPidC1_E0[6] =
            {(byte) 0x41, (byte) SupportedPidC1_E0, (byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0xff};

    int send(byte *buf, int bufSize) override;

    int closeInterface() override;


    int openInterface() override;

    void receive(byte *buf, int bufSize, int &readSize) override;

    void setDataForNextReceiveCall(byte *data, int size);

    void getDataFromLastSend(byte *buf, int bufSize, int &recvSize);

    int configureInterface() override { return 0; };

    void setDataReceivedCallback(
            function<void(byte *inBuf, int inBufSize, byte *outBuf, int &outBufSize)> callBack, bool enable);

};


#endif //OPEN_OBD2_MOCKCOMMINTERFACE_H
