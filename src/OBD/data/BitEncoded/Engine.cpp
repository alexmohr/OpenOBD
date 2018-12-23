//
// Created by me on 13/12/18.
//

#include "Engine.h"


Engine::Engine() {
    engineSystem1 = make_unique<OBDTest>("", C, 7, D, 7);
    engineSystem2 = make_unique<OBDTest>("", C, 6, D, 6);
    engineSystem3 = make_unique<OBDTest>("", C, 5, D, 5);
    engineSystem4 = make_unique<OBDTest>("", C, 4, D, 4);
    engineSystem5 = make_unique<OBDTest>("", C, 3, D, 3);
    engineSystem6 = make_unique<OBDTest>("", C, 2, D, 2);
    engineSystem7 = make_unique<OBDTest>("", C, 1, D, 1);
    engineSystem8 = make_unique<OBDTest>("", C, 0, D, 0);
    type = make_unique<DataObject<EngineType>>(B, 3);
    setEngineType(PETROL);


    calculatedLoad = make_unique<CalculatedDataObject<byte, float>>(A, 7, A, 0,
                                                                    CalculatedValues::toPercent,
                                                                    CalculatedValues::fromPercent);
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

EngineType Engine::getEngineType() {
    return type->getValue();
}

OBDTest& Engine::getEngineSystem1() {
    return *engineSystem1;
}

OBDTest& Engine::getEngineSystem2() {
    return *engineSystem2;
}

OBDTest& Engine::getEngineSystem3() {
    return *engineSystem3;
}

OBDTest& Engine::getEngineSystem4() {
    return *engineSystem4;
}

OBDTest& Engine::getEngineSystem5() {
    return *engineSystem5;
}

OBDTest& Engine::getEngineSystem6() {
    return *engineSystem6;
}

OBDTest& Engine::getEngineSystem7() {
    return *engineSystem7;
}

OBDTest& Engine::getEngineSystem8() {
    return *engineSystem8;
}

unsigned int Engine::toFrameForMonitoringSystem(unsigned int &data) {
    data = engineSystem1->toFrame(data) |
           engineSystem2->toFrame(data) |
           engineSystem3->toFrame(data) |
           engineSystem4->toFrame(data) |
           engineSystem5->toFrame(data) |
           engineSystem6->toFrame(data) |
           engineSystem7->toFrame(data) |
           engineSystem8->toFrame(data) |
           type->toFrame(data);
    return data;
}

CalculatedDataObject<byte, float> &Engine::getLoad() {
    return *calculatedLoad;
}

