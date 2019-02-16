//
// Created by me on 21/12/18.
//

#include "PidSupport.h"


PidSupport::PidSupport() {
    pidSupported01_20 = make_unique<SupportedPidCollection>(1);
    pidSupported21_40 = make_unique<SupportedPidCollection>(33);
    pidSupported41_60 = make_unique<SupportedPidCollection>(65);
    pidSupported61_80 = make_unique<SupportedPidCollection>(97);
    pidSupported81_A0 = make_unique<SupportedPidCollection>(129);
    pidSupportedA1_C0 = make_unique<SupportedPidCollection>(161);
    pidSupportedC1_E0 = make_unique<SupportedPidCollection>(193);
}

void PidSupport::setPidSupported(Service service, int pid, bool supported) {
    switch (service) {
        case POWERTRAIN:
        case FREEZE_FRAME:
            if ((pid >= 0x01) & (pid <= 0x20)) {
                pidSupported01_20->getSupportedPids().at(static_cast<unsigned long>(pid - 0x01)).setValue(supported);
            } else if ((pid >= 0x21) & (pid <= 0x40)) {
                pidSupported21_40->getSupportedPids().at(static_cast<unsigned long>(pid - 0x21)).setValue(supported);
            } else if ((pid >= 0x41) & (pid <= 0x60)) {
                pidSupported41_60->getSupportedPids().at(static_cast<unsigned long>(pid - 0x41)).setValue(supported);
            } else if ((pid >= 0x61) & (pid <= 0x80)) {
                pidSupported61_80->getSupportedPids().at(static_cast<unsigned long>(pid - 0x61)).setValue(supported);
            } else if ((pid >= 0x81) & (pid <= 0xA0)) {
                pidSupported81_A0->getSupportedPids().at(static_cast<unsigned long>(pid - 0x81)).setValue(supported);
            } else if ((pid >= 0xA1) & (pid <= 0xC0)) {
                pidSupportedA1_C0->getSupportedPids().at(static_cast<unsigned long>(pid - 0xA1)).setValue(supported);
            } else if ((pid >= 0xC1) & (pid <= 0xE0)) {
                pidSupportedC1_E0->getSupportedPids().at(static_cast<unsigned long>(pid - 0xC1)).setValue(supported);
            }
            break;
        default:
            break;
    }
}

bool PidSupport::getPidSupported(Service service, int pid) {
    switch (service) {
        case POWERTRAIN:
        case FREEZE_FRAME:

            if (0 == pid) {
                return true;
            }

            if ((pid >= 0x01) & (pid <= 0x20)) {
                return pidSupported01_20->getSupportedPids().at(static_cast<unsigned long>(pid - 0x01)).getValue();
            } else if ((pid >= 0x21) & (pid <= 0x40)) {
                return pidSupported21_40->getSupportedPids().at(static_cast<unsigned long>(pid - 0x21)).getValue();
            } else if ((pid >= 0x41) & (pid <= 0x60)) {
                return pidSupported41_60->getSupportedPids().at(static_cast<unsigned long>(pid - 0x41)).getValue();
            } else if ((pid >= 0x61) & (pid <= 0x80)) {
                return pidSupported61_80->getSupportedPids().at(static_cast<unsigned long>(pid - 0x61)).getValue();
            } else if ((pid >= 0x81) & (pid <= 0xA0)) {
                return pidSupported81_A0->getSupportedPids().at(static_cast<unsigned long>(pid - 0x81)).getValue();
            } else if ((pid >= 0xA1) & (pid <= 0xC0)) {
                return pidSupportedA1_C0->getSupportedPids().at(static_cast<unsigned long>(pid - 0xA1)).getValue();
            } else if ((pid >= 0xC1) & (pid <= 0xE0)) {
                return pidSupportedC1_E0->getSupportedPids().at(static_cast<unsigned long>(pid - 0xC1)).getValue();
            }

        default:
            return false;
    }

    return false;
}

SupportedPidCollection &PidSupport::getCollectionPid01_20() {
    return *pidSupported01_20;
}

SupportedPidCollection &PidSupport::getCollectionPid21_40() {
    return *pidSupported21_40;
}

SupportedPidCollection &PidSupport::getCollectionPid41_60() {
    return *pidSupported41_60;
}

SupportedPidCollection &PidSupport::getCollectionPid61_80() {
    return *pidSupported61_80;
}

SupportedPidCollection &PidSupport::getCollectionPid81_A0() {
    return *pidSupported81_A0;
}

SupportedPidCollection &PidSupport::getCollectionPidA1_C0() {
    return *pidSupportedA1_C0;
}

SupportedPidCollection &PidSupport::getCollectionPidC1_E0() {
    return *pidSupportedC1_E0;
}