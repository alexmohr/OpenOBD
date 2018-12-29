//
// Created by me on 29/12/18.
//

#ifndef OPEN_OBD2_UNIT_H
#define OPEN_OBD2_UNIT_H

#include <string>

using namespace std;

class DataObjectDescription {
private:
    string unit;
    string description;
public:
    DataObjectDescription(string unit, string description);

    string getUnit();

    string getDescription();
};


#endif //OPEN_OBD2_UNIT_H
