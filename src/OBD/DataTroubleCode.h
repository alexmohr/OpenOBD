//
// Created by me on 18/12/18.
//

#ifndef OPEN_OBD2_DATATROUBLECODE_H
#define OPEN_OBD2_DATATROUBLECODE_H

#include <string>
#include "../communication/CanIsoTP.h"
#include "data/dataObject/DataObject.h"

using namespace std;


class DataTroubleCode {

    // Constants
public:
    static const char DTC_PREFIX_POWERTRAIN = 'P';
    static const char DTC_PREFIX_CHASIS = 'C';
    static const char DTC_PREFIX_BODY = 'B';
    static const char DTC_PREFIX_NETWORK = 'U';

    static const int DTC_CAN_OFFSET_POWERTRAIN = 0x00;
    static const int DTC_CAN_OFFSET_CHASIS = 0x04;
    static const int DTC_CAN_OFFSET_BODY = 0x08;
    static const int DTC_CAN_OFFSET_NETWORK = 0x0c;

private:
    unsigned int canId;

    unsigned int convertSaeIdToCan(string saeId);

// fields set from configuration
private:
    string saeId;
    shared_ptr<DataObjectDescription> description;


public:
    DataTroubleCode();

    unsigned int getCanId();

    void setSaeId(string saeId);

    void addDescription(string descriptionText);

    string getSaeId();

    shared_ptr<DataObjectDescription> getDescription();

};


/*

 */

#endif //OPEN_OBD2_DATATROUBLECODE_H
