#include <utility>

//
// Created by me on 02/01/19.
//

#include "CommandHandler.h"

#include <unistd.h>
#include <poll.h>

#include <readline/readline.h>
#include <readline/history.h>


CommandHandler::CommandHandler(CLI_TYPE type, shared_ptr<ICommunicationInterface> comInterface,
                               shared_ptr<OBDHandler> obdHandler) {
    this->obdHandler = obdHandler;
    this->comInterface = comInterface;
    this->vehicleDataProvider = make_unique<VehicleDataProvider>(obdHandler, comInterface);
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
    cmdHandlerRdy = false;

    if (comInterface->openInterface() != 0) {
        return 1;
    }

    if (comInterface->configureInterface() != 0) {
        return 1;
    }

    open = true;
    tCmdHandler = thread(&CommandHandler::cmdHandler, this);

    if (type == ECU) {
        configureVirtualVehicle(obdHandler->getVehicle());
        tRecv = thread(&CommandHandler::ecuRecvThread, this);
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
    comInterface->closeInterface();
    open = false;
    LOG(DEBUG) << "Closed command handler";
}


void CommandHandler::configureVirtualVehicle(Vehicle *vehicle) {
    for (auto &cmd: COMMAND_MAPPING) {
        vehicle->getPidSupport().setPidSupported(cmd.second.getService(), cmd.second.getPidId(), true);
    }

    initDone = true;
}

void CommandHandler::configureVehicle() {
    LOG(INFO) << "Getting supported pids from vehicle";

    bool anyError = vehicleDataProvider->configureVehicle();
    if (!anyError) {
        LOG(INFO) << "Successfully configured vehicle.";
    } else {
        LOG(INFO) << "Could not read all data from vehicle. Available commands may be incomplete.";
    }

    initDone = true;
}


void CommandHandler::ecuRecvThread() {
    int bufSize = 255;
    byte *answer = nullptr;
    byte *buf = new byte[bufSize];
    memset(buf, 0, bufSize);
    int readSize = 0;


    while (!exitRequested) {
        comInterface->receive(buf, bufSize, readSize);
        if (readSize <= 0) {
            continue;
        }

        // Answer frame
        if ((int) buf[0] >= ANSWER_OFFSET) {
            continue;
        }

        answer = obdHandler->createAnswerFrame(buf, readSize);
        comInterface->send(answer, readSize);
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

    console = make_unique<CppReadline::Console>(prompt);

    vector<string> supportedPids = vehicleDataProvider->getSupportedPids();

    console->registerCommand(command_help,
                             {std::bind(&CommandHandler::printHelp, this, std::placeholders::_1), vector<string>{}});

    console->registerCommand(command_get,
                             {std::bind(&CommandHandler::getDataCommand, this, std::placeholders::_1), supportedPids});

    console->registerCommand(command_set,
                             {std::bind(&CommandHandler::setDataCommand, this, std::placeholders::_1), supportedPids});

    console->registerCommand(command_sleep,
                             {std::bind(&CommandHandler::sleep, this, std::placeholders::_1), vector<string>{}});

    cmdHandlerRdy = true;

    int retVal = 0;
    do {
        retVal = console->readLine();
        // We can also change the prompt based on last return value:
        if (retVal == CppReadline::Console::Ok) {
            console->setGreeting(prompt);
        } else {
            console->setGreeting("!>");
        }
    } while (retVal != CppReadline::Console::Quit && !exitRequested);

    if (!exitRequested) {
        exitRequested = true;
    }

    cmdHandlerRdy = false;
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
        for (const auto &pid: vehicleDataProvider->getSupportedPids()) {
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

bool CommandHandler::getPid(const vector<string> &cmd, Pid &pid, Service &service) {
    if (cmd.size() == 1) {
        return false;
    }

    const CommandInfo *info = nullptr;
    for (const auto &cmdName : COMMAND_MAPPING) {
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
        state = vehicleDataProvider->queryVehicle(pid, service);
        if (state.type != SUCCESS) {
            return state;
        }
    }

    auto *frameObject = pid.getFrameObject(obdHandler->getVehicle());
    if (frameObject == nullptr) {
        return DataObjectState(NOT_SUPPORTED);
    }
    cout << frameObject->getPrintableData() << endl;
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
    auto *frameObject = pid.getFrameObject(obdHandler->getVehicle());
    if (nullptr == frameObject) {
        cout << "Not supported Pid or service";
        return NOT_SUPPORTED;
    }

    DataObjectStateCollection sc = frameObject->setValueFromString(std::move(val));
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

    cout << "New value: " << frameObject->getPrintableData() << endl;
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

void CommandHandler::executeFile(string fileName) {
    while (!cmdHandlerRdy) {
        this_thread::sleep_for(100ms);
    }
    console->executeFile(fileName);
}

