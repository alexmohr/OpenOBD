#include <utility>

//
// Created by me on 22/01/19.
//

#ifndef OPEN_OBD2_ELM327_H
#define OPEN_OBD2_ELM327_H

#include <string>
#include <map>

using namespace std;


const string ELM_CONFIG_PREFIX = "AT";
const string ELM_CONFIG_SPACES = ELM_CONFIG_PREFIX + "S";
const string ELM_CONFIG_HEADER = ELM_CONFIG_PREFIX + "H";
const string ELM_CONFIG_ECHO = ELM_CONFIG_PREFIX + "E";
const string ELM_CONFIG_PROTOCOL = ELM_CONFIG_PREFIX + "SP";

const string ELM_CONFIG_ENABLE = "1";
const string ELM_CONFIG_DISABLE = "0";

const char ELM_FLOW_PROMPT = '>';
const char ELM_FLOW_NEWLINE = '\r';
const string ELM_FLOW_STOP = "STOP";
const string ELM_FLOW_OK = "OK";
const string ELM_FLOW_ERROR = "ERROR";
const string ELM_FLOW_NEWLINE_PROMPT = "\r>";

const string ELM_HEADER_CAN_11_BIT = "7E8";
const string ELM_HEADER_CAN_29_BIT = "000007E8";
const string ELM_HEADER_SAE = "486B10";

const string ELM_PROTOCOL_TEST_MESSAGE = "0101\r";


string getElmConfigString(const string &option, bool enable);


struct ElmProtocol {
    ElmProtocol(string name, int id, int canIdLength) {
        this->name = std::move(name);
        this->canIdBitLength = canIdLength;
        this->id = id;
    }

    string name;
    int canIdBitLength;
    int id;
};

static inline map<int, ElmProtocol> availableProtocols = {
        {1,  ElmProtocol("SAE_J1850_PWM", 1, 0)},
        {2,  ElmProtocol("SAE_J1850_VPW", 2, 0)},
        {3,  ElmProtocol("ISO_9141_2", 3, 0)},
        {4,  ElmProtocol("ISO_14230_4_5baud", 4, 0)},
        {5,  ElmProtocol("ISO_14230_4_fast", 5, 0)},
        {6,  ElmProtocol("ISO_15765_4_11bit_500k", 6, 11)},
        {7,  ElmProtocol("ISO_15765_4_29bit_500k", 7, 29)},
        {8,  ElmProtocol("ISO_15765_4_11bit_250k", 8, 11)},
        {9,  ElmProtocol("ISO_15765_4_29bit_250k", 9, 29)},
        {10, ElmProtocol("SAE_J1939", 10, 11)}
};


#endif //OPEN_OBD2_ELM327_H
