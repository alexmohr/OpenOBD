//
// Created by me on 12/12/18.
//


#include "Config.h"
#include "easylogging++.h"
using namespace std;



template <typename T>
void copyToVector(const json &jsData, vector<T> &target){
    target.resize(jsData.size());
    std::copy(jsData.begin(), jsData.end(), target.begin());
}

void from_json(const json &jsData, map<int, DataTroubleCode> &dtcMap) {
    for (auto const &value: jsData) {
        DataTroubleCode dtc = DataTroubleCode();
        dtc.setSaeId(value.at("saeId"));
        dtc.setDescription(value.at("description"));
        auto it = dtcMap.find(dtc.getCanId());
        if (it == dtcMap.end()) {
            dtcMap.insert(pair<int, DataTroubleCode>(dtc.getCanId(), dtc));
        } else {
            it->second.setDescription(it->second.getDescription() + " OR " + dtc.getDescription());
//            LOG(WARNING) << "DataTroubleCode Configuration contains duplicate can id: "
//                         << dtc.getCanId()
//                         << " Descriptions have been merged";

            // if these are not the same something is realy wrong because the calculation
            // of the can creates collisions.
            assert (it->second.getSaeId() == dtc.getSaeId());
        }
    }
}

void from_json(const json& jsData, map<Service, PidCollection>& pcmap) {
    long unsigned int i;

    for (i = 0; i < jsData.size(); i++){
        const auto jsonPC = jsData[i];
        const vector<int> services = jsonPC .at("validForServices");
        for (auto &serviceId : services){
            PidCollection pc;

            for (auto const &element : jsonPC["pidList"]) {
                pc.pidList.insert(pair<int,Pid>(element["id"], element));
            }

            copyToVector(services, pc.validForServices);

            auto service = static_cast<Service>(serviceId);
            pcmap.insert(pair<Service, PidCollection>(service, pc));
        }
    }
}

void from_json(const json& jsData, Pid& pid) {
    pid.id = jsData.at("id");
    pid.size = jsData.at("size");
    pid.description = jsData.at("description");
    pid.datafields = jsData.at("dataFields");

    copyToVector(jsData.at("maxValues"), pid.maxValues);
    copyToVector(jsData.at("minValues"), pid.minValues);
    copyToVector(jsData.at("units"), pid.units);
}


void Config::configureLogging(bool logdebug, bool toFile) {

    el::Configurations defaultConf;
    defaultConf.setToDefault();

    string val = "true";
    if (!logdebug) {
        val = false;
    }

    defaultConf.set(el::Level::Trace, el::ConfigurationType::Enabled, val);
    defaultConf.set(el::Level::Debug, el::ConfigurationType::Enabled, val);


    if (toFile) {
        defaultConf.set(el::Level::Global, el::ConfigurationType::ToFile, "true");
        defaultConf.set(el::Level::Global, el::ConfigurationType::Filename, "openobd.log");
    } else {
        defaultConf.set(el::Level::Global, el::ConfigurationType::ToFile, "false");
    }

    // default logger uses default configurations
    el::Loggers::reconfigureLogger("default", defaultConf);

}

string Config::findConfigFolder(vector<string> additionalSearchPaths) {
    return std::__cxx11::string();
}