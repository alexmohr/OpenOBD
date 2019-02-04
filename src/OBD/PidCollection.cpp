//
// Created by me on 04/02/19.
//

#include "PidCollection.h"

const vector<Pid> PidCollection::get_pid_list_as_vector() const {
    auto pid_vector = vector<Pid>();
    for (auto const &pid : pidList) {
        pid_vector.push_back(pid.second);
    }

    return pid_vector;
}

const vector<string> PidCollection::getPidNames() const {
    auto pidNames = vector<string>();
    for (const auto &pid : get_pid_list_as_vector()) {
        pidNames.push_back(pid.name);
    }
    return pidNames;
}
