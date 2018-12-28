//
// Created by me on 12/12/18.
//

#ifndef OPEN_OBD2_CONFIGPARSER_H
#define OPEN_OBD2_CONFIGPARSER_H

#include <string>
#include <vector>
#include <fstream>
#include "json.hpp"
#include "easylogging++.h"
#include "OBD/Pid.h"
#include "OBD/DataTroubleCode.h"

using namespace std;
using json = nlohmann::json;

#define TESTER_ID 0x7DF
#define VEHICLE_ID 0x7E8

class PidCollection {
public:
    vector<int> validForServices;
    map<int, Pid> pidList;
};



void from_json(const json& jsdata, map<Service, PidCollection>& pcmap);
void from_json(const json& jsdata, Pid& pid);

void from_json(const json &jsData, map<int, DataTroubleCode> &dtcMap);


template <typename T>
void copyToVector(const json &jsdata, vector<T> &target);



class Config {
public:
    template<typename T>
    bool parseJson(const string &filename, T &t) {
        // read a JSON file
        std::ifstream fs(filename);
        json j;
        try {
            fs >> j;
            t = j.get<T>();
        } catch (exception &ex){
            LOG(ERROR) << "Failed to read json " << ex.what();
            return false;
        }

        return true;
    }

};



#endif //OPEN_OBD2_CONFIGPARSER_H
