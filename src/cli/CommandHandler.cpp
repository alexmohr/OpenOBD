//
// Created by me on 02/01/19.
//

#include "CommandHandler.h"


CommandHandler::CommandHandler() {

}


bool CommandHandler::start(char *canInterface, CLI_TYPES type) {
    Config p = Config();

    // todo make paths configurable
    auto pcMap = map<Service, PidCollection>();
    p.parseJson("../configuration/pidConfig.json", pcMap);

    auto dtcMap = map<int, DataTroubleCode>();
    p.parseJson("../configuration/dtcConfig.json", dtcMap);

    obdHandler = make_unique<OBDHandler>(
            make_unique<map<Service, PidCollection>>(pcMap),
            dtcMap);

    auto *can = new CanIsoTP();
    int retVal;
    if (type == TESTER) {
        retVal = can->openIsoTp(TESTER_ID, VEHICLE_ID, canInterface);
    } else {
        retVal = can->openIsoTp(VEHICLE_ID, TESTER_ID, canInterface);
    }
    if (retVal != 0) {
        LOG(ERROR) << "Failed to open interface " << canInterface;
        return false;
    }

    configureVirtualVehicle(obdHandler->getVehicle());
    LOG(INFO) << "Started ECU simulation";

    open = true;

    tCanHandler = thread(&CommandHandler::canHandler, this, can);
    tCmdHandler = thread(&CommandHandler::cmdHandler, this);


    return true;

}

void CommandHandler::stopECUSimulation() {
    if (!open) {
        return;
    }

    exitRequested = true;

    cout << "Press any key to exit ..." << endl;

    tCanHandler.join();
    tCmdHandler.join();
    open = false;
    LOG(DEBUG) << "Cleanup done";
}


void CommandHandler::configureVirtualVehicle(Vehicle *vehicle) {
    for (auto &cmd: commandMapping) {
        vehicle->getPidSupport().setPidSupported(cmd.second, true);
    }
}

void CommandHandler::canHandler(CanIsoTP *can) {
    int bufSize = 255;
    byte *buf = (byte *) malloc(bufSize);
    byte *answer;
    int readSize = 0;

    while (!exitRequested) {
        can->receive(buf, bufSize, readSize);
        if (readSize > 0) {
            answer = obdHandler->createAnswerFrame(buf, readSize);
            can->send(answer, readSize);
        }
    }
}

void CommandHandler::cmdHandler() {
    //string input;
    char input[256];
    while (!exitRequested) {
        cout << ">>" << std::flush;
        std::cin.getline(input, 256);

        std::istringstream iss(input);
        std::vector<std::string> cmd(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());

        if (cmd.empty()) {
            continue;
        }

        if (std::find(commands.begin(), commands.end(), cmd.at(0)) == commands.end()) {
            cout << "Command " << input << " is invalid\n";
            cout << "Type 'help' to get more information" << endl;
            continue;
        }

        if (cmd.at(0) == command_help) {
            printHelp(cmd);
        } else if (cmd.at(0) == command_get) {
            getData(cmd);
        } else if (cmd.at(0) == command_set) {
            setData(cmd);
        }


    }
}

bool CommandHandler::isOpen() {
    return open;
}

void CommandHandler::printHelp(vector<string> &cmd) {
    if (cmd.size() == 1) {
        cout << "Usage cmd system [value]\n";
        cout << "Type 'help cmd' or 'help system' to get more information." << endl;
        return;
    }

    if (cmd.at(1) == command_cmd) {
        cout << "Type 'help name_of_command\n";
        cout << "Available commands: \n";
        for (const auto &cmdName : commands) {
            cout << cmdName << " ";
        }
        cout << endl;
    } else if (cmd.at(1) == command_pid) {
        for (const auto &cmdName : commandMapping) {
            cout << cmdName.first << " ";
        }
        cout << endl;
    } else {
        cout << err_invalid_input << endl;
    }
}

int CommandHandler::getPid(std::vector<std::string> &cmd) {
    int pidId = -1;

    if (cmd.size() == 1) {
        cout << "No system given. See help for more details" << endl;
        return pidId;
    }

    for (const auto &cmdName : commandMapping) {
        if (cmd.at(1) == cmdName.first) {
            pidId = cmdName.second;
        }
    }

    if (-1 == pidId) {
        cout << "Pid " << cmd.at(1) << " is invalid." << endl;
    }

    return pidId;
}

void CommandHandler::getData(std::vector<std::string> &cmd) {
    int pidId = getPid(cmd);
    if (pidId < 0) {
        return;
    }

    // todo find a way to support other services.
    const int serviceId = 1;
    Service service;
    Pid pid;
    if (obdHandler->getFrameInfo(pidId, serviceId, pid, service) < 0) {
        cout << "Failed to retrieve info" << endl;
        return;
    }

    cout << pid.getFrameObject(obdHandler->getVehicle()).getPrintableData() << endl;
}

void CommandHandler::setData(std::vector<std::string> &cmd) {
    int pidId = getPid(cmd);
    if (pidId < 0) {
        return;
    }

    // todo find a way to support other services.
    const int serviceId = 1;
    Service service;
    Pid pid;
    if (obdHandler->getFrameInfo(pidId, serviceId, pid, service) < 0) {
        cout << "Failed to retrieve info" << endl;
        return;
    }

    if (cmd.size() < 3) {
        cout << "Give at least 1 value" << endl;
    }

    int i;
    string val;
    for (i = 2; i < cmd.size(); i++) {
        val += cmd.at(i);
    }

    pid.getFrameObject(obdHandler->getVehicle()).setValueFromString(val);
    cout << pid.getFrameObject(obdHandler->getVehicle()).getPrintableData() << endl;
}

