//
// Created by me on 02/01/19.
//

#ifndef OPEN_OBD2_COMMANDHANDLER_H
#define OPEN_OBD2_COMMANDHANDLER_H

#include <thread>
#include <map>
#include <mutex>
#include <condition_variable>
#include "../../OBD/Pid.h"
#include "../../communication/CanIsoTP.h"
#include "../../communication/ELMClient.h"
#include "../../communication/ELM327WifiServer.h"
#include "../../OBD/OBDHandler.h"
#include "../CommandInfo.h"
#include "../../../submodules/cpp-readline/src/Console.hpp"

using namespace std;


enum CLI_TYPE {
    ECU,
    TESTER,
    WIFI_ELM,
    SERIAL_ELM
};

class CommandHandler {
private:

    const string command_get = "get";
    const string command_set = "set";
    const string command_sleep = "sleep";
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

    unique_ptr<CppReadline::Console> console;

public:



private:
    std::thread tRecv;
    std::thread tCmdHandler;
    std::thread tInit;
    bool exitRequested;
    unique_ptr<OBDHandler> obdHandler;
    bool open;
    bool initDone;
    bool cmdHandlerRdy;
    CLI_TYPE type;
    ICommunicationInterface *com;


public:
    CommandHandler(CLI_TYPE type, ICommunicationInterface *com);

public:

    int start();

    void stopHandler();

    bool isOpen();

    bool isExitRequested();

    void executeFile(string fileName);

public: // public for testing
    DataObjectState setData(const vector<string> &cmd);

    DataObjectState getData(const vector<string> &cmd);

    bool getPid(const vector<string> &cmd, Pid &pid, Service &service);

    bool isInitDone();

    OBDHandler &getObdHandler();

private:

    int sleep(const vector<string> &cmd);

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

    vector<string> getSupportedPids() const;
};


#endif //OPEN_OBD2_COMMANDHANDLER_H
