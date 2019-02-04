//
// Created by me on 14/12/18.
//

#ifndef OPEN_OBD2_SERVICE_H
#define OPEN_OBD2_SERVICE_H


enum Service {
    POWERTRAIN = 0x01,


    FREEZE_FRAME = 0x02,
    // These services must be implemented
    /* CONFIRMED_DTCS = 0x03,
     CLEAR_DTCS = 0x04,
     OXYGEN_SENSOR = 0x05,
     VEHICLE_INFORMATION = 0x09,*/

    // These are defined by the standard but no documentation has been found.
    // EMISSION_RELATED_PERMANENT_DTC = 0x0a
    // ONBOARD_MONITORING_TESTS = 0x06,
    // EMISSION_RELATED_DTC = 0x07,
    // ENABLE_OFF_BOARD_DIAGNOSIS = 0x08,

};


#endif //OPEN_OBD2_SERVICE_H
