//
// Created by me on 02/01/19.
//

#include "CommandHandler.h"

#include <unistd.h>
#include <poll.h>

CommandHandler::CommandHandler(CLI_TYPE type, ICommunicationInterface *interface) {
    Config p = Config();

    // todo make paths configurable
    auto pcMap = map<Service, PidCollection>();
    p.parseJson("../configuration/pidConfig.json", pcMap);

    auto dtcMap = map<int, DataTroubleCode>();
    p.parseJson("../configuration/dtcConfig.json", dtcMap);

    obdHandler = make_unique<OBDHandler>(
            make_unique<map<Service, PidCollection>>(pcMap),
            dtcMap);

    com = interface;
    this->type = type;
}

bool CommandHandler::start() {
    exitRequested = false;
    LOG(INFO) << "Starting command handler";

    if (com->openInterface() != 0) {
        return;
    }
    open = true;
    tCmdHandler = thread(&CommandHandler::cmdHandler, this, com);

    if (type != ELM) {
        tCanHandler = thread(&CommandHandler::comHandler, this, com);
    }

    if (type == ECU) {
        configureVirtualVehicle(obdHandler->getVehicle());
    } else {
        configureVehicle();
    }

    return true;
}

void CommandHandler::stopHandler() {
    if (!open) {
        return;
    }

    exitRequested = true;

    cout << "\n\nPress any key to exit ..." << endl;

    string s = "\r\n";
    write(STDIN_FILENO, s.c_str(), s.size());

    tCanHandler.join();
    tCmdHandler.join();
    com->closeInterface();
    open = false;
    LOG(DEBUG) << "Closed command handler";
}


void CommandHandler::configureVirtualVehicle(Vehicle *vehicle) {
    for (auto &cmd: commandMapping) {
        vehicle->getPidSupport().setPidSupported(cmd.second, true);
    }
}

void CommandHandler::configureVehicle() {
    // query the vehicle which PID's it supports
    vector<Service1Pids> pidIds{
            SupportedPid01_20, SupportedPid21_40, SupportedPid41_60, SupportedPid61_80,
            SupportedPid81_A0, SupportedPidA1_C0, SupportedPidC1_E0,
    };

    auto service = POWERTRAIN;
    for (const auto &id: pidIds) {
        Pid pid;
        if (obdHandler->getFrameInfo(id, service, pid, service) < 0) {
            LOG(ERROR) << "failed to get pid information";
        }

        queryECU(pid, service);

        if (exitRequested) {
            return;
        }
    }
}


void CommandHandler::comHandler(ICommunicationInterface *com) {
    int bufSize = 255;
    byte *buf = (byte *) malloc(bufSize);
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
                continue;
            }

            byte *answer;
            answer = obdHandler->createAnswerFrame(buf, readSize);
            if (nullptr != answer) {
                com->send(answer, readSize);
                delete answer;
            }
        }

        usleep(100);
    }

    delete buf;
}

void CommandHandler::cmdHandler(ICommunicationInterface *com) {
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

int CommandHandler::getData(std::vector<std::string> &cmd) {
    Service service;
    Pid pid;
    int i;
    if (!getPid(cmd, pid, service)) {
        return -1;
    }

    // query data from ecu if we are not one
    if (ECU != type) {
        i = queryECU(pid, service);
    }
    cout << pid.getFrameObject(obdHandler->getVehicle()).getPrintableData() << endl;
    return i;
}

int CommandHandler::setData(std::vector<std::string> &cmd) {
    if (ELM == type) {
        cout << "ELM does not support setting values" << endl;
        return -1;
    }

    if (cmd.size() < 3) {
        cout << "Give at least 1 value" << endl;
    }

    int i;
    string val;
    for (i = 2; i < cmd.size(); i++) {
        val += cmd.at(i) + " ";
    }
    val.pop_back();

    Service service;
    Pid pid;
    if (!getPid(cmd, pid, service)) {
        return -1;
    }

    // Try to update vehicle from data.
    auto &frameObject = pid.getFrameObject(obdHandler->getVehicle());
    i = frameObject.setValueFromString(val);
    if (i != 0) {
        return i;
    }

    i = 0;
    byte *data = pid.getVehicleData(service, obdHandler->getVehicle(), i);
    data = obdHandler->createAnswerFrame(service, pid, data, i);
    i = com->send(data, i);

    delete data;

    cout << "New value: " << frameObject.getPrintableData() << endl;
    return 0;
}

// Queries the vehicle and updates internal stored object
int CommandHandler::queryECU(Pid pid, Service service) {
    const int maxTries = 3;
    int tries = 0;
    int frameLen = 0;
    int retVal = 0;

    byte *frame = pid.getQueryForService(service, frameLen);

    if (type == TESTER) {
        cv_status result;
        // try 3 times to receive the data. Give ecu 500ms each.
        do {
            com->send(frame, frameLen);

            // wait until answer is received.
            expectedPid = pid.id;
            std::unique_lock<std::mutex> lk(dataMutex);
            result = dataCv.wait_for(lk, 500ms);
        } while (result != cv_status::no_timeout && tries++ < maxTries);

        if (cv_status::timeout == result) {
            LOG(WARNING) << "Received no answer. Tried " << maxTries << " times";
            retVal = 1;
        }

    } else {
        // make space for answer
        int buflen = 255;
        byte *buf = (byte *) malloc(buflen);
        int readSize = 0;
        bool success;
        int i;

        do {
            com->send(frame, frameLen);

            bool timeout = false;
            auto t0 = chrono::high_resolution_clock::now();
            while (readSize <= 0 && !timeout) {
                com->receive(buf, buflen, readSize);
                timeout = (chrono::high_resolution_clock::now() - t0) > 2000ms;
            }

            if (timeout) {
                continue;
            }

            int rs = readSize + 1;
            byte *nbuf = (byte *) (malloc(rs));
            for (i = 0; i < readSize; i++) {
                nbuf[i + 1] = buf[i];
            }

            nbuf[0] = (byte) (service + ANSWER_OFFSET);
            obdHandler->updateFromFrame(buf, readSize);
            success = true;
            delete nbuf;
        } while (!success && tries++ < maxTries);

        if (!success) {
            retVal = -1;
        }

        delete buf;
    }

    delete frame;
    return retVal;
}

OBDHandler &CommandHandler::getObdHandler() {
    return *obdHandler;
}


