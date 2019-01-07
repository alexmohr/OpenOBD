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
    open = false;
    this->type = type;
}

bool CommandHandler::start() {
    if (open) {
        return false;
    }

    LOG(INFO) << "Starting CLI";
    exitRequested = false;
    initDone = false;

    if (com->openInterface() != 0) {
        return false;
    }

    open = true;
    tCmdHandler = thread(&CommandHandler::cmdHandler, this);

    if (type != ELM) {
        tCanHandler = thread(&CommandHandler::comHandler, this, com);
    }

    if (type == ECU) {
        configureVirtualVehicle(obdHandler->getVehicle());
    } else {
        // run in background to give user to chance to abort if
        // the requests to the vehicle time out.
        tInit = thread(&CommandHandler::configureVehicle, this);
    }

    return true;
}

void CommandHandler::stopHandler() {
    if (!open) {
        return;
    }

    exitRequested = true;

    LOG(DEBUG) << "Closing command handler";
    if (type != ELM) {
        tCanHandler.join();
    }

    if (type != ECU) {
        tInit.join();
    }

    tCmdHandler.join();
    com->closeInterface();
    open = false;
    LOG(DEBUG) << "Closed command handler";
}


void CommandHandler::configureVirtualVehicle(Vehicle *vehicle) {
    for (auto &cmd: commandMapping) {
        vehicle->getPidSupport().setPidSupported(cmd.second.getPidId(), true);
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
    int rt = 0;
    for (const auto &id: pidIds) {
        Pid pid;
        if (obdHandler->getServiceAndPidInfo(id, service, pid, service) < 0) {
            LOG(ERROR) << "failed to get pid information";
        }

        rt += queryECU(pid, service);

        if (exitRequested) {
            return;
        }
    }

    if (0 == rt) {
        LOG(INFO) << "Successfully configured vehicle.";
    } else {
        LOG(INFO) << "Could not read all data from vehicle. Available commands may be incomplete.";
    }

    cout << ">>" << flush;
    initDone = true;
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

void CommandHandler::cmdHandler() {
    std::string input;
    cout << ">>" << std::flush;
    while (!exitRequested) {
        struct pollfd pfd = {STDIN_FILENO, POLLIN, 0};

        int ret = 0;
        ret = poll(&pfd, 1, 500);  // timeout of 500ms
        if (ret == 1) // there is something to read
        {
            std::getline(std::cin, input);
        } else if (ret == -1) {
            LOG(ERROR) << "Error: " << strerror(errno) << std::endl;
        } else {
            continue;
        }

        std::vector<std::string> cmd = splitString(const_cast<char *>(input.c_str()));
        if (cmd.empty()) {
            cout << ">>" << std::flush;
            continue;
        }

        if (std::find(commands.begin(), commands.end(), cmd.at(0)) == commands.end()) {
            cout << "Command " << input << " is invalid\n";
            cout << "Type 'help' to get more information" << endl;
            cout << ">>" << std::flush;
            continue;
        }

        if (cmd.at(0) == command_help) {
            printHelp(cmd);
        } else if (cmd.at(0) == command_get) {
            getData(cmd);
        } else if (cmd.at(0) == command_set) {
            setData(cmd);
        }

        cout << ">>" << std::flush;
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
        Service service = Service::POWERTRAIN;
        Pid pid;
        cout << "Supported Pids for service " << service << ":\n";
        for (const auto &cmdName : commandMapping) {
            if (obdHandler->getServiceAndPidInfo(
                    cmdName.second.getPidId(), cmdName.second.getService(), pid, service) != 0) {

                LOG(FATAL) << "Pid with ID " << pid.id << "does only exist in cmdHandler";
                continue;
            }

            if (obdHandler->getVehicle()->getPidSupport().getPidSupported(pid.id)) {
                cout << cmdName.first << " ";
            }
        }
        cout << endl;
    } else {
        cout << err_invalid_input << endl;
    }
}

bool CommandHandler::getPid(std::vector<std::string> &cmd, Pid &pid, Service &service) {
    if (cmd.size() == 1) {
        cout << "No system given. See help for more details" << endl;
        return false;
    }

    const CommandInfo *info = nullptr;
    for (const auto &cmdName : commandMapping) {
        if (cmd.at(1) == cmdName.first) {
            info = &cmdName.second;
        }
    }

    if (nullptr == info) {
        cout << "Pid " << cmd.at(1) << " is invalid." << endl;
        return false;
    }

    service = info->getService();
    if (obdHandler->getServiceAndPidInfo(info->getPidId(), service, pid, service) < 0) {
        cout << "Failed to retrieve info" << endl;
        return false;
    }

    return true;
}

int CommandHandler::getData(std::vector<std::string> &cmd) {
    Service service;
    Pid pid;
    int i = 0;
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

DataObjectState CommandHandler::setData(std::vector<std::string> &cmd) {
    if (ELM == type) {
        cout << "ELM does not support setting values" << endl;
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
    if (!getPid(cmd, pid, service)) {
        return DataObjectState(DATA_ERROR);
    }

    // Try to update vehicle from data.
    auto &frameObject = pid.getFrameObject(obdHandler->getVehicle());
    DataObjectStateCollection sc = frameObject.setValueFromString(val);
    if (!sc.msg.empty()) {
        cout << sc.msg;
    }
    for (const auto &state : sc.resultSet) {
        switch (state.type) {
            case TOO_LARGE:
                cout << "Value " << state.value << " is too large, max value: " << state.max << endl;;
                return state;
            case TOO_SMALL:
                cout << "Value " << state.value << " is too small, min value: " << state.min << endl;
                return state;
            case MISSING_ARGUMENTS:
                cout << "Argument count mismatch. Count: " << state.count << ", Expected: " << state.expectedCount
                     << endl;;
                return state;
            case INVALID_NUMBER:
                cout << "Input is not a valid number" << endl;
                return state;
            case NOT_SUPPORTED:
                cout << "Not supported pid";
                return state;
            case DATA_ERROR:
                cout << "Error while parsing data";
                return state;
            default:
                break;
        }
    }


    i = 0;
    byte *data = pid.getVehicleData(service, obdHandler->getVehicle(), i);
    data = obdHandler->createAnswerFrame(service, pid, data, i);
    i = com->send(data, i);

    delete data;

    cout << "New value: " << frameObject.getPrintableData() << endl;
    return DataObjectState(SUCCESS);
}

// Queries the vehicle and updates internal stored object
int CommandHandler::queryECU(Pid pid, Service service) {
    const int maxTries = 3;
    int tries = 0;
    int frameLen = 0;
    int retVal = 0;
    auto timeout = 500ms;
    const string timeoutWarning = "Failed to retrieve pid " + to_string(pid.id)
                                  + " in service " + to_string(service) + " in " + to_string(maxTries) + " tries";

    byte *frame = pid.getQueryForService(service, frameLen);

    if (type == TESTER) {
        cv_status result;
        // try 3 times to receive the data. Give ecu 500ms each.
        do {
            com->send(frame, frameLen);

            // wait until answer is received.
            expectedPid = pid.id;
            std::unique_lock<std::mutex> lk(dataMutex);
            result = dataCv.wait_for(lk, timeout);
        } while (result != cv_status::no_timeout && tries++ < maxTries);

        if (cv_status::timeout == result) {
            LOG(WARNING) << timeoutWarning;
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

            bool hasTimeout = false;
            auto t0 = chrono::high_resolution_clock::now();
            while (readSize <= 0 && !hasTimeout) {
                com->receive(buf, buflen, readSize);
                hasTimeout = (chrono::high_resolution_clock::now() - t0) > timeout;
            }

            if (hasTimeout) {
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
            LOG(WARNING) << timeoutWarning;
            retVal = 1;
        }

        delete buf;
    }

    delete frame;
    return retVal;
}

OBDHandler &CommandHandler::getObdHandler() {
    return *obdHandler;
}

bool CommandHandler::isInitDone() {
    return initDone;
}

