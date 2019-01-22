//
// Created by me on 22/01/19.
//

#include "ELM327.h"

string getElmConfigString(const string &option, bool enable) {
    if (enable) {
        return option + ELM_CONFIG_ENABLE;
    }
    return option + ELM_CONFIG_DISABLE;
}

