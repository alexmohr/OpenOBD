//
// Created by me on 14/12/18.
//

#include "Pid.h"


void Pid::updateVehicle(Service service, Vehicle *vehicle, byte *data, int dataSize) {
    switch (service){
        case POWERTRAIN:
        case FREEZE_FRAME:
            writeService1_2(vehicle, data, dataSize);
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

byte *Pid::getVehicleData(Service service, Vehicle *vehicle, int &size) {
    byte* data = nullptr;
    switch (service){
        case POWERTRAIN:
        case FREEZE_FRAME:
            data = readService1_2(vehicle, size);
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

IFrameObject &Pid::getFrameObject(Vehicle *vehicle) {
    auto pid = (Service1Pids) id;
    switch (pid) {
        case FuelSystemStatus:
            return vehicle->getFuelSystemStates();
        case MonitoringStatusSinceDTCsCleared:
            return vehicle->getMonitorStatusSinceDTCsCleared();
        case FreezeDTCPid:
            return vehicle->getFreezeDTC();
        case CalculatedEngineLoad:
            return vehicle->getEngine().getLoad();
        case EngineCoolantTemperature:
            return vehicle->getEngine().getCoolantTemperature();
        case ShortTermFuelTrimBank1:
            return vehicle->getEngine().getShortTermFuelTrimBank1();
        case LongTermFuelTrimBank1:
            return vehicle->getEngine().getLongTermFuelTrimBank1();
        case ShortTermFuelTrimBank2:
            return vehicle->getEngine().getShortTermFuelTrimBank2();
        case LongTermFuelTrimBank2:
            return vehicle->getEngine().getLongTermFuelTrimBank2();
        case FuelPressure:
            return vehicle->getEngine().getFuelPressure();
        case IntakeManifoldAbsolutePressure:
            return vehicle->getEngine().getIntakeManifoldAbsolutePressure();
        case EngineRPM:
            return vehicle->getEngine().getEngineRPM();
        case VehicleSpeed:
            return vehicle->getSpeed();
        case TimingAdvance:
            return vehicle->getEngine().getTimingAdvance();
        case IntakeAirTemperature:
            return vehicle->getEngine().getIntakeAirTemperature();
        case MAFAirFlowRate:
            return vehicle->getEngine().getMAFAirFlowRate();
        case ThrottlePosition:
            return vehicle->getThrottle().getThrottlePosition();
        case CommandedSecondaryAirStatus:
            return vehicle->getCommandedSecondaryAirStatus();
        case OxygenSensorsPresent:
            return vehicle->getOxygenSystem().getBankOxygenSensorsCollection();
        case BankOxygenSensor1:
            return vehicle->getOxygenSystem().getBankOxygenSensor1();
        case BankOxygenSensor2:
            return vehicle->getOxygenSystem().getBankOxygenSensor2();
        case BankOxygenSensor3:
            return vehicle->getOxygenSystem().getBankOxygenSensor3();
        case BankOxygenSensor4:
            return vehicle->getOxygenSystem().getBankOxygenSensor4();
        case BankOxygenSensor5:
            return vehicle->getOxygenSystem().getBankOxygenSensor5();
        case BankOxygenSensor6:
            return vehicle->getOxygenSystem().getBankOxygenSensor6();
        case BankOxygenSensor7:
            return vehicle->getOxygenSystem().getBankOxygenSensor7();
        case BankOxygenSensor8:
            return vehicle->getOxygenSystem().getBankOxygenSensor8();
        case OBDStandardsVehicleConformsTo:
            return vehicle->getOBDCompliance();
        case OxygenSensorsPresent4Banks:
            return vehicle->getOxygenSystem().getBankOxygenSensor4BankCollection();
        case AuxiliaryInputStatus:
            return vehicle->getAuxiliaryInputStatus();
        case RunTimeSinceEngineStart:
            return vehicle->getRunTimeSinceEngineStart();
        case DistanceTraveledWithMilOn:
            return vehicle->getDistanceTraveledWithMilOn();
        case FuelRailPressure:
            return vehicle->getFuelRailPressure();
        case FuelRailGaugePressure:
            return vehicle->getFuelRailGaugePressure();
        case FuelRailOxygenSensor1:
            return vehicle->getOxygenSystem().getFuelRailOxygenSensor1();
        case FuelRailOxygenSensor2:
            return vehicle->getOxygenSystem().getFuelRailOxygenSensor2();
        case FuelRailOxygenSensor3:
            return vehicle->getOxygenSystem().getFuelRailOxygenSensor3();
        case FuelRailOxygenSensor4:
            return vehicle->getOxygenSystem().getFuelRailOxygenSensor4();
        case FuelRailOxygenSensor5:
            return vehicle->getOxygenSystem().getFuelRailOxygenSensor5();
        case FuelRailOxygenSensor6:
            return vehicle->getOxygenSystem().getFuelRailOxygenSensor6();
        case FuelRailOxygenSensor7:
            return vehicle->getOxygenSystem().getFuelRailOxygenSensor7();
        case FuelRailOxygenSensor8:
            return vehicle->getOxygenSystem().getFuelRailOxygenSensor8();
        case CommandedEGR:
            return vehicle->getCommandedEGR();
        case EGRError:
            return vehicle->getEGRError();
        case CommandedEvaporativePurge:
            return vehicle->getCommandedEvaporativePurge();
        case FuelTankLevelInput:
            return vehicle->getFuelTankLevelInput();
        case WarmUpsSinceCodesCleared:
            return vehicle->getWarmUpsSinceCodesCleared();
        case DistanceTraveledSinceCodesCleared:
            return vehicle->getDistanceTraveledSinceCodesCleared();
        case EvaporativePurgeSystemVaporPressure:
            return vehicle->getEvaporativePurgeSystemVaporPressure();
        case AbsoluteBarometricPressure:
            return vehicle->getAbsoluteBarometricPressure();
        case ExtendedRangeOxygenSensor1:
            return vehicle->getOxygenSystem().getExtendedRangeOxygenSensor1();
        case ExtendedRangeOxygenSensor2:
            return vehicle->getOxygenSystem().getExtendedRangeOxygenSensor2();
        case ExtendedRangeOxygenSensor3:
            return vehicle->getOxygenSystem().getExtendedRangeOxygenSensor3();
        case ExtendedRangeOxygenSensor4:
            return vehicle->getOxygenSystem().getExtendedRangeOxygenSensor4();
        case ExtendedRangeOxygenSensor5:
            return vehicle->getOxygenSystem().getExtendedRangeOxygenSensor5();
        case ExtendedRangeOxygenSensor6:
            return vehicle->getOxygenSystem().getExtendedRangeOxygenSensor6();
        case ExtendedRangeOxygenSensor7:
            return vehicle->getOxygenSystem().getExtendedRangeOxygenSensor7();
        case ExtendedRangeOxygenSensor8:
            return vehicle->getOxygenSystem().getExtendedRangeOxygenSensor8();
        case CatalystTemperatureBank1Sensor1:
            return vehicle->getCatalyst().getTemperatureBank1Sensor1();
        case CatalystTemperatureBank2Sensor1:
            return vehicle->getCatalyst().getTemperatureBank2Sensor1();
        case CatalystTemperatureBank1Sensor2:
            return vehicle->getCatalyst().getTemperatureBank1Sensor2();
        case CatalystTemperatureBank2Sensor2:
            return vehicle->getCatalyst().getTemperatureBank2Sensor2();
        case MonitorStatusThisDriveCycle:
            return vehicle->getMonitorStatusThisDriveCycle();
        case ControlModuleVoltage:
            return vehicle->getControlModuleVoltage();
        case AbsoluteLoadValue:
            return vehicle->getAbsoluteLoadValue();
        case FuelAirCommandedEquivalenceRatio:
            return vehicle->getFuelAirCommandedEquivalenceRatio();
        case RelativeThrottlePosition:
            return vehicle->getThrottle().getRelativeThrottlePosition();
        case AmbientAirTemperature:
            return vehicle->getAmbientAirTemperature();

    }

    throw invalid_argument("pid: " + to_string(pid) + " not implemented");
}

void Pid::writeService1_2(Vehicle *vehicle, byte *data, int size) {
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
        default:
            getFrameObject(vehicle).fromFrame(data, size);
    }
}

byte *Pid::readService1_2(Vehicle *vehicle, int &size) {
    unsigned int data = 0;
    auto pid = (Service1Pids) id;
    switch (pid) {
        case SupportedPid01_20:
            data = vehicle->getPidSupport().getPidSupportedRange(Pid01_20, data, size);
            break;
        case SupportedPid21_40:
            data = vehicle->getPidSupport().getPidSupportedRange(Pid21_40, data, size);
            break;
        case SupportedPid41_60:
            data = vehicle->getPidSupport().getPidSupportedRange(Pid41_60, data, size);
            break;
        case SupportedPid61_80:
            data = vehicle->getPidSupport().getPidSupportedRange(Pid61_80, data, size);
            break;
        case SupportedPid81_A0:
            data = vehicle->getPidSupport().getPidSupportedRange(Pid81_A0, data, size);
            break;
        case SupportedPidA1_C0:
            data = vehicle->getPidSupport().getPidSupportedRange(PidA1_C0, data, size);
            break;
        case SupportedPidC1_E0:
            data = vehicle->getPidSupport().getPidSupportedRange(PidC1_E0, data, size);
            break;
        default:
            data = getFrameObject(vehicle).toFrame(data, size);
    }

    size = getBytes(size);
    byte *retVal = uintToByteArray(data);
    return retVal;
}

byte *Pid::getQueryForService(Service service, int& buflen) {
    buflen = 2;
    byte* frame = (byte*)malloc(buflen);
    frame[0] = (byte)service;
    frame[1] = (byte)id;
    return frame;
}




