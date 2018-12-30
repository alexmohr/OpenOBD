#include <utility>

//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_ENGINE_H
#define OPEN_OBD2_ENGINE_H

#include <string>
#include "../OBDTest.h"
#include "../dataObject/CalculatedDataObject.h"

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

    unique_ptr<DataObject<EngineType>> type;

    unique_ptr<CalculatedDataObject<byte, float>> calculatedLoad;
    unique_ptr<CalculatedDataObject<byte, short>> coolantTemperature;

    unique_ptr<CalculatedDataObject<byte, float>> shortTermFuelTrimBank1;
    unique_ptr<CalculatedDataObject<byte, float>> longTermFuelTrimBank1;
    unique_ptr<CalculatedDataObject<byte, float>> shortTermFuelTrimBank2;
    unique_ptr<CalculatedDataObject<byte, float>> longTermFuelTrimBank2;


    unique_ptr<CalculatedDataObject<byte, unsigned short>> fuelPressure;
    unique_ptr<DataObject<byte>> intakeManifoldAbsolutePressure;
    unique_ptr<CalculatedDataObject<unsigned short, float>> engineRPM;

    unique_ptr<CalculatedDataObject<byte, float>> timingAdvance;
    unique_ptr<CalculatedDataObject<byte, short>> intakeAirTemperature;
    unique_ptr<CalculatedDataObject<unsigned short, float>> mafAirFlowRate;


public:
    explicit Engine();

    ~Engine() = default;

    unsigned int toFrameForMonitoringSystem(unsigned int &data);

    void fromFrameForMonitoringSystem(byte *frame, int size);

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

    CalculatedDataObject<byte, float> &getLoad();

    CalculatedDataObject<byte, short> &getCoolantTemperature();


    CalculatedDataObject<byte, float> &getShortTermFuelTrimBank1();

    CalculatedDataObject<byte, float> &getLongTermFuelTrimBank1();

    CalculatedDataObject<byte, float> &getShortTermFuelTrimBank2();

    CalculatedDataObject<byte, float> &getLongTermFuelTrimBank2();

    CalculatedDataObject<byte, unsigned short> &getFuelPressure();

    DataObject<byte> &getIntakeManifoldAbsolutePressure();

    CalculatedDataObject<unsigned short, float> &getEngineRPM();

    CalculatedDataObject<byte, float> &getTimingAdvance();

    CalculatedDataObject<byte, short> &getIntakeAirTemperature();

    CalculatedDataObject<unsigned short, float> &getMAFAirFlowRate();


};

#endif //OPEN_OBD2_ENGINE_H










