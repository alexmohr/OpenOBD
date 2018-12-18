//
// Created by me on 18/12/18.
//

#ifndef OPEN_OBD2_DATATROUBLECODE_H
#define OPEN_OBD2_DATATROUBLECODE_H

#include <string>
#include "../CAN/CanIsoTP.h"

using namespace std;


class DataTroubleCode {

    // Constants
private:
    const char PREFIX_POWERTRAIN = 'P';
    const char PREFIX_CHASIS = 'C';
    const char PREFIX_BODY = 'B';
    const char PREFIX_NETWORK = 'U';

    const int CAN_OFFSET_POWERTRAIN = 0x00;
    const int CAN_OFFSET_CHASIS = 0x04;
    const int CAN_OFFSET_BODY = 0x08;
    const int CAN_OFFSET_NETWORK = 0x0c;

private:
    unsigned int canId;

    unsigned int convertSaeIdToCan(string saeId);

    unsigned int convertHexToInt(string hex);

    string convertIntToHex(unsigned int n);


// fields set from configuration
private:
    string saeId;
    string description;


public:
    DataTroubleCode();

    unsigned int getCanId();

    void setSaeId(string saeId);

    void setDescription(string description);

    string getSaeId();

    string getDescription();

};


/*

 */

#endif //OPEN_OBD2_DATATROUBLECODE_H
