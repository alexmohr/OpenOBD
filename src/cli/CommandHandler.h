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
#include "CommandInfo.h"

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

    map<string, CommandInfo> commandMapping{
            {"MonitoringStatusSinceDTCsCleared",    CommandInfo(Service::POWERTRAIN, MonitoringStatusSinceDTCsCleared)},
            {"FreezeDTCPid",                        CommandInfo(Service::POWERTRAIN, FreezeDTCPid)},
            {"FuelSystemStatus",                    CommandInfo(Service::POWERTRAIN, FuelSystemStatus)},
            {"CalculatedEngineLoad",                CommandInfo(Service::POWERTRAIN, CalculatedEngineLoad)},
            {"EngineCoolantTemperature",            CommandInfo(Service::POWERTRAIN, EngineCoolantTemperature)},
            {"ShortTermFuelTrimBank1",              CommandInfo(Service::POWERTRAIN, ShortTermFuelTrimBank1)},
            {"LongTermFuelTrimBank1",               CommandInfo(Service::POWERTRAIN, LongTermFuelTrimBank1)},
            {"ShortTermFuelTrimBank2",              CommandInfo(Service::POWERTRAIN, ShortTermFuelTrimBank2)},
            {"LongTermFuelTrimBank2",               CommandInfo(Service::POWERTRAIN, LongTermFuelTrimBank2)},
            {"FuelPressure",                        CommandInfo(Service::POWERTRAIN, FuelPressure)},
            {"IntakeManifoldAbsolutePressure",      CommandInfo(Service::POWERTRAIN, IntakeManifoldAbsolutePressure)},
            {"EngineRPM",                           CommandInfo(Service::POWERTRAIN, EngineRPM)},
            {"VehicleSpeed",                        CommandInfo(Service::POWERTRAIN, VehicleSpeed)},
            {"TimingAdvance",                       CommandInfo(Service::POWERTRAIN, TimingAdvance)},
            {"IntakeAirTemperature",                CommandInfo(Service::POWERTRAIN, IntakeAirTemperature)},
            {"MAFAirFlowRate",                      CommandInfo(Service::POWERTRAIN, MAFAirFlowRate)},
            {"ThrottlePosition",                    CommandInfo(Service::POWERTRAIN, ThrottlePosition)},
            {"CommandedSecondaryAirStatus",         CommandInfo(Service::POWERTRAIN, CommandedSecondaryAirStatus)},
            {"OxygenSensorsPresent",                CommandInfo(Service::POWERTRAIN, OxygenSensorsPresent)},
            {"BankOxygenSensor1",                   CommandInfo(Service::POWERTRAIN, BankOxygenSensor1)},
            {"BankOxygenSensor2",                   CommandInfo(Service::POWERTRAIN, BankOxygenSensor2)},
            {"BankOxygenSensor3",                   CommandInfo(Service::POWERTRAIN, BankOxygenSensor3)},
            {"BankOxygenSensor4",                   CommandInfo(Service::POWERTRAIN, BankOxygenSensor4)},
            {"BankOxygenSensor5",                   CommandInfo(Service::POWERTRAIN, BankOxygenSensor5)},
            {"BankOxygenSensor6",                   CommandInfo(Service::POWERTRAIN, BankOxygenSensor6)},
            {"BankOxygenSensor7",                   CommandInfo(Service::POWERTRAIN, BankOxygenSensor7)},
            {"BankOxygenSensor8",                   CommandInfo(Service::POWERTRAIN, BankOxygenSensor8)},
            {"OBDStandardsVehicleConformsTo",       CommandInfo(Service::POWERTRAIN, OBDStandardsVehicleConformsTo)},
            {"OxygenSensorsPresent4Banks",          CommandInfo(Service::POWERTRAIN, OxygenSensorsPresent4Banks)},
            {"AuxiliaryInputStatus",                CommandInfo(Service::POWERTRAIN, AuxiliaryInputStatus)},
            {"RunTimeSinceEngineStart",             CommandInfo(Service::POWERTRAIN, RunTimeSinceEngineStart)},
            {"DistanceTraveledWithMilOn",           CommandInfo(Service::POWERTRAIN, DistanceTraveledWithMilOn)},
            {"FuelRailPressure",                    CommandInfo(Service::POWERTRAIN, FuelRailPressure)},
            {"FuelRailGaugePressure",               CommandInfo(Service::POWERTRAIN, FuelRailGaugePressure)},
            {"FuelRailOxygenSensor1",               CommandInfo(Service::POWERTRAIN, FuelRailOxygenSensor1)},
            {"FuelRailOxygenSensor2",               CommandInfo(Service::POWERTRAIN, FuelRailOxygenSensor2)},
            {"FuelRailOxygenSensor3",               CommandInfo(Service::POWERTRAIN, FuelRailOxygenSensor3)},
            {"FuelRailOxygenSensor4",               CommandInfo(Service::POWERTRAIN, FuelRailOxygenSensor4)},
            {"FuelRailOxygenSensor5",               CommandInfo(Service::POWERTRAIN, FuelRailOxygenSensor5)},
            {"FuelRailOxygenSensor6",               CommandInfo(Service::POWERTRAIN, FuelRailOxygenSensor6)},
            {"FuelRailOxygenSensor7",               CommandInfo(Service::POWERTRAIN, FuelRailOxygenSensor7)},
            {"FuelRailOxygenSensor8",               CommandInfo(Service::POWERTRAIN, FuelRailOxygenSensor8)},
            {"CommandedEGR",                        CommandInfo(Service::POWERTRAIN, CommandedEGR)},
            {"EGRError",                            CommandInfo(Service::POWERTRAIN, EGRError)},
            {"CommandedEvaporativePurge",           CommandInfo(Service::POWERTRAIN, CommandedEvaporativePurge)},
            {"FuelTankLevelInput",                  CommandInfo(Service::POWERTRAIN, FuelTankLevelInput)},
            {"WarmUpsSinceCodesCleared",            CommandInfo(Service::POWERTRAIN, WarmUpsSinceCodesCleared)},
            {"DistanceTraveledSinceCodesCleared",   CommandInfo(Service::POWERTRAIN,
                                                                DistanceTraveledSinceCodesCleared)},
            {"EvaporativePurgeSystemVaporPressure", CommandInfo(Service::POWERTRAIN,
                                                                EvaporativePurgeSystemVaporPressure)},
            {"AbsoluteBarometricPressure",          CommandInfo(Service::POWERTRAIN, AbsoluteBarometricPressure)},
            {"ExtendedRangeOxygenSensor1",          CommandInfo(Service::POWERTRAIN, ExtendedRangeOxygenSensor1)},
            {"ExtendedRangeOxygenSensor2",          CommandInfo(Service::POWERTRAIN, ExtendedRangeOxygenSensor2)},
            {"ExtendedRangeOxygenSensor3",          CommandInfo(Service::POWERTRAIN, ExtendedRangeOxygenSensor3)},
            {"ExtendedRangeOxygenSensor4",          CommandInfo(Service::POWERTRAIN, ExtendedRangeOxygenSensor4)},
            {"ExtendedRangeOxygenSensor5",          CommandInfo(Service::POWERTRAIN, ExtendedRangeOxygenSensor5)},
            {"ExtendedRangeOxygenSensor6",          CommandInfo(Service::POWERTRAIN, ExtendedRangeOxygenSensor6)},
            {"ExtendedRangeOxygenSensor7",          CommandInfo(Service::POWERTRAIN, ExtendedRangeOxygenSensor7)},
            {"ExtendedRangeOxygenSensor8",          CommandInfo(Service::POWERTRAIN, ExtendedRangeOxygenSensor8)},
            {"CatalystTemperatureBank1Sensor1",     CommandInfo(Service::POWERTRAIN, CatalystTemperatureBank1Sensor1)},
            {"CatalystTemperatureBank2Sensor1",     CommandInfo(Service::POWERTRAIN, CatalystTemperatureBank2Sensor1)},
            {"CatalystTemperatureBank1Sensor2",     CommandInfo(Service::POWERTRAIN, CatalystTemperatureBank1Sensor2)},
            {"CatalystTemperatureBank2Sensor2",     CommandInfo(Service::POWERTRAIN, CatalystTemperatureBank2Sensor2)},
            {"MonitorStatusThisDriveCycle",         CommandInfo(Service::POWERTRAIN, MonitorStatusThisDriveCycle)},
            {"ControlModuleVoltage",                CommandInfo(Service::POWERTRAIN, ControlModuleVoltage)},
            {"AbsoluteLoadValue",                   CommandInfo(Service::POWERTRAIN, AbsoluteLoadValue)},
            {"FuelAirCommandedEquivalenceRatio",    CommandInfo(Service::POWERTRAIN, FuelAirCommandedEquivalenceRatio)},
            {"RelativeThrottlePosition",            CommandInfo(Service::POWERTRAIN, RelativeThrottlePosition)},
            {"AmbientAirTemperature",               CommandInfo(Service::POWERTRAIN, AmbientAirTemperature)},
    };


private:
    std::thread tCanHandler;
    std::thread tCmdHandler;
    std::thread tInit;
    bool exitRequested;
    unique_ptr<OBDHandler> obdHandler;
    bool open;
    bool initDone;
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

    bool isInitDone();

    OBDHandler &getObdHandler();
private:
    void configureVirtualVehicle(Vehicle *vehicle);

    void configureVehicle();

    void comHandler(ICommunicationInterface *com);

    void cmdHandler();

    void printHelp(std::vector<std::string> &cmd);

    int queryECU(Pid pid, Service service);


};


#endif //OPEN_OBD2_COMMANDHANDLER_H
