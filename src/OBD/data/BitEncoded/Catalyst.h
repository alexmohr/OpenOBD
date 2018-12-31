//
// Created by me on 31/12/18.
//

#ifndef OPEN_OBD2_CATALYST_H
#define OPEN_OBD2_CATALYST_H

#include "../dataObject/CalculatedDataObject.h"

class Catalyst {
private:
    unique_ptr<CalculatedDataObject<unsigned short, float>> temperatureBank1Sensor1;
    unique_ptr<CalculatedDataObject<unsigned short, float>> temperatureBank2Sensor1;
    unique_ptr<CalculatedDataObject<unsigned short, float>> temperatureBank1Sensor2;
    unique_ptr<CalculatedDataObject<unsigned short, float>> temperatureBank2Sensor2;
public:
    Catalyst();

    CalculatedDataObject<unsigned short, float> &getTemperatureBank1Sensor1();
    CalculatedDataObject<unsigned short, float> &getTemperatureBank2Sensor1();
    CalculatedDataObject<unsigned short, float> &getTemperatureBank1Sensor2();
    CalculatedDataObject<unsigned short, float> &getTemperatureBank2Sensor2();
};


#endif //OPEN_OBD2_CATALYST_H
