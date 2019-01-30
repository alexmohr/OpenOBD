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
#include "../../communication/SocketServer.h"
#include "../../communication/SerialClient.h"
#include "easylogging++.h"


class CliHandler {
private:
    shared_ptr<ELM327WifiServer> elmServer;
    shared_ptr<CommandHandler> cmdHandler;
    shared_ptr<ISocketServer> socketServer;
    shared_ptr<ICommunicationInterface> physicalComInterface;
    shared_ptr<ICommunicationInterface> logicalComInterface;

private:
    bool running;
    int wifiDefaultPort = 35000;

public:
    CliHandler();

public:
    int openCli(int argc, char *argv[]);

    void closeCli();

    bool isOpen();

    bool isExitRequested();

private:
    void display_help(char *progname);

    int getCommandLineArgs(int argc, char **argv, char &interface, int &port, CLI_TYPE &type, bool &enableElm,
                           char &script);
};


#endif //OPEN_OBD2_CLIHANDLING_H
