//
// Created by me on 31/12/18.
//

#include "Catalyst.h"

Catalyst::Catalyst() {
    temperatureBank1Sensor1 = CalculatedDataObjectFactory::celsius_Divided10Minus40(
            DataObjectDescriptionText::getCatalystTemperatureSensor(1, 1));
    temperatureBank2Sensor1 = CalculatedDataObjectFactory::celsius_Divided10Minus40(
            DataObjectDescriptionText::getCatalystTemperatureSensor(2, 1));
    temperatureBank1Sensor2 = CalculatedDataObjectFactory::celsius_Divided10Minus40(
            DataObjectDescriptionText::getCatalystTemperatureSensor(1, 2));
    temperatureBank2Sensor2 = CalculatedDataObjectFactory::celsius_Divided10Minus40(
            DataObjectDescriptionText::getCatalystTemperatureSensor(2, 2));
}

CalculatedDataObject<unsigned short, float> &Catalyst::getTemperatureBank1Sensor1() {
    return *temperatureBank1Sensor1;
}

CalculatedDataObject<unsigned short, float> &Catalyst::getTemperatureBank2Sensor1() {
    return *temperatureBank2Sensor1;
}

CalculatedDataObject<unsigned short, float> &Catalyst::getTemperatureBank1Sensor2() {
    return *temperatureBank1Sensor2;
}

CalculatedDataObject<unsigned short, float> &Catalyst::getTemperatureBank2Sensor2() {
    return *temperatureBank2Sensor2;
}