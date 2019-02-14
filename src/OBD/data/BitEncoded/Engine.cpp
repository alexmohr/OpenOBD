//
// Created by me on 13/12/18.
//

#include "Engine.h"


Engine::Engine() {
    engineSystem1 = make_unique<OBDTest>(DataObjectDescriptionText::getEngineSystem(1), C, 7, D, 7);
    engineSystem2 = make_unique<OBDTest>(DataObjectDescriptionText::getEngineSystem(2), C, 6, D, 6);
    engineSystem3 = make_unique<OBDTest>(DataObjectDescriptionText::getEngineSystem(3), C, 5, D, 5);
    engineSystem4 = make_unique<OBDTest>(DataObjectDescriptionText::getEngineSystem(4), C, 4, D, 4);
    engineSystem5 = make_unique<OBDTest>(DataObjectDescriptionText::getEngineSystem(5), C, 3, D, 3);
    engineSystem6 = make_unique<OBDTest>(DataObjectDescriptionText::getEngineSystem(6), C, 2, D, 2);
    engineSystem7 = make_unique<OBDTest>(DataObjectDescriptionText::getEngineSystem(7), C, 1, D, 1);
    engineSystem8 = make_unique<OBDTest>(DataObjectDescriptionText::getEngineSystem(8), C, 0, D, 0);
    type = make_unique<DataObject<EngineType>>(B, 3, B, 3, unit_bool, EngineType::PETROL, EngineType::DIESEL,
                                               DataObjectDescriptionText::getEngineType());
    setEngineType(PETROL);


    calculatedLoad = CalculatedDataObjectFactory::percent(DataObjectDescriptionText::getCalculatedLoad());
    coolantTemperature = CalculatedDataObjectFactory::celsius_AMinus40(
            DataObjectDescriptionText::getCoolantTemperature());

    // Fuel banks
    shortTermFuelTrimBank1 = CalculatedDataObjectFactory::percent_Percent128Minus100(
            A, DataObjectDescriptionText::getShortTermFuelTrimBank(1));
    shortTermFuelTrimBank2 = CalculatedDataObjectFactory::percent_Percent128Minus100(
            A, DataObjectDescriptionText::getShortTermFuelTrimBank(2));
    longTermFuelTrimBank1 = CalculatedDataObjectFactory::percent_Percent128Minus100(
            A, DataObjectDescriptionText::getLongTermFuelTrimBank(1));
    longTermFuelTrimBank2 = CalculatedDataObjectFactory::percent_Percent128Minus100(
            A, DataObjectDescriptionText::getLongTermFuelTrimBank(2));


    fuelPressure = CalculatedDataObjectFactory::kPa_3A(DataObjectDescriptionText::getFuelPressure());

    intakeManifoldAbsolutePressure = make_unique<DataObject<byte>>(A, 7, A, 0,
                                                                   unit_kPa, (byte) 0, (byte) 255,
                                                                   DataObjectDescriptionText::getIntakeManifoldAbsolutePressure());

    engineRPM = CalculatedDataObjectFactory::rpm_divided4(DataObjectDescriptionText::getEngineRPM());
    timingAdvance = CalculatedDataObjectFactory::degree_Divided2Minus64(DataObjectDescriptionText::getTimingAdvance());
    intakeAirTemperature = CalculatedDataObjectFactory::celsius_AMinus40(
            DataObjectDescriptionText::getIntakeAirTemperature());
    mafAirFlowRate = CalculatedDataObjectFactory::gramSec_Divided100(DataObjectDescriptionText::getMafAirFlowRate());
}

void Engine::fromFrameForMonitoringSystem(byte *frame, int size) {
    engineSystem1->fromFrame(frame, size);
    engineSystem2->fromFrame(frame, size);
    engineSystem3->fromFrame(frame, size);
    engineSystem4->fromFrame(frame, size);
    engineSystem5->fromFrame(frame, size);
    engineSystem6->fromFrame(frame, size);
    engineSystem7->fromFrame(frame, size);
    engineSystem8->fromFrame(frame, size);
    type->fromFrame(frame, size);
}

