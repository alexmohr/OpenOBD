//
// Created by me on 31/12/18.
//

#include "Catalyst.h"

Catalyst::Catalyst() {
    temperatureBank1Sensor1 = make_unique<CalculatedDataObject<unsigned short, float>>(
            A, 7, B, 0,
            CalculatedValues::to256APlusBDivided10Minus40, CalculatedValues::from256APlusBDivided10Minus40,
            unit_celsius, -40, 6513.5);

    temperatureBank2Sensor1 = make_unique<CalculatedDataObject<unsigned short, float>>(
            A, 7, B, 0,
            CalculatedValues::to256APlusBDivided10Minus40, CalculatedValues::from256APlusBDivided10Minus40,
            unit_celsius, -40, 6513.5);

    temperatureBank1Sensor2 = make_unique<CalculatedDataObject<unsigned short, float>>(
            A, 7, B, 0,
            CalculatedValues::to256APlusBDivided10Minus40, CalculatedValues::from256APlusBDivided10Minus40,
            unit_celsius, -40, 6513.5);

    temperatureBank2Sensor2 = make_unique<CalculatedDataObject<unsigned short, float>>(
            A, 7, B, 0,
            CalculatedValues::to256APlusBDivided10Minus40, CalculatedValues::from256APlusBDivided10Minus40,
            unit_celsius, -40, 6513.5);

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