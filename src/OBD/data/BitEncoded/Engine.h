#include <utility>

//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_ENGINE_H
#define OPEN_OBD2_ENGINE_H

#include <string>
#include "../OBDTest.h"

using namespace std;


enum EngineType {
    PETROL = 0,
    DIESEL = 1,
};

class Engine {
private:
    OBDTest* engineSystem1;
    OBDTest* engineSystem2;
    OBDTest* engineSystem3;
    OBDTest* engineSystem4;
    OBDTest* engineSystem5;
    OBDTest* engineSystem6;
    OBDTest* engineSystem7;
    OBDTest* engineSystem8;

    EngineType type;
public:
    Engine();
    ~Engine(){
        delete engineSystem1;
        delete engineSystem2;
        delete engineSystem3;
        delete engineSystem4;
        delete engineSystem5;
        delete engineSystem6;
        delete engineSystem7;
        delete engineSystem8;
    }

    byte *toFrame();
    void fromFrame(byte *frame);

    void setEngineType(EngineType type);

    EngineType getEngineType();
};

#endif //OPEN_OBD2_ENGINE_H










