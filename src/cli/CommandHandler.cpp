#include <utility>

//
// Created by me on 02/01/19.
//

#include "CommandHandler.h"

#include <unistd.h>
#include <poll.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "../../submodules/cpp-readline/src/Console.hpp"

CommandHandler::CommandHandler(CLI_TYPE type, ICommunicationInterface *interface) {
    obdHandler = OBDHandler::createInstance();
    com = interface;
    open = false;
    this->type = type;
}

int CommandHandler::start() {
    if (open) {
        return 1;
    }

    LOG(INFO) << "Starting CLI";
    exitRequested = false;
    initDone = false;

    if (com->openInterface() != 0) {
        return 1;
    }

    if (com->configureInterface() != 0) {
        return 1;
    }

    open = true;
    tCmdHandler = thread(&CommandHandler::cmdHandler, this);

    if (type == ECU) {
        configureVirtualVehicle(obdHandler->getVehicle());
        tRecv = thread(&CommandHandler::ecuRecvThread, this, com);
    } else {
        // run in background to give user to chance to abort if
        // the requests to the vehicle time out.
        tInit = thread(&CommandHandler::configureVehicle, this);
    }

    return 0;
}

void CommandHandler::stopHandler() {
    if (!open) {
        return;
    }

    exitRequested = true;

    LOG(DEBUG) << "Closing command handler";
    if (type == ECU) {
        tRecv.join();
    } else {
        tInit.join();
    }

    tCmdHandler.join();
    com->closeInterface();
    open = false;
    LOG(DEBUG) << "Closed command handler";
}


void CommandHandler::configureVirtualVehicle(Vehicle *vehicle) {
    for (auto &cmd: commandMapping) {
        vehicle->getPidSupport().setPidSupported(cmd.second.getService(), cmd.second.getPidId(), true);
    }

    initDone = true;
}

void CommandHandler::configureVehicle() {
    LOG(INFO) << "Getting supported pids from vehicle";

    // query the vehicle which PID's it supports
    vector<Service1Pids> pidIds{
            SupportedPid01_20, SupportedPid21_40, SupportedPid41_60, SupportedPid61_80,
            SupportedPid81_A0, SupportedPidA1_C0, SupportedPidC1_E0,
    };

    auto service = POWERTRAIN;
    bool anyError = false;
    for (const auto &id: pidIds) {
        Pid pid;
        if (obdHandler->getServiceAndPidInfo(id, service, pid, service) < 0) {
            LOG(ERROR) << "failed to get pid information";
        }

        anyError |= queryECU(pid, service).type != SUCCESS;

        if (exitRequested) {
            return;
        }
    }

    if (!anyError) {
        LOG(INFO) << "Successfully configured vehicle.";
    } else {
        LOG(INFO) << "Could not read all data from vehicle. Available commands may be incomplete.";
    }

    initDone = true;
}


void CommandHandler::ecuRecvThread(ICommunicationInterface *com) {
    int bufSize = 255;
    byte *answer;
    byte *buf = new byte[bufSize];
    memset(buf, 0, bufSize);
    int readSize = 0;


    while (!exitRequested) {
        com->receive(buf, bufSize, readSize);
        if (readSize <= 0) {
            continue;
        }

        // Answer frame
        if ((int) buf[0] >= ANSWER_OFFSET) {
            continue;
        }


        answer = obdHandler->createAnswerFrame(buf, readSize);
        com->send(answer, readSize);
        usleep(100);
    }

    delete[] answer;
    delete[] buf;
}

void CommandHandler::cmdHandler() {

    while (!initDone) {
        this_thread::sleep_for(1ms);
    }

    if (exitRequested) {
        return;
    }

    CppReadline::Console console(prompt);
    vector<string> supportedPids = getSupportedPids();

    console.registerCommand(command_help,
                            {std::bind(&CommandHandler::printHelp, this, std::placeholders::_1), vector<string>{}});

    console.registerCommand(command_get,
                            {std::bind(&CommandHandler::getDataCommand, this, std::placeholders::_1), supportedPids});

    console.registerCommand(command_set,
                            {std::bind(&CommandHandler::setDataCommand, this, std::placeholders::_1), supportedPids});

    console.registerCommand(command_sleep,
                            {std::bind(&CommandHandler::sleep, this, std::placeholders::_1), vector<string>{}});

    int retVal = 0;
    do {
        retVal = console.readLine();
        // We can also change the prompt based on last return value:
        if (retVal == CppReadline::Console::Ok) {
            console.setGreeting(prompt);
        } else {
            console.setGreeting("!>");
        }
    } while (retVal != CppReadline::Console::Quit && !exitRequested);

    if (!exitRequested) {
        exitRequested = true;
    }
}

bool CommandHandler::isOpen() {
    return open;
}

