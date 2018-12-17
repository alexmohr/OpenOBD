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
    switch (id){
        case 0x00:
            vehicle->PIDSupported01_20 = data;
            break;
        case 0x20:
            vehicle->PIDSupported21_40 = data;
            break;
        case 0x40:
            vehicle->PIDSupported41_60 = data;
            break;
        case 0x60:
            vehicle->PIDSupported61_80 = data;
            break;
        case 0x80:
            vehicle->PIDSupported81_A0 = data;
            break;
        case 0xA0:
            vehicle->PIDSupportedA1_C0 = data;
            break;
        case 0xC0:
            vehicle->PIDSupportedC1_E0 = data;
            break;
        case 0x01:
            vehicle->getMonitorStatus()->fromFrame(data, size);
    }
}



byte* Pid::readService1_2(Vehicle *vehicle) {
    byte* data = nullptr;
    switch (id){
        case 0x00:
            data = vehicle->PIDSupported01_20;
            break;
        case 0x20:
            data = vehicle->PIDSupported21_40;
            break;
        case 0x40:
            data = vehicle->PIDSupported41_60;
            break;
        case 0x60:
            data = vehicle->PIDSupported61_80;
            break;
        case 0x80:
            data = vehicle->PIDSupported81_A0;
            break;
        case 0xA0:
            data = vehicle->PIDSupportedA1_C0;
            break;
        case 0xC0:
            data = vehicle->PIDSupportedC1_E0;
            break;
        case 0x01:
            data = vehicle->getMonitorStatus()->toFrame();

    }

    return data;
}



int Pid::to_int32(byte *data) {
    int result;
    memcpy(&result, data, sizeof(int));
    return result;
}



