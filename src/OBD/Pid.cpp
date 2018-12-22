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
            vehicle->getPidSupport().setPidSupportedFromFrame(Pid01_20, data, size);
            break;
        case SupportedPid21_40:
            vehicle->getPidSupport().setPidSupportedFromFrame(Pid21_40, data, size);
            break;
        case SupportedPid41_60:
            vehicle->getPidSupport().setPidSupportedFromFrame(Pid41_60, data, size);
            break;
        case SupportedPid61_80:
            vehicle->getPidSupport().setPidSupportedFromFrame(Pid61_80, data, size);
            break;
        case SupportedPid81_A0:
            vehicle->getPidSupport().setPidSupportedFromFrame(Pid81_A0, data, size);
            break;
        case SupportedPidA1_C0:
            vehicle->getPidSupport().setPidSupportedFromFrame(PidA1_C0, data, size);
            break;
        case SupportedPidC1_E0:
            vehicle->getPidSupport().setPidSupportedFromFrame(PidC1_E0, data, size);
            break;
        case MonitoringStatus:
            vehicle->getMonitorStatus().fromFrame(data, size);
            break;
        case FreezeDTCPid:
            vehicle->getFreezeDTC().fromFrame(data, size);
            break;
        case FuelSystemStatus:
            vehicle->getFuelSystem1().fromFrame(data, size);
            vehicle->getFuelSystem2().fromFrame(data, size);
            break;
    }
}



byte* Pid::readService1_2(Vehicle *vehicle) {
    unsigned int data = 0;
    auto pid = (Service1Pids) id;
    switch (pid) {
        case SupportedPid01_20:
            data = vehicle->getPidSupport().getPidSupportedRange(Pid01_20, data);
            break;
        case SupportedPid21_40:
            data = vehicle->getPidSupport().getPidSupportedRange(Pid21_40, data);
            break;
        case SupportedPid41_60:
            data = vehicle->getPidSupport().getPidSupportedRange(Pid41_60, data);
            break;
        case SupportedPid61_80:
            data = vehicle->getPidSupport().getPidSupportedRange(Pid61_80, data);
            break;
        case SupportedPid81_A0:
            data = vehicle->getPidSupport().getPidSupportedRange(Pid81_A0, data);
            break;
        case SupportedPidA1_C0:
            data = vehicle->getPidSupport().getPidSupportedRange(PidA1_C0, data);
            break;
        case SupportedPidC1_E0:
            data = vehicle->getPidSupport().getPidSupportedRange(PidC1_E0, data);
            break;
        case MonitoringStatus:
            data = vehicle->getMonitorStatus().toFrame();
            break;
        case FreezeDTCPid:
            data = vehicle->getFreezeDTC().toFrame(data);
            break;
        case FuelSystemStatus:
            data = vehicle->getFuelSystem1().toFrame(data) |
                   vehicle->getFuelSystem2().toFrame(data);
            break;
    }

    byte *retVal = toByteArray(data);
    return retVal;
}



