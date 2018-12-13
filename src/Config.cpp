//
// Created by me on 12/12/18.
//


#include "Config.h"

using namespace std;



template <typename T>
void copyFromVector(const json& jsData, vector<T> &target){
    target.resize(jsData.size());
    std::copy(jsData.begin(), jsData.end(), target.begin());

}

void from_json(const json& jsData, map<Service, PidCollection>& pcmap) {
    int i,j;


    for (i = 0; i < jsData.size(); i++){
        const auto jsonPC = jsData[i];
        const vector<int> services = jsonPC .at("validForServices");
        for (auto &serviceId : services){
            PidCollection pc;
            copyFromVector(jsonPC["pidList"], pc.pidList);
            copyFromVector(services, pc.validForServices);

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

    copyFromVector(jsData.at("maxValues"), pid.maxValues);
    copyFromVector(jsData.at("minValues"), pid.minValues);
    copyFromVector(jsData.at("units"), pid.units);
    copyFromVector(jsData.at("formulas"), pid.formulas);
}


