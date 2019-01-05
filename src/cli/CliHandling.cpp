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

    CLI_TYPE type;

    if (getCommandLineArgs(argc, argv, *target, port, type) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    switch (type) {
        case ELM:
            commHandler = make_unique<ELM327>(port, target);
            break;
        case TESTER:
            commHandler = make_unique<CanIsoTP>(VEHICLE_ID, TESTER_ID, target);
            break;
        case ECU:
            commHandler = make_unique<CanIsoTP>(TESTER_ID, VEHICLE_ID, target);
            break;
        default:
            LOG(ERROR) << "Unsupported interface type";
            return EXIT_FAILURE;

    }

    cmdHandler = make_unique<CommandHandler>(type, commHandler.get());
    cmdHandler->start();

    return EXIT_SUCCESS;
}

void CliHandling::closeCli() {
    cmdHandler->stopHandler();
}

void CliHandling::display_help(char *progname) {
    fprintf(stderr, "Usage: %s <options>\n", progname);
    fprintf(stderr, "Options:\n"
                    "  -h                 Display this help and exit.\n"
                    "  -d CAN_DEVICE      Select the can device which is used. Defaults to can0.\n"
                    "  -t ecu|tester|elm  Define if the software is used as tester or simulates a ECU. Defaults to ecu.\n"
                    "                     Note that tester does not work together with an interface like ELM327\n"
                    "                     ELM does only work with wifi interfaces.\n"
                    "  -i ADDRESS         IP Address of the ELM interface.\n"
                    "  -p PORT IP         PORT of the ELM interface\n."
                    "  -p PORT IP         PORT of the ELM interface\n."
                    "  -x                 Set logging to debug\n."
                    "\n");
}

int CliHandling::getCommandLineArgs(int argc, char **argv, char &interface, int &port,
                                    CLI_TYPE &type) {
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

    bool logdebug = false;

    int c;
    while ((c = getopt(argc, argv, "d:t:i:p:x")) != -1) {
        switch (c) {
            case 'x':
                logdebug = true;
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

    Config::configureLogging(logdebug, false);

    return EXIT_SUCCESS;
}

bool CliHandling::isOpen() {
    return cmdHandler->isOpen();
}

