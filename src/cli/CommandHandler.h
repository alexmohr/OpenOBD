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
#include "../communication/CanIsoTP.h"
#include "../communication/ELM327WifiClient.h"
#include "../communication/ELM327WifiServer.h"
#include "../OBD/OBDHandler.h"
#include "CommandInfo.h"

using namespace std;


enum CLI_TYPE {
    ECU,
    TESTER,
    ELM
};

class CommandHandler {
private:

    const string command_get = "get";
    const string command_set = "set";
    const string command_help = "?";
    const string command_cmd = "cmd";
    const string command_pid = "pid";
    const string prompt = ">> ";

    const string command_pid_by_number = "PidByNumber";
    const string command_set_by_hex_number = "PidByHexNumber";

    const string err_invalid_input = "Invalid usage. See help";
    vector<string> commands{
            command_get,
            command_set,
            command_help
    };

    vector<string> specialSetCommands{
            command_pid_by_number,
            command_set_by_hex_number
    };

public:

    map<string, CommandInfo> commandMapping{

            {"SupportedPid01_20",                   CommandInfo(Service::POWERTRAIN, SupportedPid01_20)},
            {"SupportedPid21_40",                   CommandInfo(Service::POWERTRAIN, SupportedPid21_40)},
            {"SupportedPid41_60",                   CommandInfo(Service::POWERTRAIN, SupportedPid41_60)},
            {"SupportedPid61_80",                   CommandInfo(Service::POWERTRAIN, SupportedPid61_80)},
            {"SupportedPid81_A0",                   CommandInfo(Service::POWERTRAIN, SupportedPid81_A0)},
            {"SupportedPidA1_C0",                   CommandInfo(Service::POWERTRAIN, SupportedPidA1_C0)},
            {"SupportedPidC1_E0",                   CommandInfo(Service::POWERTRAIN, SupportedPidC1_E0)},
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
            {"AbsoluteThrottlePositionB",           CommandInfo(Service::POWERTRAIN, AbsoluteThrottlePositionB)},
            {"AbsoluteThrottlePositionC",           CommandInfo(Service::POWERTRAIN, AbsoluteThrottlePositionC)},
            {"AcceleratorPedalPositionD",           CommandInfo(Service::POWERTRAIN, AcceleratorPedalPositionD)},
            {"AcceleratorPedalPositionE",           CommandInfo(Service::POWERTRAIN, AcceleratorPedalPositionE)},
            {"AcceleratorPedalPositionF",           CommandInfo(Service::POWERTRAIN, AcceleratorPedalPositionF)},
    };


private:
    std::thread tRecv;
    std::thread tCmdHandler;
    std::thread tInit;
    bool exitRequested;
    unique_ptr<OBDHandler> obdHandler;
    bool open;
    bool initDone;
    CLI_TYPE type;
    ICommunicationInterface *com;


public:
    CommandHandler(CLI_TYPE type, ICommunicationInterface *com);

public:

    int start();

    void stopHandler();

    bool isOpen();

    bool isExitRequested();

public: // public for testing
    DataObjectState setData(const vector<string> &cmd);

    DataObjectState getData(const vector<string> &cmd);

    bool getPid(const vector<string> &cmd, Pid &pid, Service &service);

    bool isInitDone();

    OBDHandler &getObdHandler();

private:

    int getDataCommand(const vector<string> &cmd);

    int setDataCommand(const vector<string> &cmd);

    DataObjectState setDataViaPid(string val, Service service, Pid pid);

    DataObjectState setDataSpecial(const vector<string> &cmd);

    DataObjectState getDataSpecial(const vector<string> &cmd);

    void configureVirtualVehicle(Vehicle *vehicle);

    void configureVehicle();

    void ecuRecvThread(ICommunicationInterface *com);

    void cmdHandler();

    int printHelp(const vector<string> &cmd);

    DataObjectState queryECU(Pid pid, Service service);

};


#endif //OPEN_OBD2_COMMANDHANDLER_H
