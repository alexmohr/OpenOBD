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
#include "OBD/PidCollection.h"
#include "OBD/DataTroubleCode.h"

using namespace std;
using json = nlohmann::json;

#define TESTER_ID 0x7DF
#define VEHICLE_ID 0x7E8

enum APP_TYPE {
    ECU,
    TESTER,
    WIFI_ELM,
    SERIAL_ELM
};


void from_json(const json &jsdata, map<Service, PidCollection> &pcmap);

void from_json(const json &jsdata, Pid &pid);

void from_json(const json &jsData, map<int, DataTroubleCode> &dtcMap);


template<typename T>
void copyToVector(const json &jsdata, vector<T> &target);


class Config {
private:
    static inline string configFolder = "../configuration/";
public:
    static inline const string pidConfigName = "pidConfig.json";
    static inline const string dtcConfigName = "dtcConfig.json";

public:
    template<typename T>
    bool parseJson(const string &filename, T &t) {
        // read a JSON file
        json j;
        try {
            std::ifstream fs(filename);
            fs >> j;
            t = j.get<T>();
        } catch (exception &ex) {
            LOG(ERROR) << "Failed to read json " << ex.what();
            return false;
        }

        return true;
    }

    static void configureLogging(bool logdebug, bool toFile);

    static void setConfigFolder(string folder);

    static string getConfigFolder();
};


#endif //OPEN_OBD2_CONFIGPARSER_H