int CommandHandler::printHelp(const vector<string> &cmd) {
    if (cmd.size() == 1) {
        cout << "Usage cmd system [value]\n";
        cout << "Type 'help cmd' or 'help pid' to get more information." << endl;
        return 0;
    }

    if (cmd.at(1) == command_cmd) {
        cout << "Type 'help name_of_command\n";
        cout << "Available commands: \n";
        for (const auto &cmdName : commands) {
            cout << cmdName << " ";
        }
        cout << endl;
    } else if (cmd.at(1) == command_pid) {
        cout << "Supported Pids:\n";
        for (const auto &pid: getSupportedPids()) {
            cout << pid << " ";
        }
        cout << endl << "These additional commands can follow a set as well:" << endl;
        for (const auto &cmdName : specialSetCommands) {
            cout << cmdName << " ";
        }
        cout << endl;
    } else {
        cout << err_invalid_input << endl;
    }
    return 0;
}

vector<string> CommandHandler::getSupportedPids() const {
    Service service;
    Pid pid;
    vector<string> supportedPids = vector<string>();
    for (const auto &cmdName : commandMapping) {
        if (obdHandler->getServiceAndPidInfo(
                cmdName.second.getPidId(), cmdName.second.getService(), pid, service) != 0) {
            LOG(FATAL) << "Pid with ID " << pid.id << "does only exist in cmdHandler";
            continue;
        }

        if (obdHandler->getVehicle()->getPidSupport().getPidSupported(service, pid.id)) {
            supportedPids.push_back(cmdName.first);
        }
    }
    return supportedPids;
}

bool CommandHandler::getPid(const vector<string> &cmd, Pid &pid, Service &service) {
    if (cmd.size() == 1) {
        return false;
    }

    const CommandInfo *info = nullptr;
    for (const auto &cmdName : commandMapping) {
        if (cmd.at(1) == cmdName.first) {
            info = &cmdName.second;
        }
    }

    if (nullptr == info) {
        return false;
    }

    service = info->getService();
    if (obdHandler->getServiceAndPidInfo(info->getPidId(), service, pid, service) < 0) {
        cout << "Failed to retrieve info" << endl;
        return false;
    }

    return true;
}

DataObjectState CommandHandler::getData(const vector<string> &cmd) {
    Service service;
    Pid pid;
    DataObjectState state;
    if (cmd.size() == 1) {
        cout << "No system given. See help for more details" << endl;
        return DataObjectState(MISSING_ARGUMENTS);;
    }

    if (!getPid(cmd, pid, service)) {
        return getDataSpecial(cmd);
    }

    state = obdHandler->isPidSupported(service, pid.id);
    if (state.type != SUCCESS) {
        return state;
    }


    // query data from ecu if we are not one
    if (ECU != type) {
        state = queryECU(pid, service);
        if (state.type != SUCCESS) {
            return state;
        }
    }
    cout << pid.getFrameObject(obdHandler->getVehicle()).getPrintableData() << endl;
    return DataObjectState(SUCCESS);
}

DataObjectState CommandHandler::getDataSpecial(const vector<string> &cmd) {
    const string usage = "Argument missing. Usage: command <SERVICE> <PID>";
    if (cmd.at(1) == command_pid_by_number || cmd.at(1) == command_set_by_hex_number) {
        if (cmd.size() < 4) {
            cout << usage << endl;
            return DataObjectState(ErrorType::MISSING_ARGUMENTS);
        }

        int service = convertStringToT<int>(cmd.at(2));
        int pid;
        if (cmd.at(1) == command_pid_by_number) {
            pid = convertStringToT<int>(cmd.at(3));
        } else {
            pid = convertHexToInt(cmd.at(3));
        }

        bool supported =
                obdHandler->getVehicle()->getPidSupport().getPidSupported((Service) service, pid);
        cout << hex << "Support for pid " << pid << " new value: " << to_string(supported) << endl;
        return DataObjectState(ErrorType::SUCCESS);
    } else {
        cout << "Command " << cmd.at(1) << " is invalid." << endl;
        return DataObjectState(ErrorType::DATA_ERROR);
    }

}

DataObjectState CommandHandler::setData(const vector<string> &cmd) {
    if (ECU != type) {
        cout << "Only ECU does support setting values" << endl;
        return DataObjectState(NOT_SUPPORTED);
    }

    if (cmd.size() < 3) {
        cout << "Give at least 1 value" << endl;
        return DataObjectState(MISSING_ARGUMENTS);
    }

    int i;
    string val;
    for (i = 2; i < (int) cmd.size(); i++) {
        val += cmd.at(i) + " ";
    }
    val.pop_back();
    if (val.empty()) {
        cout << "Give at least 1 value" << endl;
        return DataObjectState(MISSING_ARGUMENTS);
    }

    Service service;
    Pid pid;
    // command is a pid.
    if (getPid(cmd, pid, service)) {
        return setDataViaPid(val, service, pid);
    } else {
        // try if it is special command
        return setDataSpecial(cmd);
    }
}


