//
// Created by me on 04/02/19.
//

#ifndef OPEN_OBD2_PIDCOLLECTION_H
#define OPEN_OBD2_PIDCOLLECTION_H

#include <vector>
#include "Pid.h"

using namespace std;

class PidCollection {
public:
    vector<int> validForServices;
    map<int, Pid> pidList;

    const vector<Pid> get_pid_list_as_vector() const;

    const vector<string> getPidNames() const;
};


#endif //OPEN_OBD2_PIDCOLLECTION_H
