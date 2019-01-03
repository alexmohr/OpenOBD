//
// Created by me on 02/01/19.
//

#include "CliHandling.h"
#include <chrono>         // std::chrono::seconds


CliHandling::CliHandling() {
    cmdHandler = make_unique<CommandHandler>();
}

int CliHandling::openCli(int argc, char *argv[]) {

    char *canAdapter = static_cast<char *>(malloc(255));
    CLI_TYPES type;

    if (getCommandLineArgs(argc, argv, *canAdapter, type) == EXIT_FAILURE) {
        return EXIT_SUCCESS;
    }

    cmdHandler->start(canAdapter, type);

    return EXIT_SUCCESS;
}

void CliHandling::closeCli() {
    cmdHandler->stopECUSimulation();
}

void CliHandling::display_help(char *progname) {
    fprintf(stderr, "Usage: %s <options>\n", progname);
    fprintf(stderr, "Options:\n"
                    "  -h             Display this help and exit.\n"
                    "  -d CAN_DEVICE  Select the can device which is used. Defaults to can0.\n"
                    "  -t ecu|tester  Define if the software is used as tester or simulates a ECU. Defaults to ecu.\n"
                    "\n");
}

int CliHandling::getCommandLineArgs(int argc, char **argv, char &canAdapter, CLI_TYPES &type) {
    char *typeTester = const_cast<char *>("tester");
    char *typeEcu = const_cast<char *>("ecu");

    type = ECU;
    strcpy(&canAdapter, "can0");

    int c;
    while ((c = getopt(argc, argv, "d:t:")) != -1) {
        switch (c) {
            case 'd':
                strcpy(&canAdapter, optarg);
                break;
            case 't':
                if (strncmp(typeTester, optarg, sizeof(&typeTester)) == 0) {
                    type = TESTER;
                } else if (strncmp(typeEcu, optarg, sizeof(&typeEcu)) == 0) {
                    type = ECU;
                } else {
                    fprintf(stderr, "Specified type %s is invalid.\n", optarg);
                    return EXIT_FAILURE;
                }
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

    return EXIT_SUCCESS;
}

bool CliHandling::isOpen() {
    return cmdHandler->isOpen();
}