DataObjectState CommandHandler::setDataViaPid(string val, Service service, Pid pid) {
    DataObjectState state = obdHandler->isPidSupported(service, pid.id);
    if (state.type != SUCCESS) {
        return state;
    }
    // Try to update vehicle from data.
    auto &frameObject = pid.getFrameObject(obdHandler->getVehicle());
    DataObjectStateCollection sc = frameObject.setValueFromString(std::move(val));
    if (!sc.msg.empty()) {
        cout << sc.msg;
    }
    for (const auto &scState : sc.resultSet) {
        switch (scState.type) {
            case TOO_LARGE:
                cout << "Value " << scState.value << " is too large, max value: " << scState.max << endl;;
                return scState;
            case TOO_SMALL:
                cout << "Value " << scState.value << " is too small, min value: " << scState.min << endl;
                return scState;
            case MISSING_ARGUMENTS:
                cout << "Argument count mismatch. Count: " << scState.count << ", Expected: " << scState.expectedCount
                     << endl;;
                return scState;
            case INVALID_NUMBER:
                cout << "Input is not a valid number" << endl;
                return scState;
            case NOT_SUPPORTED:
                cout << "Not supported pid";
                return scState;
            case DATA_ERROR:
                cout << "Error while parsing data";
                return scState;
            default:
                break;
        }
    }

    cout << "New value: " << frameObject.getPrintableData() << endl;
    return DataObjectState(SUCCESS);
}


DataObjectState CommandHandler::setDataSpecial(const vector<string> &cmd) {
    const string usage = "Argument missing. Usage: command <SERVICE> <PID> <0|1>";
    if (cmd.at(1) == command_pid_by_number || cmd.at(1) == command_set_by_hex_number) {
        if (cmd.size() < 5) {
            cout << usage << endl;
            return DataObjectState(ErrorType::MISSING_ARGUMENTS);
        }

        int service = convertStringToT<int>(cmd.at(2));
        int pid;
        if (cmd.at(1) == command_pid_by_number) {
            pid = convertStringToT<int>(cmd.at(3));
        } else {
            pid = convertHexToInt(cmd.at(3));
        }

        int val = convertStringToT<int>(cmd.at(4));
        obdHandler->getVehicle()->getPidSupport().setPidSupported((Service) service, pid, val > 0);
        return DataObjectState(ErrorType::SUCCESS);
    } else {
        cout << "Command " << cmd.at(1) << " is invalid." << endl;
        return DataObjectState(ErrorType::DATA_ERROR);
    }
}

// Queries the vehicle and updates internal stored object
DataObjectState CommandHandler::queryECU(Pid pid, Service service) {
    if (obdHandler->isPidSupported(service, pid.id).type != SUCCESS) {
        return NOT_SUPPORTED;
    }

    const int maxTries = 3;
    int tries = 0;
    int frameLen = 0;
    auto retVal = DataObjectState(SUCCESS);
    auto timeout = 500ms;
    const string timeoutWarning = "Failed to retrieve pid " + to_string(pid.id)
                                  + " in service " + to_string(service) + " in " + to_string(maxTries) + " tries";

    byte *frame = pid.getQueryForService(service, frameLen);
    int bufSize = 255;
    byte *buf = new byte[bufSize];
    int readSize = 0;
    bool success;

    do {
        com->send(frame, frameLen);
        bool hasTimeout = false;
        auto t0 = chrono::high_resolution_clock::now();
        while (readSize <= 0 && !hasTimeout) {
            com->receive(buf, bufSize, readSize);
            hasTimeout = (chrono::high_resolution_clock::now() - t0) > timeout;
        }

        if (hasTimeout || readSize < 1) {
            continue;
        }

        obdHandler->updateFromFrame(buf, readSize);
        success = true;
    } while (!success && tries++ < maxTries);


    if (!success) {
        LOG(WARNING) << timeoutWarning;
        retVal = DataObjectState(TIMEOUT);
    }

    delete[] frame;
    delete[] buf;
    return retVal;
}


OBDHandler &CommandHandler::getObdHandler() {
    return *obdHandler;
}

bool CommandHandler::isInitDone() {
    return initDone;
}

bool CommandHandler::isExitRequested() {
    return exitRequested;
}

int CommandHandler::getDataCommand(const vector<string> &cmd) {
    return getData(cmd).type;
}

int CommandHandler::setDataCommand(const vector<string> &cmd) {
    return setData(cmd).type;
}

int CommandHandler::sleep(const vector<string> &cmd) {
    if (cmd.size() < 2) {
        cout << "Give a sleep time in milli seconds";
        return 1;
    }

    int sleepTime = convertStringToT<int>(cmd.at(1));
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    return 0;
}

