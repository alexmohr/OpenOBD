//
// Created by me on 02/01/19.
//

#include "CommandHandler.h"


CommandHandler::CommandHandler() {

}


void CommandHandler::startECUSimulation(char *canInterface) {
    Config p = Config();

    // todo make paths configurable
    auto pcMap = map<Service, PidCollection>();
    p.parseJson("../configuration/pidConfig.json", pcMap);

    auto dtcMap = map<int, DataTroubleCode>();
    p.parseJson("../configuration/dtcConfig.json", pcMap);

    obdHandler = make_unique<OBDHandler>(
            make_unique<map<Service, PidCollection>>(pcMap),
            dtcMap);


    // configure
    configureVirtualVehicle(obdHandler->getVehicle());

    tCanHandler = thread(&CommandHandler::canHandler, this, canInterface);
    tCmdHandler = thread(&CommandHandler::cmdHandler, this);

    isOpen = true;
}

void CommandHandler::stopECUSimulation() {
    if (!isOpen) {
        return;
    }

    exitRequested = true;
    tCanHandler.join();
    tCmdHandler.join();
}


void CommandHandler::configureVirtualVehicle(Vehicle *vehicle) {
    for (auto &cmd: commandMapping) {
        vehicle->getPidSupport().setPidSupported(cmd.second, true);
    }
}

void CommandHandler::canHandler(char *canInterface) {
    auto *vehicleCAN = new CanIsoTP();
    vehicleCAN->openIsoTp(TESTER_ID, VEHICLE_ID, canInterface);

    byte buf[255];
    byte *answer;
    int readSize = 0;

    while (!exitRequested) {
        vehicleCAN->receive(buf, 255, readSize);
        answer = obdHandler->createAnswerFrame(buf, readSize);
        vehicleCAN->send(answer, readSize);
    }
}

void CommandHandler::cmdHandler() {

}

