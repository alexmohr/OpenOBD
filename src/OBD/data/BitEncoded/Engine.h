#include <utility>

//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_ENGINE_H
#define OPEN_OBD2_ENGINE_H

#include <string>
#include "../OBDTest.h"

using namespace std;

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

protected:
    Engine(string systemLabel1, string systemLabel2, string systemLabel3,
             string systemLabel4, string systemLabel5, string systemLabel6,
             string systemLabel7, string systemLabel8)
     {
        engineSystem1 = new OBDTest(std::move(systemLabel1), C,(byte)7, D,(byte)7);
        engineSystem2 = new OBDTest(std::move(systemLabel2), C,(byte)6, D,(byte)6);
        engineSystem3 = new OBDTest(std::move(systemLabel3), C,(byte)5, D,(byte)5);
        engineSystem4 = new OBDTest(std::move(systemLabel4), C,(byte)4, D,(byte)4);
        engineSystem5 = new OBDTest(std::move(systemLabel5), C,(byte)3, D,(byte)3);
        engineSystem6 = new OBDTest(std::move(systemLabel6), C,(byte)2, D,(byte)2);
        engineSystem7 = new OBDTest(std::move(systemLabel7), C,(byte)1, D,(byte)1);
        engineSystem8 = new OBDTest(std::move(systemLabel8), C,(byte)0, D,(byte)0);
    }

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

public:
    byte *toFrame();

    void fromFrame(byte *frame);
};

class Petrol: public Engine{
public:
Petrol() : Engine("EGR System", "Oxygen Sensor Heater", "Oxygen Sensor",
                "A/C Refrigerant", "Secondary Air System", "Evaporative System",
                "Heated Catalyst", "Catalyst") {}
};

class Diesel: public Engine{
public:
    Diesel(): Engine("EGR and/or VVT System", "PM filter monitoring", "Exhaust Gas Sensor",
            "- Reserved -", "Boost Pressure", "- Reserved -",
            "NOx/SCR Monitor", "NMHC Catalyst[a]") {}
};

#endif //OPEN_OBD2_ENGINE_H










