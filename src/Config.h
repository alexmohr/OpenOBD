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

using namespace std;
using json = nlohmann::json;

class Pid {
public:
    int id;
    int size;
    string description;
    int datafields;
    vector<float> maxValues;
    vector<float> minValues;
    vector<string> units;
    vector<string> formulas;
};

class PidCollection {
public:
    vector<int> validForServices;
    vector<Pid> pidList;
};


enum Service {
    POWERTRAIN = 0x01,
    FREEZE_FRAME = 0x02,
    CONFIRMED_DTCS = 0x03,
    CLEAR_DTCS = 0x04,
    OXYGEN_SENSOR = 0x05,
    ONBOARD_MONITORING_TESTS = 0x06,
    EMISSION_RELATED_DTC = 0x07,
    ENABLE_OFF_BOARD_DIAGNOSIS = 0x08,
    VEHICLE_INFORMATION = 0x09,
    EMISSION_RELATED_PERMANENT_DTC = 0x0a

};

enum ids {
    tester = 0x7DF,
    vehicle = 0x7DF
};



void from_json(const json& jsdata, map<Service, PidCollection>& pcmap);
void from_json(const json& jsdata, Pid& pid);

template <typename T>
void copyFromVector(const json& jsdata, vector<T> &target);



class Config {
public:
    template<typename T>
    bool parseJson(string filename, T& t) {
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
