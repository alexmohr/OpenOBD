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
#include "../VehicleDataProvider.h"
#include "../../../submodules/cpp-readline/src/Console.hpp"

using namespace std;

class CommandHandler {
private:

    const string command_get_1 = "get_1";
    const string command_set_1 = "set_1";
    const string command_get_2 = "get_2";
    const string command_sleep = "sleep";
    const string command_help = "?";
    const string command_cmd = "cmd";
    const string command_pid = "pid";
    const string prompt = ">> ";

    const string command_pid_by_number_1 = "PidByNumber_1";
    const string command_set_by_hex_number_2 = "PidByHexNumber_1";

    const string err_invalid_input = "Invalid usage. See help";
    vector<string> commands{
            command_get_1,
            command_set_1,
            command_get_2,
            command_help
    };

    vector<string> specialSetCommands{
            command_pid_by_number_1,
            command_set_by_hex_number_2
    };

private:

    std::thread tRecv;
    std::thread tCmdHandler;
    std::thread tInit;
    shared_ptr<OBDHandler> obdHandler;
    shared_ptr<ICommunicationInterface> comInterface;
    shared_ptr<VehicleDataProvider> vehicleDataProvider;
    unique_ptr<CppReadline::Console> console;
    bool open;
    bool cmdHandlerRdy;
    bool exitRequested;
    APP_TYPE type;


public:
    CommandHandler(APP_TYPE type, shared_ptr<ICommunicationInterface> comInterface,
                   shared_ptr<OBDHandler> obdHandler, shared_ptr<VehicleDataProvider> vehicleDataProvider);

public:

    int start();

    void stopHandler();

    bool isOpen();

    bool isExitRequested();

    void executeFile(string fileName);

public: // public for testing
    DataObjectState setData(const vector<string> &cmd);

    DataObjectState getData(const vector<string> &cmd, bool freezeFrameVehicle);

    bool isInitDone();

    OBDHandler &getObdHandler();

    VehicleDataProvider *getVehicleDataProvider();

private:

    int sleep(const vector<string> &cmd);

    int getDataCommand(const vector<string> &cmd, bool freezeFrameVehicle);

    int setDataCommand(const vector<string> &cmd);

    DataObjectState setDataViaPid(string val, Service service, Pid pid);

    DataObjectState setDataSpecial(const vector<string> &cmd);

    DataObjectState getDataSpecial(const vector<string> &cmd);

    void configureVirtualVehicle(Vehicle *vehicle);

    void ecuRecvThread();

    void cmdHandler();

    int printHelp(const vector<string> &cmd) const;

    void setDataGetCommand(const map<Service, PidCollection> &pidCollection, string getCmd, bool freezeFrameVehicle);


};


#endif //OPEN_OBD2_COMMANDHANDLER_H
