//
// Created by me on 30/12/18.
//

#include "DataObjectDescriptionText.h"

const string
DataObjectDescriptionText::getMonitorStatusMIL() { return "Off or On, indicates if the CEL/MIL is on (or should be on)"; }

const string
DataObjectDescriptionText::getMonitorStatusDTC() { return "Number of confirmed emissions-related DTCs available for display."; }

const string DataObjectDescriptionText::getOBDTest() { return "OBDTest "; }

const string DataObjectDescriptionText::getOBDTestAvailable() { return " available"; }

const string DataObjectDescriptionText::getOBDTestIncomplete() { return " incomplete"; }

const string DataObjectDescriptionText::getBankOxygenSensorVoltage() { return "Bank Oxygensensor Voltage"; }

const string DataObjectDescriptionText::getBankOxygenSensorShortFuelTrim() { return "Bank Oxygensensor Fuel Trim"; }

const string DataObjectDescriptionText::getCatalystTemperatureSensor(int bank, int sensor) {
    return "Catalyst Temperature Bank " + to_string(bank) + " Sensor " + to_string(sensor);
}

const string DataObjectDescriptionText::getCalculatedLoad() { return "Calculated Load"; }

const string DataObjectDescriptionText::getCoolantTemperature() { return "Coolant Temperature"; }

const string DataObjectDescriptionText::getShortTermFuelTrimBank(int bank) {
    return "Short term fuel trim bank" + to_string(bank);
}

const string DataObjectDescriptionText::getLongTermFuelTrimBank(int bank) {
    return "Long term fuel trim bank" + to_string(bank);
}

const string DataObjectDescriptionText::getFuelPressure() { return "Fuel pressure"; }

const string DataObjectDescriptionText::getIntakeManifoldAbsolutePressure() { return "Intake Manifold Pressure"; }

const string DataObjectDescriptionText::getEngineRPM() { return "Engine RPM"; }

const string DataObjectDescriptionText::getTimingAdvance() { return "Timing Advance"; }

const string DataObjectDescriptionText::getIntakeAirTemperature() { return "Intake Air Temperature"; }

const string DataObjectDescriptionText::getMafAirFlowRate() { return "Maf Airflow rate"; }

const string DataObjectDescriptionText::getEngineType() { return "Engine Type"; }

const string DataObjectDescriptionText::getDataTroubleCode() { return "Data Trouble Code"; }

const string DataObjectDescriptionText::getComponents() {
    return "Components";
}

const string DataObjectDescriptionText::getMisfire() {
    return "Misfire";
}

const string DataObjectDescriptionText::getFuelSystem() {
    return "Fuel system";
}

const string DataObjectDescriptionText::getVoltage() {
    return "Voltage";
}

const string DataObjectDescriptionText::getShortTermFuelTrim() {
    return "Short Term Fuel Trim";
}

const string DataObjectDescriptionText::getBankSensorPresent(int bank, int sensor) {
    return "Bank " + to_string(bank) + " Oxygen Sensor " + to_string(sensor) + " present";
}

const string DataObjectDescriptionText::getBankSensorPresentIn4Banks(int bank, int sensor) {
    return "4 Bank " + to_string(bank) + " Oxygen Sensor " + to_string(sensor) + " present";
}

const string DataObjectDescriptionText::getFuelAirEquivalenceRatio() {
    return "Fuel Air Equivalence Ration";
}

const string DataObjectDescriptionText::getCurrent() {
    return "Current";
}

const string DataObjectDescriptionText::getPidSupported(int pid) {
    return "Pid " + to_string(pid) + " Supported";
}

const string DataObjectDescriptionText::getThrottlePosition() {
    return "Throttle position";
}

const string DataObjectDescriptionText::getRelativeThrottlePosition() {
    return "Relative Throttle Position";
}

const string DataObjectDescriptionText::getAbsoluteThrottlePosition(string val) {
    return "Absolute Throttle Position " + val;
}

const string DataObjectDescriptionText::getFuelSystemState(int system) {
    return "Fuel System State " + to_string(system);
}


const string DataObjectDescriptionText::getCommandedSecondaryAirStatus() {
    return "Commanded Secondary AirS tatus";
}

const string DataObjectDescriptionText::getSpeed() {
    return "Speed";
}

const string DataObjectDescriptionText::getWarmUpsSinceCodesCleared() {
    return "Warm Ups Since Codes Cleared";
}

const string DataObjectDescriptionText::getDistanceTraveledSinceCodesCleared() {
    return "Distance Traveled Since Codes Cleared";
}

const string DataObjectDescriptionText::getAuxiliaryInputStatus() {
    return "Auxiliary Input Status";
}

const string DataObjectDescriptionText::getRunTimeSinceEngineStart() {
    return "Run Time SinceEngineStart";
}

const string DataObjectDescriptionText::getDistanceTraveledWithMilOn() {
    return "Distance Traveled With Mil on";
}

const string DataObjectDescriptionText::getAbsoluteBarometricPressure() {
    return "Absolute Barometric Pressure";
}

const string DataObjectDescriptionText::getFuelRailPressure() {
    return "Fuel Rail Pressure";
}

const string DataObjectDescriptionText::getCommandedEGR() {
    return "Commanded EGR";
}

const string DataObjectDescriptionText::getEgrError() {
    return "Egr Error";
}

const string DataObjectDescriptionText::getCommandedEvaporativePurge() {
    return "Commanded Evaporative Purge";
}

const string DataObjectDescriptionText::getFuelTankLevelInput() {
    return "Fuel TankLevel Input";
}

const string DataObjectDescriptionText::getEvaporativePurgeSystemVaporPressure() {
    return "Evaporative Purge System Vapor Pressure";
}

const string DataObjectDescriptionText::getControlModuleVoltage() {
    return "Control Module Voltage";
}

const string DataObjectDescriptionText::getAbsoluteLoadValue() {
    return "Absolute Load Value";
}

const string DataObjectDescriptionText::getFuelAirCommandedEquivalenceRatio() {
    return "Fuel Air Commanded Equivalence Ratio";
}

const string DataObjectDescriptionText::getAmbientAirTemperature() {
    return "Ambient Air Temperature";
}

const string DataObjectDescriptionText::getFuelRailGaugePressure() {
    return "Fuel Rail Gauge Pressure";
}
