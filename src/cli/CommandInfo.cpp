//
// Created by me on 05/01/19.
//

#include "CommandInfo.h"

CommandInfo::CommandInfo(Service service, int pidId) {
    this->service = service;
    this->pidId = pidId;
}

Service CommandInfo::getService() const {
    return service;
}

int CommandInfo::getPidId() const {
    return pidId;
}

