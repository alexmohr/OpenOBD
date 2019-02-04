//
// Created by me on 14/12/18.
//

#include "Pid.h"


void Pid::updateVehicle(Service service, Vehicle *vehicle, byte *data, int dataSize) {
    switch (service) {
        case POWERTRAIN:
        case FREEZE_FRAME:
            writeService1_2(vehicle, data, dataSize);
            break;
            /*    case CONFIRMED_DTCS:
                    break;
                case CLEAR_DTCS:
                    break;
                case OXYGEN_SENSOR:
                    break;*/
            /*   case VEHICLE_INFORMATION:
                   break;*/

    }

}

byte *Pid::getVehicleData(Service service, Vehicle *vehicle, int &size) {
    byte *data = nullptr;
    switch (service) {
        case POWERTRAIN:
        case FREEZE_FRAME:
            data = readService1_2(vehicle, size);
            break;
/*        case CONFIRMED_DTCS:
            break;
        case CLEAR_DTCS:
            break;
        case OXYGEN_SENSOR:
            break;
        case VEHICLE_INFORMATION:
            break;*/
    }
    return data;
}

IFrameObject *Pid::getFrameObject(Vehicle *vehicle) {
    auto pid = (Service1Pids) id;
    switch (pid) {
        case SupportedPid01_20:
            return &vehicle->getPidSupport().getCollectionPid01_20();
        case SupportedPid21_40:
            return &vehicle->getPidSupport().getCollectionPid21_40();
        case SupportedPid41_60:
            return &vehicle->getPidSupport().getCollectionPid41_60();
        case SupportedPid61_80:
            return &vehicle->getPidSupport().getCollectionPid61_80();
        case SupportedPid81_A0:
            return &vehicle->getPidSupport().getCollectionPid81_A0();
        case SupportedPidA1_C0:
            return &vehicle->getPidSupport().getCollectionPidA1_C0();
        case SupportedPidC1_E0:
            return &vehicle->getPidSupport().getCollectionPidC1_E0();
        case FuelSystemStatus:
            return &vehicle->getFuelSystemStates();
        case MonitoringStatusSinceDTCsCleared:
            return &vehicle->getMonitorStatusSinceDTCsCleared();
        case FreezeDTCPid:
            return &vehicle->getFreezeDTC();
        case CalculatedEngineLoad:
            return &vehicle->getEngine().getLoad();
        case EngineCoolantTemperature:
            return &vehicle->getEngine().getCoolantTemperature();
        case ShortTermFuelTrimBank1:
            return &vehicle->getEngine().getShortTermFuelTrimBank1();
        case LongTermFuelTrimBank1:
            return &vehicle->getEngine().getLongTermFuelTrimBank1();
        case ShortTermFuelTrimBank2:
            return &vehicle->getEngine().getShortTermFuelTrimBank2();
        case LongTermFuelTrimBank2:
            return &vehicle->getEngine().getLongTermFuelTrimBank2();
        case FuelPressure:
            return &vehicle->getEngine().getFuelPressure();
        case IntakeManifoldAbsolutePressure:
            return &vehicle->getEngine().getIntakeManifoldAbsolutePressure();
        case EngineRPM:
            return &vehicle->getEngine().getEngineRPM();
        case VehicleSpeed:
            return &vehicle->getSpeed();
        case TimingAdvance:
            return &vehicle->getEngine().getTimingAdvance();
        case IntakeAirTemperature:
            return &vehicle->getEngine().getIntakeAirTemperature();
        case MAFAirFlowRate:
            return &vehicle->getEngine().getMAFAirFlowRate();
        case ThrottlePosition:
            return &vehicle->getThrottle().getThrottlePosition();
        case CommandedSecondaryAirStatus:
            return &vehicle->getCommandedSecondaryAirStatus();
        case OxygenSensorsPresent:
            return &vehicle->getOxygenSystem().getBankOxygenSensorsCollection();
        case BankOxygenSensor1:
            return &vehicle->getOxygenSystem().getBankOxygenSensor1();
        case BankOxygenSensor2:
            return &vehicle->getOxygenSystem().getBankOxygenSensor2();
        case BankOxygenSensor3:
            return &vehicle->getOxygenSystem().getBankOxygenSensor3();
        case BankOxygenSensor4:
            return &vehicle->getOxygenSystem().getBankOxygenSensor4();
        case BankOxygenSensor5:
            return &vehicle->getOxygenSystem().getBankOxygenSensor5();
        case BankOxygenSensor6:
            return &vehicle->getOxygenSystem().getBankOxygenSensor6();
        case BankOxygenSensor7:
            return &vehicle->getOxygenSystem().getBankOxygenSensor7();
        case BankOxygenSensor8:
            return &vehicle->getOxygenSystem().getBankOxygenSensor8();
        case OBDStandardsVehicleConformsTo:
            return &vehicle->getOBDCompliance();
        case OxygenSensorsPresent4Banks:
            return &vehicle->getOxygenSystem().getBankOxygenSensor4BankCollection();
        case AuxiliaryInputStatus:
            return &vehicle->getAuxiliaryInputStatus();
        case RunTimeSinceEngineStart:
            return &vehicle->getRunTimeSinceEngineStart();
        case DistanceTraveledWithMilOn:
            return &vehicle->getDistanceTraveledWithMilOn();
        case FuelRailPressure:
            return &vehicle->getFuelRailPressure();
        case FuelRailGaugePressure:
            return &vehicle->getFuelRailGaugePressure();
        case FuelRailOxygenSensor1:
            return &vehicle->getOxygenSystem().getFuelRailOxygenSensor1();
        case FuelRailOxygenSensor2:
            return &vehicle->getOxygenSystem().getFuelRailOxygenSensor2();
        case FuelRailOxygenSensor3:
            return &vehicle->getOxygenSystem().getFuelRailOxygenSensor3();
        case FuelRailOxygenSensor4:
            return &vehicle->getOxygenSystem().getFuelRailOxygenSensor4();
        case FuelRailOxygenSensor5:
            return &vehicle->getOxygenSystem().getFuelRailOxygenSensor5();
        case FuelRailOxygenSensor6:
            return &vehicle->getOxygenSystem().getFuelRailOxygenSensor6();
        case FuelRailOxygenSensor7:
            return &vehicle->getOxygenSystem().getFuelRailOxygenSensor7();
        case FuelRailOxygenSensor8:
            return &vehicle->getOxygenSystem().getFuelRailOxygenSensor8();
        case CommandedEGR:
            return &vehicle->getCommandedEGR();
        case EGRError:
            return &vehicle->getEGRError();
        case CommandedEvaporativePurge:
            return &vehicle->getCommandedEvaporativePurge();
        case FuelTankLevelInput:
            return &vehicle->getFuelTankLevelInput();
        case WarmUpsSinceCodesCleared:
            return &vehicle->getWarmUpsSinceCodesCleared();
        case DistanceTraveledSinceCodesCleared:
            return &vehicle->getDistanceTraveledSinceCodesCleared();
        case EvaporativePurgeSystemVaporPressure:
            return &vehicle->getEvaporativePurgeSystemVaporPressure();
        case AbsoluteBarometricPressure:
            return &vehicle->getAbsoluteBarometricPressure();
        case ExtendedRangeOxygenSensor1:
            return &vehicle->getOxygenSystem().getExtendedRangeOxygenSensor1();
        case ExtendedRangeOxygenSensor2:
            return &vehicle->getOxygenSystem().getExtendedRangeOxygenSensor2();
        case ExtendedRangeOxygenSensor3:
            return &vehicle->getOxygenSystem().getExtendedRangeOxygenSensor3();
        case ExtendedRangeOxygenSensor4:
            return &vehicle->getOxygenSystem().getExtendedRangeOxygenSensor4();
        case ExtendedRangeOxygenSensor5:
            return &vehicle->getOxygenSystem().getExtendedRangeOxygenSensor5();
        case ExtendedRangeOxygenSensor6:
            return &vehicle->getOxygenSystem().getExtendedRangeOxygenSensor6();
        case ExtendedRangeOxygenSensor7:
            return &vehicle->getOxygenSystem().getExtendedRangeOxygenSensor7();
        case ExtendedRangeOxygenSensor8:
            return &vehicle->getOxygenSystem().getExtendedRangeOxygenSensor8();
        case CatalystTemperatureBank1Sensor1:
            return &vehicle->getCatalyst().getTemperatureBank1Sensor1();
        case CatalystTemperatureBank2Sensor1:
            return &vehicle->getCatalyst().getTemperatureBank2Sensor1();
        case CatalystTemperatureBank1Sensor2:
            return &vehicle->getCatalyst().getTemperatureBank1Sensor2();
        case CatalystTemperatureBank2Sensor2:
            return &vehicle->getCatalyst().getTemperatureBank2Sensor2();
        case MonitorStatusThisDriveCycle:
            return &vehicle->getMonitorStatusThisDriveCycle();
        case ControlModuleVoltage:
            return &vehicle->getControlModuleVoltage();
        case AbsoluteLoadValue:
            return &vehicle->getAbsoluteLoadValue();
        case FuelAirCommandedEquivalenceRatio:
            return &vehicle->getFuelAirCommandedEquivalenceRatio();
        case RelativeThrottlePosition:
            return &vehicle->getThrottle().getRelativeThrottlePosition();
        case AmbientAirTemperature:
            return &vehicle->getAmbientAirTemperature();
        case AbsoluteThrottlePositionB:
            return &vehicle->getThrottle().getAbsoluteThrottlePositionB();
        case AbsoluteThrottlePositionC:
            return &vehicle->getThrottle().getAbsoluteThrottlePositionC();
        case AcceleratorPedalPositionD:
            return &vehicle->getThrottle().getAcceleratorPedalPositionD();
        case AcceleratorPedalPositionE:
            return &vehicle->getThrottle().getAcceleratorPedalPositionE();
        case AcceleratorPedalPositionF:
            return &vehicle->getThrottle().getAcceleratorPedalPositionF();
        default:
            LOG(ERROR) << "pid: " + to_string(pid) + " not implemented";
            return nullptr;
    }
}

void Pid::writeService1_2(Vehicle *vehicle, byte *data, int size) {
    auto *fo = getFrameObject(vehicle);
    if (nullptr != fo) {
        fo->fromFrame(data, size);
    }
}

byte *Pid::readService1_2(Vehicle *vehicle, int &size) {
    unsigned int data = 0;
    int bitSize = 0;
    auto *fo = getFrameObject(vehicle);
    if (nullptr == fo) {
        return nullptr;
    }

    data = getFrameObject(vehicle)->toFrame(data, bitSize);

    size = getBytes(bitSize);
    byte *retVal = uintToByteArray(data);
    return retVal;
}

byte *Pid::getQueryForService(Service service, int &buflen) {
    buflen = 2;
    byte *frame = new byte[buflen];
    frame[0] = (byte) service;
    frame[1] = (byte) id;
    return frame;
}




