//
// Created by me on 14/12/18.
//

#ifndef OPEN_OBD2_ISOTP_H
#define OPEN_OBD2_ISOTP_H


#define NO_CAN_ID 0xFFFFFFFFU
#define BUFSIZE 5000 /* size > 4095 to check socket API internal checks */

#define MAX_CAN_ID_NORMAL 0x800
#define MAX_CAN_ID_EXTENDED 0x20000000

#include <cstddef>

using namespace std;

enum TP_ERRORS{
    InvalidIds = 1,
    FailedToOpenSocket =2
};

class CanIsoTP {
private:
    int socketHandle;
public:

    int openIsoTp(unsigned int rxId, unsigned int txId, char* ifname);
    void closeIsoTp();

    int send(byte* buf, int buflen);
    void receive(byte* buffer, int buffSize, int& readSize);
};


#endif //OPEN_OBD2_ISOTP_H
