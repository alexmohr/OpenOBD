//
// Created by me on 27/01/19.
//

#ifndef OPEN_OBD2_WAMP_H
#define OPEN_OBD2_WAMP_H

#include "wampcc/wampcc.h"


class Wamp {
private:
    void foo();

public:
    inline static const std::string REALM = "openobd";
};


#endif //OPEN_OBD2_WAMP_H
