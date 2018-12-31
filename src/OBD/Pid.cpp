//
// Created by me on 14/12/18.
//

#include "Pid.h"


void Pid::updateVehicle(Service service, Vehicle *vehicle, byte *data, int dataSize) {
    switch (service){
        case POWERTRAIN:
        case FREEZE_FRAME:
            updateService1_2(vehicle, data, dataSize);
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
        case CalculatedEngineLoad:
            vehicle->getEngine().getLoad().fromFrame(data, size);
            break;
        case EngineCoolantTemperature:
            vehicle->getEngine().getCoolantTemperature().fromFrame(data, size);
            break;
        case ShortTermFuelTrimBank1:
            vehicle->getEngine().getShortTermFuelTrimBank1().fromFrame(data, size);
            break;
        case LongTermFuelTrimBank1:
            vehicle->getEngine().getLongTermFuelTrimBank1().fromFrame(data, size);
            break;
        case ShortTermFuelTrimBank2:
            vehicle->getEngine().getShortTermFuelTrimBank2().fromFrame(data, size);
            break;
        case LongTermFuelTrimBank2:
            vehicle->getEngine().getLongTermFuelTrimBank2().fromFrame(data, size);
            break;
        case FuelPressure:
            vehicle->getEngine().getFuelPressure().fromFrame(data, size);
            break;
        case IntakeManifoldAbsolutePressure:
            vehicle->getEngine().getIntakeManifoldAbsolutePressure().fromFrame(data, size);
            break;
        case EngineRPM:
            vehicle->getEngine().getEngineRPM().fromFrame(data, size);
            break;
        case VehicleSpeed:
            vehicle->getSpeed().fromFrame(data, size);
            break;
        case TimingAdvance:
            vehicle->getEngine().getTimingAdvance().fromFrame(data, size);
            break;
        case IntakeAirTemperature:
            vehicle->getEngine().getIntakeAirTemperature().fromFrame(data, size);
            break;
        case MAFAirFlowRate:
            vehicle->getEngine().getMAFAirFlowRate().fromFrame(data, size);
            break;
        case ThrottlePosition:
            vehicle->getThrottlePosition().fromFrame(data, size);
            break;
        case CommandedSecondaryAirStatus:
            vehicle->getCommandedSecondaryAirStatus().fromFrame(data, size);
            break;
        case OxygenSensorsPresent:
            vehicle->getOxygenSystem().getBankSensorsPresentFromFrame(data, size);
            break;
        case BankOxygenSensor1:
            vehicle->getOxygenSystem().getBankOxygenSensor1().fromFrame(data, size);
            break;
        case BankOxygenSensor2:
            vehicle->getOxygenSystem().getBankOxygenSensor2().fromFrame(data, size);
            break;
        case BankOxygenSensor3:
            vehicle->getOxygenSystem().getBankOxygenSensor3().fromFrame(data, size);
            break;
        case BankOxygenSensor4:
            vehicle->getOxygenSystem().getBankOxygenSensor4().fromFrame(data, size);
            break;
        case BankOxygenSensor5:
            vehicle->getOxygenSystem().getBankOxygenSensor5().fromFrame(data, size);
            break;
        case BankOxygenSensor6:
            vehicle->getOxygenSystem().getBankOxygenSensor6().fromFrame(data, size);
            break;
        case BankOxygenSensor7:
            vehicle->getOxygenSystem().getBankOxygenSensor7().fromFrame(data, size);
            break;
        case BankOxygenSensor8:
            vehicle->getOxygenSystem().getBankOxygenSensor8().fromFrame(data, size);
            break;
        case OBDStandardsVehicleConformsTo:
            vehicle->getOBDCompliance().fromFrame(data, size);
            break;
        case OxygenSensorsPresent4Banks:
            vehicle->getOxygenSystem().getBankSensorsPresentIn4BanksFromFrame(data, size);
            break;
        case AuxiliaryInputStatus:
            vehicle->getAuxiliaryInputStatus().fromFrame(data, size);
            break;
        case RunTimeSinceEngineStart:
            vehicle->getRunTimeSinceEngineStart().fromFrame(data, size);
            break;
        case DistanceTraveledWithMilOn:
            vehicle->getDistanceTraveledWithMilOn().fromFrame(data, size);
            break;
        case FuelRailPressure:
            vehicle->getFuelRailPressure().fromFrame(data, size);
            break;
        case FuelRailGaugePressure:
            vehicle->getFuelRailGaugePressure().fromFrame(data, size);
            break;
        case FuelRailOxygenSensor1:
            vehicle->getOxygenSystem().getFuelRailOxygenSensor1().fromFrame(data, size);
            break;
        case FuelRailOxygenSensor2:
            vehicle->getOxygenSystem().getFuelRailOxygenSensor2().fromFrame(data, size);
            break;
        case FuelRailOxygenSensor3:
            vehicle->getOxygenSystem().getFuelRailOxygenSensor3().fromFrame(data, size);
            break;
        case FuelRailOxygenSensor4:
            vehicle->getOxygenSystem().getFuelRailOxygenSensor4().fromFrame(data, size);
            break;
        case FuelRailOxygenSensor5:
            vehicle->getOxygenSystem().getFuelRailOxygenSensor5().fromFrame(data, size);
            break;
        case FuelRailOxygenSensor6:
            vehicle->getOxygenSystem().getFuelRailOxygenSensor6().fromFrame(data, size);
            break;
        case FuelRailOxygenSensor7:
            vehicle->getOxygenSystem().getFuelRailOxygenSensor7().fromFrame(data, size);
            break;
        case FuelRailOxygenSensor8:
            vehicle->getOxygenSystem().getFuelRailOxygenSensor8().fromFrame(data, size);
            break;
        case CommandedEGR:
            vehicle->getCommandedEGR().fromFrame(data, size);
            break;
        case EGRError:
            vehicle->getEGRError().fromFrame(data, size);
            break;
        case CommandedEvaporativePurge:
            vehicle->getCommandedEvaporativePurge().fromFrame(data, size);
            break;
        case FuelTankLevelInput:
            vehicle->getFuelTankLevelInput().fromFrame(data, size);
            break;
        case WarmUpsSinceCodesCleared:
            vehicle->getWarmUpsSinceCodesCleared().fromFrame(data, size);
            break;
        case DistanceTraveledSinceCodesCleared:
            vehicle->getDistanceTraveledSinceCodesCleared().fromFrame(data, size);
            break;
        case EvaporativePurgeSystemVaporPressure:
            vehicle->getEvaporativePurgeSystemVaporPressure().fromFrame(data, size);
            break;
        case AbsoluteBarometricPressure:
            vehicle->getAbsoluteBarometricPressure().fromFrame(data, size);
            break;
        case ExtendedRangeOxygenSensor1:
            vehicle->getOxygenSystem().getExtendedRangeOxygenSensor1().fromFrame(data, size);
            break;
        case ExtendedRangeOxygenSensor2:
            vehicle->getOxygenSystem().getExtendedRangeOxygenSensor2().fromFrame(data, size);
            break;
        case ExtendedRangeOxygenSensor3:
            vehicle->getOxygenSystem().getExtendedRangeOxygenSensor3().fromFrame(data, size);
            break;
        case ExtendedRangeOxygenSensor4:
            vehicle->getOxygenSystem().getExtendedRangeOxygenSensor4().fromFrame(data, size);
            break;
        case ExtendedRangeOxygenSensor5:
            vehicle->getOxygenSystem().getExtendedRangeOxygenSensor5().fromFrame(data, size);
            break;
        case ExtendedRangeOxygenSensor6:
            vehicle->getOxygenSystem().getExtendedRangeOxygenSensor6().fromFrame(data, size);
            break;
        case ExtendedRangeOxygenSensor7:
            vehicle->getOxygenSystem().getExtendedRangeOxygenSensor7().fromFrame(data, size);
            break;
        case ExtendedRangeOxygenSensor8:
            vehicle->getOxygenSystem().getExtendedRangeOxygenSensor8().fromFrame(data, size);
            break;
        case CatalystTemperatureBank1Sensor1:
            vehicle->getCatalyst().getTemperatureBank1Sensor1().fromFrame(data, size);
            break;
        case CatalystTemperatureBank2Sensor1:
            vehicle->getCatalyst().getTemperatureBank2Sensor1().fromFrame(data, size);
            break;
        case CatalystTemperatureBank1Sensor2:
            vehicle->getCatalyst().getTemperatureBank1Sensor2().fromFrame(data, size);
            break;
        case CatalystTemperatureBank2Sensor2:
            vehicle->getCatalyst().getTemperatureBank2Sensor2().fromFrame(data, size);
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
        case CalculatedEngineLoad:
            data = vehicle->getEngine().getLoad().toFrame(data);
            break;
        case EngineCoolantTemperature:
            data = vehicle->getEngine().getCoolantTemperature().toFrame(data);
            break;
        case ShortTermFuelTrimBank1:
            data = vehicle->getEngine().getShortTermFuelTrimBank1().toFrame(data);
            break;
        case LongTermFuelTrimBank1:
            data = vehicle->getEngine().getLongTermFuelTrimBank1().toFrame(data);
            break;
        case ShortTermFuelTrimBank2:
            data = vehicle->getEngine().getShortTermFuelTrimBank2().toFrame(data);
            break;
        case LongTermFuelTrimBank2:
            data = vehicle->getEngine().getLongTermFuelTrimBank2().toFrame(data);
            break;
        case FuelPressure:
            data = vehicle->getEngine().getFuelPressure().toFrame(data);
            break;
        case IntakeManifoldAbsolutePressure:
            data = vehicle->getEngine().getIntakeManifoldAbsolutePressure().toFrame(data);
            break;
        case EngineRPM:
            data = vehicle->getEngine().getEngineRPM().toFrame(data);
            break;
        case VehicleSpeed:
            data = vehicle->getSpeed().toFrame(data);
            break;
        case TimingAdvance:
            data = vehicle->getEngine().getTimingAdvance().toFrame(data);
            break;
        case IntakeAirTemperature:
            data = vehicle->getEngine().getIntakeAirTemperature().toFrame(data);
            break;
        case MAFAirFlowRate:
            data = vehicle->getEngine().getMAFAirFlowRate().toFrame(data);
            break;
        case ThrottlePosition:
            data = vehicle->getThrottlePosition().toFrame(data);
            break;
        case CommandedSecondaryAirStatus:
            data = vehicle->getCommandedSecondaryAirStatus().toFrame(data);
            break;
        case OxygenSensorsPresent:
            data = vehicle->getOxygenSystem().getBankSensorsPresentToFrame(data);
            break;
        case BankOxygenSensor1:
            data = vehicle->getOxygenSystem().getBankOxygenSensor1().toFrame(data);
            break;
        case BankOxygenSensor2:
            data = vehicle->getOxygenSystem().getBankOxygenSensor2().toFrame(data);
            break;
        case BankOxygenSensor3:
            data = vehicle->getOxygenSystem().getBankOxygenSensor3().toFrame(data);
            break;
        case BankOxygenSensor4:
            data = vehicle->getOxygenSystem().getBankOxygenSensor4().toFrame(data);
            break;
        case BankOxygenSensor5:
            data = vehicle->getOxygenSystem().getBankOxygenSensor5().toFrame(data);
            break;
        case BankOxygenSensor6:
            data = vehicle->getOxygenSystem().getBankOxygenSensor6().toFrame(data);
            break;
        case BankOxygenSensor7:
            data = vehicle->getOxygenSystem().getBankOxygenSensor7().toFrame(data);
            break;
        case BankOxygenSensor8:
            data = vehicle->getOxygenSystem().getBankOxygenSensor8().toFrame(data);
            break;
        case OBDStandardsVehicleConformsTo:
            data = vehicle->getOBDCompliance().toFrame(data);
            break;
        case OxygenSensorsPresent4Banks:
            data = vehicle->getOxygenSystem().getBankSensorsPresentIn4BanksToFrame(data);
            break;
        case AuxiliaryInputStatus:
            data = vehicle->getAuxiliaryInputStatus().toFrame(data);
            break;
        case RunTimeSinceEngineStart:
            data = vehicle->getRunTimeSinceEngineStart().toFrame(data);
            break;
        case DistanceTraveledWithMilOn:
            data = vehicle->getDistanceTraveledWithMilOn().toFrame(data);
            break;
        case FuelRailPressure:
            data = vehicle->getFuelRailPressure().toFrame(data);
            break;
        case FuelRailGaugePressure:
            data = vehicle->getFuelRailGaugePressure().toFrame(data);
            break;
        case FuelRailOxygenSensor1:
            data = vehicle->getOxygenSystem().getFuelRailOxygenSensor1().toFrame(data);
            break;
        case FuelRailOxygenSensor2:
            data = vehicle->getOxygenSystem().getFuelRailOxygenSensor2().toFrame(data);
            break;
        case FuelRailOxygenSensor3:
            data = vehicle->getOxygenSystem().getFuelRailOxygenSensor3().toFrame(data);
            break;
        case FuelRailOxygenSensor4:
            data = vehicle->getOxygenSystem().getFuelRailOxygenSensor4().toFrame(data);
            break;
        case FuelRailOxygenSensor5:
            data = vehicle->getOxygenSystem().getFuelRailOxygenSensor5().toFrame(data);
            break;
        case FuelRailOxygenSensor6:
            data = vehicle->getOxygenSystem().getFuelRailOxygenSensor6().toFrame(data);
            break;
        case FuelRailOxygenSensor7:
            data = vehicle->getOxygenSystem().getFuelRailOxygenSensor7().toFrame(data);
            break;
        case FuelRailOxygenSensor8:
            data = vehicle->getOxygenSystem().getFuelRailOxygenSensor8().toFrame(data);
            break;
        case CommandedEGR:
            data = vehicle->getCommandedEGR().toFrame(data);
            break;
        case EGRError:
            data = vehicle->getEGRError().toFrame(data);
            break;
        case CommandedEvaporativePurge:
            data = vehicle->getCommandedEvaporativePurge().toFrame(data);
            break;
        case FuelTankLevelInput:
            data = vehicle->getFuelTankLevelInput().toFrame(data);
            break;
        case WarmUpsSinceCodesCleared:
            data = vehicle->getWarmUpsSinceCodesCleared().toFrame(data);
            break;
        case DistanceTraveledSinceCodesCleared:
            data = vehicle->getDistanceTraveledSinceCodesCleared().toFrame(data);
            break;
        case EvaporativePurgeSystemVaporPressure:
            data = vehicle->getEvaporativePurgeSystemVaporPressure().toFrame(data);
            break;
        case AbsoluteBarometricPressure:
            data = vehicle->getAbsoluteBarometricPressure().toFrame(data);
            break;
        case ExtendedRangeOxygenSensor1:
            data = vehicle->getOxygenSystem().getExtendedRangeOxygenSensor1().toFrame(data);
            break;
        case ExtendedRangeOxygenSensor2:
            data = vehicle->getOxygenSystem().getExtendedRangeOxygenSensor2().toFrame(data);
            break;
        case ExtendedRangeOxygenSensor3:
            data = vehicle->getOxygenSystem().getExtendedRangeOxygenSensor3().toFrame(data);
            break;
        case ExtendedRangeOxygenSensor4:
            data = vehicle->getOxygenSystem().getExtendedRangeOxygenSensor4().toFrame(data);
            break;
        case ExtendedRangeOxygenSensor5:
            data = vehicle->getOxygenSystem().getExtendedRangeOxygenSensor5().toFrame(data);
            break;
        case ExtendedRangeOxygenSensor6:
            data = vehicle->getOxygenSystem().getExtendedRangeOxygenSensor6().toFrame(data);
            break;
        case ExtendedRangeOxygenSensor7:
            data = vehicle->getOxygenSystem().getExtendedRangeOxygenSensor7().toFrame(data);
            break;
        case ExtendedRangeOxygenSensor8:
            data = vehicle->getOxygenSystem().getExtendedRangeOxygenSensor8().toFrame(data);
            break;
        case CatalystTemperatureBank1Sensor1:
            data = vehicle->getCatalyst().getTemperatureBank1Sensor1().toFrame(data);
            break;
        case CatalystTemperatureBank2Sensor1:
            data = vehicle->getCatalyst().getTemperatureBank2Sensor1().toFrame(data);
            break;
        case CatalystTemperatureBank1Sensor2:
            data = vehicle->getCatalyst().getTemperatureBank1Sensor2().toFrame(data);
            break;
        case CatalystTemperatureBank2Sensor2:
            data = vehicle->getCatalyst().getTemperatureBank2Sensor2().toFrame(data);
            break;
    }

    byte *retVal = uintToByteArray(data);
    return retVal;
}




