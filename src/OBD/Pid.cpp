//
// Created by me on 14/12/18.
//

#include "Pid.h"


void Pid::updateVehicle(Service service, Vehicle *vehicle, byte *data, int dataSize) {
    switch (service){
        case POWERTRAIN:
        case FREEZE_FRAME:
            updateService1_2(vehicle, data, size);
            break;
        case CONFIRMED_DTCS:
            break;
        case CLEAR_DTCS:
            break;
        case OXYGEN_SENSOR:
            break;
        case ONBOARD_MONITORING_TESTS:
            break;
        case EMISSION_RELATED_DTC:
            break;
        case ENABLE_OFF_BOARD_DIAGNOSIS:
            break;
        case VEHICLE_INFORMATION:
            break;
        case EMISSION_RELATED_PERMANENT_DTC:
            break;
    }

}

byte* Pid::getVehicleData(Service service, Vehicle *vehicle) {
    byte* data = nullptr;
    switch (service){
        case POWERTRAIN:
        case FREEZE_FRAME:
            data = readService1_2(vehicle);
            break;
        case CONFIRMED_DTCS:
            break;
        case CLEAR_DTCS:
            break;
        case OXYGEN_SENSOR:
            break;
        case ONBOARD_MONITORING_TESTS:
            break;
        case EMISSION_RELATED_DTC:
            break;
        case ENABLE_OFF_BOARD_DIAGNOSIS:
            break;
        case VEHICLE_INFORMATION:
            break;
        case EMISSION_RELATED_PERMANENT_DTC:
            break;
    }
    return data;
}

void Pid::updateService1_2(Vehicle *vehicle, byte *data, int size) {
    auto pid = (Service1Pids) id;
    switch (pid) {
        case SupportedPid01_20:
            vehicle->setPidSupportedFromFrame(Pid01_20, data, size);
            break;
        case SupportedPid21_40:
            vehicle->setPidSupportedFromFrame(Pid21_40, data, size);
            break;
        case SupportedPid41_60:
            vehicle->setPidSupportedFromFrame(Pid41_60, data, size);
            break;
        case SupportedPid61_80:
            vehicle->setPidSupportedFromFrame(Pid61_80, data, size);
            break;
        case SupportedPid81_A0:
            vehicle->setPidSupportedFromFrame(Pid81_A0, data, size);
            break;
        case SupportedPidA1_C0:
            vehicle->setPidSupportedFromFrame(PidA1_C0, data, size);
            break;
        case SupportedPidC1_E0:
            vehicle->setPidSupportedFromFrame(PidC1_E0, data, size);
            break;
        case MonitoringStatus:
            vehicle->getMonitorStatus()->fromFrame(data, size);
            break;
    }
}



byte* Pid::readService1_2(Vehicle *vehicle) {
    unsigned int data = 0;
    auto pid = (Service1Pids) id;
    switch (pid) {
        case SupportedPid01_20:
            data = vehicle->getPidSupportedRange(Pid01_20, data);
            break;
        case SupportedPid21_40:
            data = vehicle->getPidSupportedRange(Pid21_40, data);
            break;
        case SupportedPid41_60:
            data = vehicle->getPidSupportedRange(Pid41_60, data);
            break;
        case SupportedPid61_80:
            data = vehicle->getPidSupportedRange(Pid61_80, data);
            break;
        case SupportedPid81_A0:
            data = vehicle->getPidSupportedRange(Pid81_A0, data);
            break;
        case SupportedPidA1_C0:
            data = vehicle->getPidSupportedRange(PidA1_C0, data);
            break;
        case SupportedPidC1_E0:
            data = vehicle->getPidSupportedRange(PidC1_E0, data);
            break;
        case MonitoringStatus:
            data = vehicle->getMonitorStatus()->toFrame();
    }

    byte *retVal = new byte[4];
    retVal[0] = (byte) (data & 0xFF);
    retVal[1] = (byte) ((data >> 8) & 0xFF);
    retVal[2] = (byte) ((data >> 16) & 0xFF);
    retVal[3] = (byte) ((data >> 24) & 0xFF);
    return retVal;
}




