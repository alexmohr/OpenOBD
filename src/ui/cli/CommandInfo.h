//
// Created by me on 05/01/19.
//

#ifndef OPEN_OBD2_COMMANDINFO_H
#define OPEN_OBD2_COMMANDINFO_H


#include "../../OBD/Service.h"

class CommandInfo {

private:
    Service service;
    int pidId;
public:
    CommandInfo(Service service, int pidId);

public:
    Service getService() const;

    int getPidId() const;

};


#endif //OPEN_OBD2_COMMANDINFO_H
