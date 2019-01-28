//
// Created by me on 02/01/19.
//

#include "CliHandler.h"
#include "easylogging++.h"
#include <chrono>         // std::chrono::seconds


CliHandler::CliHandler() {
}


int CliHandler::openCli(int argc, char *argv[]) {

    int targetSize = 1024;
    char *interface = new char[targetSize];
    memset(interface, 0, targetSize);

    char *script = new char[targetSize];
    memset(script, 0, targetSize);

    int port = 0;
    bool enableElm = false;

    CLI_TYPE type;

    if (getCommandLineArgs(argc, argv, *interface, port, type, enableElm, *script) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    switch (type) {
        case WIFI_ELM:
            if (0 == port) { port = wifiDefaultPort; }
            physicalComInterface = make_unique<SocketClient>(port, interface);
            logicalComInterface = make_unique<ELMClient>(physicalComInterface.get());
            break;
        case SERIAL_ELM:
            physicalComInterface = make_unique<SerialClient>(port, interface);
            logicalComInterface = make_unique<ELMClient>(physicalComInterface.get());
            break;
        case TESTER:
            logicalComInterface = make_unique<CanIsoTP>(VEHICLE_ID, TESTER_ID, interface);
            break;
        case ECU:
            logicalComInterface = make_unique<CanIsoTP>(TESTER_ID, VEHICLE_ID, interface);
            break;
        default:
            LOG(ERROR) << "Unsupported interface type";
            return EXIT_FAILURE;
    }

    if (enableElm) {
        if (nullptr == logicalComInterface) {
            LOG(ERROR) << "Selected type does not support ELM server";
            return EXIT_FAILURE;
        }

        socketServer = make_unique<SocketServer>(port);
        elmServer = make_unique<ELM327WifiServer>(
                port, logicalComInterface.get(), socketServer.get());
        if (elmServer->openInterface() != EXIT_SUCCESS) {
            return EXIT_FAILURE;
        }
    }

    cmdHandler = make_unique<CommandHandler>(type, logicalComInterface.get());
    delete[] interface;
    int val = cmdHandler->start();
    if (script[0] != 0) {
        cmdHandler->executeFile(string(script));
    }

    return val;
}

void CliHandler::closeCli() {
    if (logicalComInterface != nullptr) {
        logicalComInterface->closeInterface();
    }
    if (physicalComInterface != nullptr) {
        physicalComInterface->closeInterface();
    }
    if (cmdHandler != nullptr) {
        cmdHandler->stopHandler();
    }
    if (elmServer != nullptr) {
        elmServer->closeInterface();
    }
    if (socketServer != nullptr) {
        socketServer->closeInterface();
    }
}

void CliHandler::display_help(char *progname) {
    fprintf(stderr, "Usage: %s <options>\n", progname);
    fprintf(stderr, "Options:\n"
                    "  -h                              Display this help and exit.\n"
                    "  -d CAN_DEVICE                   Select the can device which is used. Defaults to can0.\n"
                    "  -t ecu|tester|welm|selm         Define if the software is used as tester or simulates a ECU. Defaults to ecu.\n"
                    "                                  ecu: Simulates an ecu on the can interface given\n"
                    "                                  tester: Tester on the given can interface\n"
                    "                                  welm: Wifi Elm Interface.\n"
                    "                                  selm: Serial Elm Interface.\n"
                    "                                  Note that tester does not work together with an elm interface\n"
                    "  -i ADDRESS                      IP Address or tty device of the ELM interface.\n"
                    "  -p PORT                         PORT or baudrate of the ELM interface, set baudrate to 0 for auto baud.\n."
                    "  -x                              Set logging to debug\n."
                    "  -e                              Enable elm server\n."
                    "  -r                              Run a script directly before showing console.\n"
                    "\n");
}

int
CliHandler::getCommandLineArgs(int argc, char **argv, char &interface, int &port, CLI_TYPE &type, bool &enableElm,
                               char &script) {
    char *typeTester = const_cast<char *>("tester");
    char *typeEcu = const_cast<char *>("ecu");
    char *typeWElm = const_cast<char *>("welm");
    char *typeSElm = const_cast<char *>("selm");

    type = ECU;

    bool logDebug = false;

    int c;
    while ((c = getopt(argc, argv, "d:t:i:r:p:xe")) != -1) {
        switch (c) {
            case 'e':
                enableElm = true;
                break;
            case 'x':
                logDebug = true;
                break;
            case 'd':
                strcpy(&interface, optarg);
                break;
            case 't':
                if (strncmp(typeTester, optarg, sizeof(&typeTester)) == 0) {
                    type = TESTER;
                } else if (strncmp(typeEcu, optarg, sizeof(&typeEcu)) == 0) {
                    type = ECU;
                } else if (strncmp(typeWElm, optarg, sizeof(&typeWElm)) == 0) {
                    type = WIFI_ELM;
                } else if (strncmp(typeSElm, optarg, sizeof(&typeSElm)) == 0) {
                    type = SERIAL_ELM;
                } else {
                    fprintf(stderr, "Specified type %s is invalid.\n", optarg);
                    return EXIT_FAILURE;
                }
                break;
            case 'i':
                strcpy(&interface, optarg);
                break;
            case 'p':
                port = static_cast<int>(strtol(optarg, nullptr, 0));
                break;
            case 'r':
                strcpy(&script, optarg);
                break;
            case '?':
            case 'h':
                display_help(argv[0]);
                return EXIT_FAILURE;
            default:
                display_help(argv[0]);
                return EXIT_FAILURE;
        }
    }

    // set defaults if necessary
    if ((&interface)[0] == 0) {
        switch (type) {
            case ECU:
            case TESTER:
                strcpy(&interface, "can0");
                break;
            case WIFI_ELM:
                strcpy(&interface, "192.168.0.10");
                break;
            case SERIAL_ELM:
                strcpy(&interface, "/dev/ttyUSB0");
        }
    }

    Config::configureLogging(logDebug, false);

    return EXIT_SUCCESS;
}

bool CliHandler::isOpen() {
    if (nullptr != cmdHandler) {
        return cmdHandler->isOpen();
    }
    if (nullptr != elmServer) {
        return elmServer->isOpen();
    }
    return false;
}

bool CliHandler::isExitRequested() {
    return cmdHandler->isExitRequested();
}

