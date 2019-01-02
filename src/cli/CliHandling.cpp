//
// Created by me on 02/01/19.
//

#include "CliHandling.h"
#include <chrono>         // std::chrono::seconds


CliHandling::CliHandling() {
    cmdHandler = make_unique<CommandHandler>();
}


void CliHandling::openCli(CLI_TYPES type, char *canInterface) {
    switch (type) {
        case SIMUALATE_VEHICLE:
            cmdHandler->startECUSimulation(canInterface);
            break;
    }
}


void CliHandling::closeCli() {
    cmdHandler->stopECUSimulation();
}

