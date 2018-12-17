//
// Created by me on 13/12/18.
//

#include "Engine.h"


Engine::Engine() {
    engineSystem1 = new OBDTest("", C, (byte) 7, D, (byte) 7);
    engineSystem2 = new OBDTest("", C, (byte) 6, D, (byte) 6);
    engineSystem3 = new OBDTest("", C, (byte) 5, D, (byte) 5);
    engineSystem4 = new OBDTest("", C, (byte) 4, D, (byte) 4);
    engineSystem5 = new OBDTest("", C, (byte) 3, D, (byte) 3);
    engineSystem6 = new OBDTest("", C, (byte) 2, D, (byte) 2);
    engineSystem7 = new OBDTest("", C, (byte) 1, D, (byte) 1);
    engineSystem8 = new OBDTest("", C, (byte) 0, D, (byte) 0);
    setEngineType(PETROL);
}

void Engine::fromFrame(byte *frame, int size) {
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

OBDTest *Engine::getEngineSystem1() {
    return engineSystem1;
}

OBDTest *Engine::getEngineSystem2() {
    return engineSystem2;
}

OBDTest *Engine::getEngineSystem3() {
    return engineSystem3;
}

OBDTest *Engine::getEngineSystem4() {
    return engineSystem4;
}

OBDTest *Engine::getEngineSystem5() {
    return engineSystem5;
}

OBDTest *Engine::getEngineSystem6() {
    return engineSystem6;
}

OBDTest *Engine::getEngineSystem7() {
    return engineSystem7;
}

OBDTest *Engine::getEngineSystem8() {
    return engineSystem8;
}

unsigned int Engine::toFrame(unsigned int &data) {
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
