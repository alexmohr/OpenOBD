//
// Created by me on 21/12/18.
//

#include "PidSupport.h"


PidSupport::PidSupport(){
    pidSupported01_20 = make_unique<vector<DataObject<bool>>>();
    pidSupported21_40 = make_unique<vector<DataObject<bool>>>();
    pidSupported41_60 = make_unique<vector<DataObject<bool>>>();
    pidSupported61_80 = make_unique<vector<DataObject<bool>>>();
    pidSupported81_A0 = make_unique<vector<DataObject<bool>>>();
    pidSupportedA1_C0 = make_unique<vector<DataObject<bool>>>();
    pidSupportedC1_E0 = make_unique<vector<DataObject<bool>>>();

    initPid(*pidSupported01_20);
    initPid(*pidSupported21_40);
    initPid(*pidSupported41_60);
    initPid(*pidSupported61_80);
    initPid(*pidSupported81_A0);
    initPid(*pidSupportedA1_C0);
    initPid(*pidSupportedC1_E0);
}


void PidSupport::initPid(vector<DataObject<bool>> &data) {
    int i;
    for (i = 7; i >= 0; i--) {
        data.emplace_back(D, i);
    }
    for (i = 7; i >= 0; i--) {
        data.emplace_back(C, i);
    }
    for (i = 7; i >= 0; i--) {
        data.emplace_back(B, i);
    }
    for (i = 7; i >= 0; i--) {
        data.emplace_back(A, i);
    }
    for (auto &pid  : data) {
        pid.setValue(false);
    }
}


void PidSupport::setPidSupported(int pid, bool supported) {
    // pid--;
    if (pid >= 0x01 & pid <= 0x20) {
        pidSupported01_20->at(static_cast<unsigned long>(pid - 0x01)).setValue(supported);
    } else if (pid >= 0x21 & pid <= 0x40) {
        pidSupported21_40->at(static_cast<unsigned long>(pid - 0x21)).setValue(supported);
    } else if (pid >= 0x41 & pid <= 0x60) {
        pidSupported41_60->at(static_cast<unsigned long>(pid - 0x41)).setValue(supported);
    } else if (pid >= 0x61 & pid <= 0x80) {
        pidSupported61_80->at(static_cast<unsigned long>(pid - 0x61)).setValue(supported);
    } else if (pid >= 0x81 & pid <= 0xA0) {
        pidSupported81_A0->at(static_cast<unsigned long>(pid - 0x81)).setValue(supported);
    } else if (pid >= 0xA1 & pid <= 0xC0) {
        pidSupportedA1_C0->at(static_cast<unsigned long>(pid - 0xA1)).setValue(supported);
    } else if (pid >= 0xC1 & pid <= 0xE0) {
        pidSupportedC1_E0->at(static_cast<unsigned long>(pid - 0xC1)).setValue(supported);
    }
}

bool PidSupport::getPidSupported(int pid) {

    if (pid >= 0x01 & pid <= 0x20) {
        return pidSupported01_20->at(static_cast<unsigned long>(pid - 0x01)).getValue();
    } else if (pid >= 0x21 & pid <= 0x40) {
        return pidSupported21_40->at(static_cast<unsigned long>(pid - 0x21)).getValue();
    } else if (pid >= 0x41 & pid <= 0x60) {
        return pidSupported41_60->at(static_cast<unsigned long>(pid - 0x41)).getValue();
    } else if (pid >= 0x61 & pid <= 0x80) {
        return pidSupported61_80->at(static_cast<unsigned long>(pid - 0x61)).getValue();
    } else if (pid >= 0x81 & pid <= 0xA0) {
        return pidSupported81_A0->at(static_cast<unsigned long>(pid - 0x81)).getValue();
    } else if (pid >= 0xA1 & pid <= 0xC0) {
        return pidSupportedA1_C0->at(static_cast<unsigned long>(pid - 0xA1)).getValue();
    } else if (pid >= 0xC1 & pid <= 0xE0) {
        return pidSupportedC1_E0->at(static_cast<unsigned long>(pid - 0xC1)).getValue();
    }

    return false;
}


void PidSupport::setPidSupportedFromFrame(PidRange pid, byte *data, int size) {
    switch (pid) {
        case Pid01_20:
            setPids(*pidSupported01_20, data, size);
            break;
        case Pid21_40:
            setPids(*pidSupported21_40, data, size);
            break;
        case Pid41_60:
            setPids(*pidSupported41_60, data, size);
            break;
        case Pid61_80:
            setPids(*pidSupported61_80, data, size);
            break;
        case Pid81_A0:
            setPids(*pidSupported81_A0, data, size);
            break;
        case PidA1_C0:
            setPids(*pidSupportedA1_C0, data, size);
            break;
        case PidC1_E0:
            setPids(*pidSupportedC1_E0, data, size);
            break;
    }
}


unsigned int PidSupport::getPidSupportedRange(PidRange pid, unsigned int &data) {
    switch (pid) {
        case Pid01_20:
            data = getPids(*pidSupported01_20, data);
            break;
        case Pid21_40:
            data = getPids(*pidSupported21_40, data);
            break;
        case Pid41_60:
            data = getPids(*pidSupported41_60, data);
            break;
        case Pid61_80:
            data = getPids(*pidSupported61_80, data);
            break;
        case Pid81_A0:
            data = getPids(*pidSupported81_A0, data);
            break;
        case PidA1_C0:
            data = getPids(*pidSupportedA1_C0, data);
            break;
        case PidC1_E0:
            data = getPids(*pidSupportedC1_E0, data);
            break;
    }

    return swapEndian(data);
}


unsigned int PidSupport::getPids(vector<DataObject<bool>> &pids, unsigned int &data) {
    for (auto pid: pids) {
        data |= pid.toFrame(data);
    }
    return data;
}

void PidSupport::setPids(vector<DataObject<bool>> &pids, byte *data, int size) {
    byte t;
    int end = size - 1;
    int c;
    // reverse data.
    // todo rework logic for pid setting this is very flawed
    for (c = 0; c < size / 2; c++) {
        t = data[c];
        data[c] = data[end];
        data[end] = t;

        end--;
    }

    for (auto &pid: pids) {
        pid.fromFrame(data, size);
    }
}