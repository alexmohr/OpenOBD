//
// Created by me on 02/01/19.
//

#include "CliHandling.h"
#include "easylogging++.h"
#include <chrono>         // std::chrono::seconds



CliHandling::CliHandling() {
}



int CliHandling::openCli(int argc, char *argv[]) {

    char *target = static_cast<char *>(malloc(255));
    int port = 0;
    bool enableElm = false;

    CLI_TYPE type;

    if (getCommandLineArgs(argc, argv, *target, port, type, enableElm) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    switch (type) {
        case ELM:
            // todo support other interfaces, like serial or blue tooth.
            physicalComInterface = make_unique<SocketClient>(port, target);
            logicalComInterface = make_unique<ELM327WifiClient>(physicalComInterface.get());
            break;
        case TESTER:
            logicalComInterface = make_unique<CanIsoTP>(VEHICLE_ID, TESTER_ID, target);
            break;
        case ECU:
            logicalComInterface = make_unique<CanIsoTP>(TESTER_ID, VEHICLE_ID, target);
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
    return cmdHandler->start();
}

void CliHandling::closeCli() {
    if (logicalComInterface!= nullptr) {
        logicalComInterface->closeInterface();
    }
    if (physicalComInterface != nullptr){
        physicalComInterface->closeInterface();
    }
    if (cmdHandler != nullptr) {
        cmdHandler->stopHandler();
    }
    if (elmServer != nullptr) {
        elmServer->closeInterface();
    }
    if (socketServer != nullptr){
        socketServer->closeInterface();
    }
}

void CliHandling::display_help(char *progname) {
    fprintf(stderr, "Usage: %s <options>\n", progname);
    fprintf(stderr, "Options:\n"
                    "  -h                              Display this help and exit.\n"
                    "  -d CAN_DEVICE                   Select the can device which is used. Defaults to can0.\n"
                    "  -t ecu|tester|elm               Define if the software is used as tester or simulates a ECU. Defaults to ecu.\n"
                    "                                  ecu: Simulates an ecu on the can interface given\n"
                    "                                  tester: Tester on the given can interface\n"
                    "                                  Note that tester does not work together with an elm interface\n"
                    "                                  ELM does only work with wifi interfaces.\n"
                    "  -i ADDRESS                      IP Address of the ELM interface.\n"
                    "  -p PORT IP                      PORT of the ELM interface\n."
                    "  -x                              Set logging to debug\n."
                    "  -e                              Enable elm server\n."
                    "\n");
}

int
CliHandling::getCommandLineArgs(int argc, char **argv, char &interface, int &port, CLI_TYPE &type, bool &enableElm) {
    char *typeTester = const_cast<char *>("tester");
    char *typeEcu = const_cast<char *>("ecu");
    char *typeElm = const_cast<char *>("elm");

    type = ECU;

    char *canAdapter = static_cast<char *>(malloc(255));
    char *elm = static_cast<char *>(malloc(255));
    strcpy(canAdapter, "can0");
    strcpy(&interface, canAdapter);
    strcpy(elm, "192.168.0.10");

    port = 35000;

    bool logDebug = false;

    int c;
    while ((c = getopt(argc, argv, "d:t:i:p:xe")) != -1) {
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
                } else if (strncmp(typeElm, optarg, sizeof(&typeElm)) == 0) {
                    type = ELM;
                    strcpy(&interface, elm);
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
            case '?':
            case 'h':
                display_help(argv[0]);
                return EXIT_FAILURE;
            default:
                display_help(argv[0]);
                return EXIT_FAILURE;
        }
    }

    Config::configureLogging(logDebug,
                             false);

    return EXIT_SUCCESS;
}

bool CliHandling::isOpen() {
    if (nullptr != cmdHandler) {
        return cmdHandler->isOpen();
    }
    if (nullptr != elmServer) {
        return elmServer->isOpen();
    }
    return false;
}

