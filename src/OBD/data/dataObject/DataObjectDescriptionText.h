//
// Created by me on 30/12/18.
//

#ifndef OPEN_OBD2_DATAOBJECTDESCRIPTIONS_H
#define OPEN_OBD2_DATAOBJECTDESCRIPTIONS_H

#include <string>

using namespace std;

// Todo these text should come from config some day
class DataObjectDescriptionText {
public:
    const static string getMonitorStatusMIL();

    const static string getMonitorStatusDTC();

    const static string getComponents();

    const static string getMisfire();

    const static string getFuelSystem();

public:
    const static string getOBDTest();

    const static string getOBDTestAvailable();

    const static string getOBDTestIncomplete();

public:
    const static string getBankOxygenSensorVoltage();

    const static string getBankOxygenSensorShortFuelTrim();

public:
    const static string getCatalystTemperatureSensor(int bank, int sensor);

public:
    const static string getCalculatedLoad();

    const static string getCoolantTemperature();

    const static string getShortTermFuelTrimBank(int bank);

    const static string getLongTermFuelTrimBank(int bank);

    const static string getFuelPressure();

    const static string getIntakeManifoldAbsolutePressure();

    const static string getEngineRPM();

    const static string getTimingAdvance();

    const static string getIntakeAirTemperature();

    const static string getMafAirFlowRate();

    const static string getEngineType();

public:
    const static string getDataTroubleCode();

public:
    const static string getVoltage();

    const static string getShortTermFuelTrim();

public:
    const static string getBankSensorPresent(int bank, int sensor);

public:
    const static string getBankSensorPresentIn4Banks(int bank, int sensor);

public:
    const static string getFuelAirEquivalenceRatio();

    const static string getCurrent();

public:
    const static string getPidSupported(int pid);

public:
    const static string getThrottlePosition();

    const static string getRelativeThrottlePosition();

    const static string getAbsoluteThrottlePosition(string val);

public:
    const static string getFuelSystemState(int system);

public:
    const static string getCommandedSecondaryAirStatus();

    const static string getSpeed();

    const static string getWarmUpsSinceCodesCleared();

    const static string getDistanceTraveledSinceCodesCleared();

    const static string getAuxiliaryInputStatus();

    const static string getRunTimeSinceEngineStart();

    const static string getDistanceTraveledWithMilOn();

    const static string getAbsoluteBarometricPressure();

    const static string getFuelRailPressure();

    const static string getFuelRailGaugePressure();

    const static string getCommandedEGR();

    const static string getEgrError();

    const static string getCommandedEvaporativePurge();

    const static string getFuelTankLevelInput();

    const static string getEvaporativePurgeSystemVaporPressure();

    const static string getControlModuleVoltage();

    const static string getAbsoluteLoadValue();

    const static string getFuelAirCommandedEquivalenceRatio();

    const static string getAmbientAirTemperature();
};


#endif //OPEN_OBD2_DATAOBJECTDESCRIPTIONS_H
