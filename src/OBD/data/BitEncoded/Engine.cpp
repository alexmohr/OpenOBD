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
    
}

byte *Engine::toFrame() {
    return nullptr;
}

void Engine::setEngineType(EngineType type) {
    this->type = type;
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
    return type;
}

