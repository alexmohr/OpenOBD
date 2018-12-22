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
    unique_ptr<OBDTest> engineSystem1;
    unique_ptr<OBDTest> engineSystem2;
    unique_ptr<OBDTest> engineSystem3;
    unique_ptr<OBDTest> engineSystem4;
    unique_ptr<OBDTest> engineSystem5;
    unique_ptr<OBDTest> engineSystem6;
    unique_ptr<OBDTest> engineSystem7;
    unique_ptr<OBDTest> engineSystem8;

    DataObject<EngineType> *type = new DataObject<EngineType>(B, 3);

public:
    Engine();

    ~Engine() = default;

    unsigned int toFrame(unsigned int &data);
    void fromFrame(byte *frame, int size);

    void setEngineType(EngineType type);

    EngineType getEngineType();

    OBDTest &getEngineSystem1();

    OBDTest &getEngineSystem2();

    OBDTest &getEngineSystem3();

    OBDTest &getEngineSystem4();

    OBDTest &getEngineSystem5();

    OBDTest &getEngineSystem6();

    OBDTest &getEngineSystem7();

    OBDTest &getEngineSystem8();

};

#endif //OPEN_OBD2_ENGINE_H










