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
#include "../communication/SocketServer.h"
#include "../communication/SerialClient.h"
#include "easylogging++.h"


class CliHandling {
private:
    unique_ptr<ELM327WifiServer> elmServer;
    unique_ptr<CommandHandler> cmdHandler;
    unique_ptr<ISocketServer> socketServer;
    unique_ptr<ICommunicationInterface> physicalComInterface;
    unique_ptr<ICommunicationInterface> logicalComInterface;

private:
    bool running;
    int wifiDefaultPort = 35000;

public:
    CliHandling();

public:
    int openCli(int argc, char *argv[]);

    void closeCli();

    bool isOpen();

    bool isExitRequested();

private:
    void display_help(char *progname);

    int getCommandLineArgs(int argc, char **argv, char &interface, int &port, CLI_TYPE &type, bool &enableElm);
};


#endif //OPEN_OBD2_CLIHANDLING_H
