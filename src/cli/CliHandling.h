//
// Created by me on 02/01/19.
//

#ifndef OPEN_OBD2_CLIHANDLING_H
#define OPEN_OBD2_CLIHANDLING_H

#include <memory>
#include <thread>
#include <csignal>
#include "CommandHandler.h"
#include "easylogging++.h"

enum CLI_TYPES {
    SIMUALATE_VEHICLE
};

class CliHandling {
private:
private:
    bool running;
    unique_ptr<CommandHandler> cmdHandler;
public:
    CliHandling();

public:
    void openCli(CLI_TYPES type, char *canInterface);

    void closeCli();

private:

};


#endif //OPEN_OBD2_CLIHANDLING_H
