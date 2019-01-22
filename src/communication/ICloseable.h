//
// Created by me on 22/01/19.
//

#ifndef OPEN_OBD2_ICLOSEABLE_H
#define OPEN_OBD2_ICLOSEABLE_H

class ICloseable {
public:
    virtual int closeInterface() = 0;

    virtual int openInterface() = 0;
};


#endif //OPEN_OBD2_ICLOSEABLE_H
