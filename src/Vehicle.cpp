//
// Created by me on 13/12/18.
//

#include "Vehicle.h"
#include "common/endian.h"


Vehicle::Vehicle(Engine *engine) {
    monitorStatus = new MonitorStatus(engine);

    PIDSupported01_20 = new vector<DataObject<bool>>();
    PIDSupported21_40 = new vector<DataObject<bool>>();
    PIDSupported41_60 = new vector<DataObject<bool>>();
    PIDSupported61_80 = new vector<DataObject<bool>>();
    PIDSupported81_A0 = new vector<DataObject<bool>>();
    PIDSupportedA1_C0 = new vector<DataObject<bool>>();
    PIDSupportedC1_E0 = new vector<DataObject<bool>>();

    initPid(PIDSupported01_20);
    initPid(PIDSupported21_40);
    initPid(PIDSupported41_60);
    initPid(PIDSupported61_80);
    initPid(PIDSupported81_A0);
    initPid(PIDSupportedA1_C0);
    initPid(PIDSupportedC1_E0);
}

Vehicle::~Vehicle() {
    delete monitorStatus;
    delete PIDSupported01_20;
    delete PIDSupported21_40;
    delete PIDSupported41_60;
    delete PIDSupported61_80;
    delete PIDSupported81_A0;
    delete PIDSupportedA1_C0;
}


Vehicle::Vehicle(Vehicle &vehicle) {

}

void Vehicle::initPid(vector<DataObject<bool>> *data) {
    int i;
    for (i = 7; i >= 0; i--) {
        data->push_back(DataObject<bool>(D, (byte) i));
    }
    for (i = 7; i >= 0; i--) {
        data->push_back(DataObject<bool>(C, (byte) i));
    }
    for (i = 7; i >= 0; i--) {
        data->push_back(DataObject<bool>(B, (byte) i));
    }
    for (i = 7; i >= 0; i--) {
        data->push_back(DataObject<bool>(A, (byte) i));
    }
    for (auto &pid  : *data) {
        pid.setValue(false);
    }
}

MonitorStatus *Vehicle::getMonitorStatus() {
    return monitorStatus;
}

void Vehicle::setPidSupported(int pid, bool supported) {
    // pid--;
    if (pid >= 0x01 & pid <= 0x20) {
        PIDSupported01_20->at(static_cast<unsigned long>(pid - 0x01)).setValue(supported);
    } else if (pid >= 0x21 & pid <= 0x40) {
        PIDSupported21_40->at(static_cast<unsigned long>(pid - 0x21)).setValue(supported);
    } else if (pid >= 0x41 & pid <= 0x60) {
        PIDSupported41_60->at(static_cast<unsigned long>(pid - 0x41)).setValue(supported);
    } else if (pid >= 0x61 & pid <= 0x80) {
        PIDSupported61_80->at(static_cast<unsigned long>(pid - 0x61)).setValue(supported);
    } else if (pid >= 0x81 & pid <= 0xA0) {
        PIDSupported81_A0->at(static_cast<unsigned long>(pid - 0x81)).setValue(supported);
    } else if (pid >= 0xA1 & pid <= 0xC0) {
        PIDSupportedA1_C0->at(static_cast<unsigned long>(pid - 0xA1)).setValue(supported);
    } else if (pid >= 0xC1 & pid <= 0xE0) {
        PIDSupportedC1_E0->at(static_cast<unsigned long>(pid - 0xC1)).setValue(supported);
    }
}

bool Vehicle::getPidSupported(int pid) {

    if (pid >= 0x01 & pid <= 0x20) {
        return PIDSupported01_20->at(static_cast<unsigned long>(pid - 0x01)).getValue();
    } else if (pid >= 0x21 & pid <= 0x40) {
        return PIDSupported21_40->at(static_cast<unsigned long>(pid - 0x21)).getValue();
    } else if (pid >= 0x41 & pid <= 0x60) {
        return PIDSupported41_60->at(static_cast<unsigned long>(pid - 0x41)).getValue();
    } else if (pid >= 0x61 & pid <= 0x80) {
        return PIDSupported61_80->at(static_cast<unsigned long>(pid - 0x61)).getValue();
    } else if (pid >= 0x81 & pid <= 0xA0) {
        return PIDSupported81_A0->at(static_cast<unsigned long>(pid - 0x81)).getValue();
    } else if (pid >= 0xA1 & pid <= 0xC0) {
        return PIDSupportedA1_C0->at(static_cast<unsigned long>(pid - 0xA1)).getValue();
    } else if (pid >= 0xC1 & pid <= 0xE0) {
        return PIDSupportedC1_E0->at(static_cast<unsigned long>(pid - 0xC1)).getValue();
    }

    return false;
}


void Vehicle::setPidSupportedFromFrame(PidRange pid, byte *data, int size) {
    switch (pid) {
        case Pid01_20:
            setPids(PIDSupported01_20, data, size);
            break;
        case Pid21_40:
            setPids(PIDSupported21_40, data, size);
            break;
        case Pid41_60:
            setPids(PIDSupported41_60, data, size);
            break;
        case Pid61_80:
            setPids(PIDSupported61_80, data, size);
            break;
        case Pid81_A0:
            setPids(PIDSupported81_A0, data, size);
            break;
        case PidA1_C0:
            setPids(PIDSupportedA1_C0, data, size);
            break;
        case PidC1_E0:
            setPids(PIDSupportedC1_E0, data, size);
            break;
    }
}


unsigned int Vehicle::getPidSupportedRange(PidRange pid, unsigned int &data) {
    switch (pid) {
        case Pid01_20:
            data = getPids(PIDSupported01_20, data);
            break;
        case Pid21_40:
            data = getPids(PIDSupported21_40, data);
            break;
        case Pid41_60:
            data = getPids(PIDSupported41_60, data);
            break;
        case Pid61_80:
            data = getPids(PIDSupported61_80, data);
            break;
        case Pid81_A0:
            data = getPids(PIDSupported81_A0, data);
            break;
        case PidA1_C0:
            data = getPids(PIDSupportedA1_C0, data);
            break;
        case PidC1_E0:
            data = getPids(PIDSupportedC1_E0, data);
            break;
    }

    return swapEndian(data);
}


unsigned int Vehicle::getPids(vector<DataObject<bool>> *pids, unsigned int &data) {
    for (auto pid: *pids) {
        data |= pid.toFrame(data);
    }
    return data;
}

void Vehicle::setPids(vector<DataObject<bool>> *pids, byte *data, int size) {
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

    for (auto &pid: *pids) {
        pid.fromFrame(data, size);
    }
}