void Engine::setEngineType(EngineType type) {
    this->type->setValue(type);
    if (PETROL == type) {
        engineSystem1->setName("EGR System");
        engineSystem2->setName("Oxygen Sensor Heater");
        engineSystem3->setName("Oxygen Sensor");
        engineSystem4->setName("A/C Refrigerant");
        engineSystem5->setName("Secondary Air System");
        engineSystem6->setName("Evaporative System");
        engineSystem7->setName("Heated Catalyst");
        engineSystem8->setName("Catalyst");
    } else {
        engineSystem1->setName("EGR and/or VVT System");
        engineSystem2->setName("PM filter monitoring");
        engineSystem3->setName("Exhaust Gas Sensor");
        engineSystem4->setName("- Reserved -");
        engineSystem5->setName("Boost Pressure");
        engineSystem6->setName("- Reserved -");
        engineSystem7->setName("NOx/SCR Monitor");
        engineSystem8->setName("NMHC Catalyst[a]");
    }

}

DataObject<EngineType> &Engine::getEngineType() {
    return *type;
}

OBDTest &Engine::getEngineSystem1() {
    return *engineSystem1;
}

OBDTest &Engine::getEngineSystem2() {
    return *engineSystem2;
}

OBDTest &Engine::getEngineSystem3() {
    return *engineSystem3;
}

OBDTest &Engine::getEngineSystem4() {
    return *engineSystem4;
}

OBDTest &Engine::getEngineSystem5() {
    return *engineSystem5;
}

OBDTest &Engine::getEngineSystem6() {
    return *engineSystem6;
}

OBDTest &Engine::getEngineSystem7() {
    return *engineSystem7;
}

OBDTest &Engine::getEngineSystem8() {
    return *engineSystem8;
}

// todo refactor this into a seperate class
unsigned int Engine::toFrameForMonitoringSystem(unsigned int &data, int &size) {
    data = engineSystem1->toFrame(data, size) |
           engineSystem2->toFrame(data, size) |
           engineSystem3->toFrame(data, size) |
           engineSystem4->toFrame(data, size) |
           engineSystem5->toFrame(data, size) |
           engineSystem6->toFrame(data, size) |
           engineSystem7->toFrame(data, size) |
           engineSystem8->toFrame(data, size) |
           type->toFrame(data, size);
    return data;
}

CalculatedDataObject<byte, float> &Engine::getLoad() {
    return *calculatedLoad;
}

CalculatedDataObject<byte, short> &Engine::getCoolantTemperature() {
    return *coolantTemperature;
}

CalculatedDataObject<byte, float> &Engine::getShortTermFuelTrimBank1() {
    return *shortTermFuelTrimBank1;
}

CalculatedDataObject<byte, float> &Engine::getLongTermFuelTrimBank1() {
    return *longTermFuelTrimBank1;
}

CalculatedDataObject<byte, float> &Engine::getShortTermFuelTrimBank2() {
    return *shortTermFuelTrimBank2;
}

CalculatedDataObject<byte, float> &Engine::getLongTermFuelTrimBank2() {
    return *longTermFuelTrimBank2;
}

CalculatedDataObject<byte, unsigned short> &Engine::getFuelPressure() {
    return *fuelPressure;
}

DataObject<byte> &Engine::getIntakeManifoldAbsolutePressure() {
    return *intakeManifoldAbsolutePressure;
}

CalculatedDataObject<unsigned short, float> &Engine::getEngineRPM() {
    return *engineRPM;
}

CalculatedDataObject<byte, float> &Engine::getTimingAdvance() {
    return *timingAdvance;
}

CalculatedDataObject<byte, short> &Engine::getIntakeAirTemperature() {
    return *intakeAirTemperature;
}

CalculatedDataObject<unsigned short, float> &Engine::getMAFAirFlowRate() {
    return *mafAirFlowRate;
}





