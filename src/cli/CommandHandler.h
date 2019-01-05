//
// Created by me on 02/01/19.
//

#ifndef OPEN_OBD2_COMMANDHANDLER_H
#define OPEN_OBD2_COMMANDHANDLER_H

#include <thread>
#include <map>
#include <mutex>
#include <condition_variable>
#include "../OBD/Pid.h"
#include "../CAN/CanIsoTP.h"
#include "../CAN/ELM327.h"
#include "../OBD/OBDHandler.h"

using namespace std;


enum CLI_TYPE {
    TESTER,
    ELM,
    ECU
};

class CommandHandler {
private:

    const string command_get = "get";
    const string command_set = "set";
    const string command_help = "help";
    const string command_cmd = "cmd";
    const string command_pid = "pid";

    const string err_invalid_input = "Invalid usage. See help";
    vector<string> commands{
            command_get,
            command_set,
            command_help
    };
public:
    map<string, int> commandMapping{
            {"MonitoringStatusSinceDTCsCleared",    MonitoringStatusSinceDTCsCleared},
            {"FreezeDTCPid",                        FreezeDTCPid},
            {"FuelSystemStatus",                    FuelSystemStatus},
            {"CalculatedEngineLoad",                CalculatedEngineLoad},
            {"EngineCoolantTemperature",            EngineCoolantTemperature},
            {"ShortTermFuelTrimBank1",              ShortTermFuelTrimBank1},
            {"LongTermFuelTrimBank1",               LongTermFuelTrimBank1},
            {"ShortTermFuelTrimBank2",              ShortTermFuelTrimBank2},
            {"LongTermFuelTrimBank2",               LongTermFuelTrimBank2},
            {"FuelPressure",                        FuelPressure},
            {"IntakeManifoldAbsolutePressure",      IntakeManifoldAbsolutePressure},
            {"EngineRPM",                           EngineRPM},
            {"VehicleSpeed",                        VehicleSpeed},
            {"TimingAdvance",                       TimingAdvance},
            {"IntakeAirTemperature",                IntakeAirTemperature},
            {"MAFAirFlowRate",                      MAFAirFlowRate},
            {"ThrottlePosition",                    ThrottlePosition},
            {"CommandedSecondaryAirStatus",         CommandedSecondaryAirStatus},
            {"OxygenSensorsPresent",                OxygenSensorsPresent},
            {"BankOxygenSensor1",                   BankOxygenSensor1},
            {"BankOxygenSensor2",                   BankOxygenSensor2},
            {"BankOxygenSensor3",                   BankOxygenSensor3},
            {"BankOxygenSensor4",                   BankOxygenSensor4},
            {"BankOxygenSensor5",                   BankOxygenSensor5},
            {"BankOxygenSensor6",                   BankOxygenSensor6},
            {"BankOxygenSensor7",                   BankOxygenSensor7},
            {"BankOxygenSensor8",                   BankOxygenSensor8},
            {"OBDStandardsVehicleConformsTo",       OBDStandardsVehicleConformsTo},
            {"OxygenSensorsPresent4Banks",          OxygenSensorsPresent4Banks},
            {"AuxiliaryInputStatus",                AuxiliaryInputStatus},
            {"RunTimeSinceEngineStart",             RunTimeSinceEngineStart},
            {"DistanceTraveledWithMilOn",           DistanceTraveledWithMilOn},
            {"FuelRailPressure",                    FuelRailPressure},
            {"FuelRailGaugePressure",               FuelRailGaugePressure},
            {"FuelRailOxygenSensor1",               FuelRailOxygenSensor1},
            {"FuelRailOxygenSensor2",               FuelRailOxygenSensor2},
            {"FuelRailOxygenSensor3",               FuelRailOxygenSensor3},
            {"FuelRailOxygenSensor4",               FuelRailOxygenSensor4},
            {"FuelRailOxygenSensor5",               FuelRailOxygenSensor5},
            {"FuelRailOxygenSensor6",               FuelRailOxygenSensor6},
            {"FuelRailOxygenSensor7",               FuelRailOxygenSensor7},
            {"FuelRailOxygenSensor8",               FuelRailOxygenSensor8},
            {"CommandedEGR",                        CommandedEGR},
            {"EGRError",                            EGRError},
            {"CommandedEvaporativePurge",           CommandedEvaporativePurge},
            {"FuelTankLevelInput",                  FuelTankLevelInput},
            {"WarmUpsSinceCodesCleared",            WarmUpsSinceCodesCleared},
            {"DistanceTraveledSinceCodesCleared",   DistanceTraveledSinceCodesCleared},
            {"EvaporativePurgeSystemVaporPressure", EvaporativePurgeSystemVaporPressure},
            {"AbsoluteBarometricPressure",          AbsoluteBarometricPressure},
            {"ExtendedRangeOxygenSensor1",          ExtendedRangeOxygenSensor1},
            {"ExtendedRangeOxygenSensor2",          ExtendedRangeOxygenSensor2},
            {"ExtendedRangeOxygenSensor3",          ExtendedRangeOxygenSensor3},
            {"ExtendedRangeOxygenSensor4",          ExtendedRangeOxygenSensor4},
            {"ExtendedRangeOxygenSensor5",          ExtendedRangeOxygenSensor5},
            {"ExtendedRangeOxygenSensor6",          ExtendedRangeOxygenSensor6},
            {"ExtendedRangeOxygenSensor7",          ExtendedRangeOxygenSensor7},
            {"ExtendedRangeOxygenSensor8",          ExtendedRangeOxygenSensor8},
            {"CatalystTemperatureBank1Sensor1",     CatalystTemperatureBank1Sensor1},
            {"CatalystTemperatureBank2Sensor1",     CatalystTemperatureBank2Sensor1},
            {"CatalystTemperatureBank1Sensor2",     CatalystTemperatureBank1Sensor2},
            {"CatalystTemperatureBank2Sensor2",     CatalystTemperatureBank2Sensor2},
            {"MonitorStatusThisDriveCycle",         MonitorStatusThisDriveCycle},
            {"ControlModuleVoltage",                ControlModuleVoltage},
            {"AbsoluteLoadValue",                   AbsoluteLoadValue},
            {"FuelAirCommandedEquivalenceRatio",    FuelAirCommandedEquivalenceRatio},
            {"RelativeThrottlePosition",            RelativeThrottlePosition},
            {"AmbientAirTemperature",               AmbientAirTemperature},
    };
private:
    std::thread tCanHandler;
    std::thread tCmdHandler;
    bool exitRequested;
    unique_ptr<OBDHandler> obdHandler;
    bool open;
    CLI_TYPE type;
    ICommunicationInterface *com;

    std::mutex dataMutex;
    std::condition_variable dataCv;

    int expectedPid;

public:
    CommandHandler(CLI_TYPE type, ICommunicationInterface *com);

public:

    bool start();

    void stopHandler();

    bool isOpen();

public: // public for testing
    int setData(std::vector<std::string> &cmd);

    int getData(std::vector<std::string> &cmd);

    bool getPid(std::vector<std::string> &cmd, Pid &pid, Service &service);

    OBDHandler &getObdHandler();
private:
    void configureVirtualVehicle(Vehicle *vehicle);

    void configureVehicle();

    void comHandler(ICommunicationInterface *com);

    void cmdHandler(ICommunicationInterface *com);

    void printHelp(std::vector<std::string> &cmd);

    int queryECU(Pid pid, Service service);


};


#endif //OPEN_OBD2_COMMANDHANDLER_H
