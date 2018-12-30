//
// Created by me on 30/12/18.
//

#ifndef OPEN_OBD2_DATAOBJECTDESCRIPTIONS_H
#define OPEN_OBD2_DATAOBJECTDESCRIPTIONS_H

#include <string>

using namespace std;

// Todo these text should come from config some day
class DataObjectDescriptionText {
public:
    const static string MonitorStatusMIL;
    const static string MonitorStatusDTC;
public:
    const static string OBDTest;
    const static string OBDTestAvailable;
    const static string OBDTestIncomplete;
public:
    const static string BankOxygenSensorVoltage;
    const static string BankOxygenSensorShortFuelTrim;

};


#endif //OPEN_OBD2_DATAOBJECTDESCRIPTIONS_H
