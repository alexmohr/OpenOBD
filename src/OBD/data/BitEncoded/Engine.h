#include <utility>

//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_ENGINE_H
#define OPEN_OBD2_ENGINE_H

#include <string>
#include "../OBDTest.h"

using namespace std;

enum EngineType{
    Petrol = 0,
    Diesel = 1
};
class Engine {
private:
    OBDTest* eningeSystem1;
    OBDTest* eningeSystem2;
    OBDTest* eningeSystem3;
    OBDTest* eningeSystem4;
    OBDTest* eningeSystem5;
    OBDTest* eningeSystem6;
    OBDTest* eningeSystem7;
    OBDTest* eningeSystem8;

protected:
    Engine(string systemLabel1, string systemLabel2, string systemLabel3,
             string systemLabel4, string systemLabel5, string systemLabel6,
             string systemLabel7, string systemLabel8)
     {
        eningeSystem1 = new OBDTest(std::move(systemLabel1), C,7, D,7);
        eningeSystem2 = new OBDTest(std::move(systemLabel2), C,6, D,6);
        eningeSystem3 = new OBDTest(std::move(systemLabel3), C,5, D,5);
        eningeSystem4 = new OBDTest(std::move(systemLabel4), C,4, D,4);
        eningeSystem5 = new OBDTest(std::move(systemLabel5), C,3, D,3);
        eningeSystem6 = new OBDTest(std::move(systemLabel6), C,2, D,2);
        eningeSystem7 = new OBDTest(std::move(systemLabel7), C,1, D,1);
        eningeSystem8 = new OBDTest(std::move(systemLabel8), C,0, D,0);
    }

    ~Engine(){
        delete eningeSystem1;
        delete eningeSystem2;
        delete eningeSystem3;
        delete eningeSystem4;
        delete eningeSystem5;
        delete eningeSystem6;
        delete eningeSystem7;
        delete eningeSystem8;
    }

public:
    BYTE *toFrame();
};

class Petrol: Engine{
public:
Petrol() : Engine("EGR System", "Oxygen Sensor Heater", "Oxygen Sensor",
                "A/C Refrigerant", "Secondary Air System", "Evaporative System",
                "Heated Catalyst", "Catalyst") {}
};

class Diesel: Engine{
public:
    Diesel(): Engine("EGR and/or VVT System", "PM filter monitoring", "Exhaust Gas Sensor",
            "- Reserved -", "Boost Pressure", "- Reserved -",
            "NOx/SCR Monitor", "NMHC Catalyst[a]") {}
};

#endif //OPEN_OBD2_ENGINE_H










