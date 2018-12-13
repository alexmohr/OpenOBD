#include <iostream>
#include <map>
#include "easylogging++.h"
#include "Config.h"


INITIALIZE_EASYLOGGINGPP


int main() {

    Config p = Config();

    auto pcMap = map<Service, PidCollection>();
    p.parseJson("../configuration/pidConfig.json", pcMap);

    return 0;
}