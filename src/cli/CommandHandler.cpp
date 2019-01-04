//
// Created by me on 02/01/19.
//

#include "CommandHandler.h"

#include <unistd.h>

CommandHandler::CommandHandler() = default;


bool CommandHandler::start(char *target, CLI_TYPE type, int port) {
    Config p = Config();

    this->type = type;

    // todo make paths configurable
    auto pcMap = map<Service, PidCollection>();
    p.parseJson("../configuration/pidConfig.json", pcMap);

    auto dtcMap = map<int, DataTroubleCode>();
    p.parseJson("../configuration/dtcConfig.json", dtcMap);

    obdHandler = make_unique<OBDHandler>(
            make_unique<map<Service, PidCollection>>(pcMap),
            dtcMap);

    configureVirtualVehicle(obdHandler->getVehicle());

    int retVal;
    string st;
    if (type == ELM) {
        auto *elm = new ELM327(port, target);
        retVal = elm->openElm();
        com = elm;
        st = "ELM";
    } else {
        auto *can = new CanIsoTP();
        if (type == TESTER) {
            st = "TESTER";
            retVal = can->openIsoTp(VEHICLE_ID, TESTER_ID, target);
        } else if (type == ECU) {
            st = "ECU";
            retVal = can->openIsoTp(TESTER_ID, VEHICLE_ID, target);
        } else {
            LOG(ERROR) << "Invalid type " << type << " given";
            return false;
        }

        com = can;
    }


    if (retVal != 0) {
        LOG(ERROR) << "Failed to open interface " << target;
        delete com;
        return false;
    }

    LOG(INFO) << "Started " << st;
    open = true;
    tCmdHandler = thread(&CommandHandler::cmdHandler, this, com);

    if (type != ELM) {
        tCanHandler = thread(&CommandHandler::comHandler, this, com);
    }

    return true;
}

void CommandHandler::stopHandler() {
    if (!open) {
        return;
    }

    exitRequested = true;

    cout << "\n\nPress any key to exit ..." << endl;

    tCanHandler.join();
    tCmdHandler.join();
    com->closeHandler();
    delete com;
    open = false;
    LOG(DEBUG) << "Cleanup done";
}


void CommandHandler::configureVirtualVehicle(Vehicle *vehicle) {
    for (auto &cmd: commandMapping) {
        vehicle->getPidSupport().setPidSupported(cmd.second, true);
    }
}

void CommandHandler::comHandler(ComHandler *com) {
    int bufSize = 255;
    byte *buf = (byte *) malloc(bufSize);
    byte *answer;
    int readSize = 0;

    // will not run for ELM
    while (!exitRequested) {
        com->receive(buf, bufSize, readSize);
        if (readSize <= 0) {
            continue;
        }

        // Answer frame
        if ((int) buf[0] >= ANSWER_OFFSET) {
            obdHandler->updateFromFrame(buf, readSize);
            if (expectedPid == -1) {
                continue;
            }

            if ((int) buf[1] == expectedPid) {
                dataCv.notify_one();
            }
        } else {
            if (ECU != type) {
                return;
            }

            answer = obdHandler->createAnswerFrame(buf, readSize);
            if (nullptr != answer) {
                com->send(answer, readSize);
            }
        }

        usleep(100);
        delete buf;
    }
}

void CommandHandler::cmdHandler(ComHandler *com) {
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
            getData(cmd, com);
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
        cout << "Type 'help cmd' or 'help pid' to get more information." << endl;
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

bool CommandHandler::getPid(std::vector<std::string> &cmd, Pid &pid, Service &service) {
    int pidId = -1;
    if (cmd.size() == 1) {
        cout << "No system given. See help for more details" << endl;
        return false;
    }

    for (const auto &cmdName : commandMapping) {
        if (cmd.at(1) == cmdName.first) {
            pidId = cmdName.second;
        }
    }

    if (-1 == pidId) {
        cout << "Pid " << cmd.at(1) << " is invalid." << endl;
        return false;
    }

    // todo find a way to support other services.
    service = POWERTRAIN;

    if (obdHandler->getFrameInfo(pidId, service, pid, service) < 0) {
        cout << "Failed to retrieve info" << endl;
        return false;
    }

    return true;
}

void CommandHandler::getData(std::vector<std::string> &cmd, ComHandler *com) {
    Service service;
    Pid pid;
    if (!getPid(cmd, pid, service)) {
        return;
    }

    // query data from ecu if we are not one
    if (ECU != type) {
        queryECU(pid, service);
    }
    cout << pid.getFrameObject(obdHandler->getVehicle()).getPrintableData() << endl;
}

void CommandHandler::setData(std::vector<std::string> &cmd) {
    if (ELM == type) {
        cout << "ELM does not support setting values" << endl;
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

    Service service;
    Pid pid;
    if (!getPid(cmd, pid, service)) {
        return;
    }

    // update vehicle
    auto &frameObject = pid.getFrameObject(obdHandler->getVehicle());
    frameObject.setValueFromString(val);

    i = 0;
    byte *data = pid.getVehicleData(service, obdHandler->getVehicle(), i);
    data = obdHandler->createAnswerFrame(service, pid, data, i);
    i = com->send(data, i);

    delete data;

    cout << "New value: " << frameObject.getPrintableData() << endl;
}

void CommandHandler::queryECU(Pid pid, Service service) {
    int i = 0;
    int buflen = 0;

    byte *frame = pid.getQueryForService(service, buflen);

    if (type == TESTER) {
        cv_status result;
        const int maxTries = 3;
        // try 3 times to receive the data. Give ecu 200ms each.
        do {
            com->send(frame, buflen);

            // wait until answer is received.
            expectedPid = pid.id;
            std::unique_lock<std::mutex> lk(dataMutex);
            result = dataCv.wait_for(lk, 600ms);
        } while (result != cv_status::no_timeout && i++ < maxTries);

        if (cv_status::timeout == result) {
            LOG(WARNING) << "Received no answer. Tried " << maxTries << " times";
        }

    } else {
        com->send(frame, buflen);

        // make space for answer
        buflen = 255;
        byte *buf = (byte *) malloc(buflen);
        int readSize = 0;

        bool timeout = false;
        auto t0 = chrono::high_resolution_clock::now();
        while (readSize <= 0 && !timeout) {
            com->receive(buf, buflen, readSize);
            timeout = (chrono::high_resolution_clock::now() - t0) > 2000ms;
        }

        if (timeout) {
            LOG(ERROR) << "Did not receive an answer from interface. Try restarting application if the error persists";
            return;
        }

        int rs = readSize + 1;
        byte *nbuf = (byte *) (malloc(rs));
        for (i = 0; i < readSize; i++) {
            nbuf[i + 1] = buf[i];
        }

        nbuf[0] = (byte) (service + ANSWER_OFFSET);
        obdHandler->updateFromFrame(buf, readSize);

        delete buf;
        delete nbuf;
    }

    delete frame;
}