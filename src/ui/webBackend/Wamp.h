//
// Created by me on 27/01/19.
//

#ifndef OPEN_OBD2_WAMP_H
#define OPEN_OBD2_WAMP_H

#include "wampcc/wampcc.h"
#include "../../communication/ICloseable.h"

class Wamp : public ICloseable {
public:
    inline static const std::string REALM = "openobd";

//public:


public: // Implements ICloseable
    int closeInterface() override;

    int openInterface() override;

private:

    void foo();
};


#endif //OPEN_OBD2_WAMP_H
