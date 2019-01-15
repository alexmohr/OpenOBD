//
// Created by me on 02/01/19.
//

#ifndef OPEN_OBD2_CLIHANDLING_H
#define OPEN_OBD2_CLIHANDLING_H

#include <memory>
#include <thread>
#include <csignal>
#include <unistd.h>
#include "CommandHandler.h"
#include "easylogging++.h"


class CliHandling {
private:
    bool running;
    unique_ptr<ELM327WifiServer> simElm;
    unique_ptr<CommandHandler> cmdHandler;
    unique_ptr<ICommunicationInterface> commHandler;
public:
    CliHandling();
public:
    int openCli(int argc, char *argv[]);
    void closeCli();

    bool isOpen();

private:
    void display_help(char *progname);

    int getCommandLineArgs(int argc, char **argv, char &interface, int &port, CLI_TYPE &type);
};


#endif //OPEN_OBD2_CLIHANDLING_H
