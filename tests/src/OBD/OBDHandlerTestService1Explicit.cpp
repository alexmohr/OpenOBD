//
// Created by me on 01/01/19.
//
#include "gtest/gtest.h"

#include "../../../src/Config.h"
#include "OBDHandlerTest.h"
#include "../../../src/common/endian.h"
#include "gtest/gtest.h"
#include <random>


void PID_1C_Supported_Standards_Setter(bool value, OBDCompliance &compliance) {
    compliance.getOBD_II_CARB().setValue(value);
    EXPECT_EQ(compliance.getOBD_II_CARB().getValue(), value);

    compliance.getOBD_EPA().setValue(value);
    EXPECT_EQ(compliance.getOBD_EPA().getValue(), value);

    compliance.getOBD_and_OBD_II().setValue(value);
    EXPECT_EQ(compliance.getOBD_and_OBD_II().getValue(), value);

    compliance.getOBD_I().setValue(value);
    EXPECT_EQ(compliance.getOBD_I().getValue(), value);

    compliance.getNotOBDcompliant().setValue(value);
    EXPECT_EQ(compliance.getNotOBDcompliant().getValue(), value);

    compliance.getEOBD().setValue(value);
    EXPECT_EQ(compliance.getEOBD().getValue(), value);

    compliance.getEOBDandOBD_II().setValue(value);
    EXPECT_EQ(compliance.getEOBDandOBD_II().getValue(), value);

    compliance.getEOBDandOBD().setValue(value);
    EXPECT_EQ(compliance.getEOBDandOBD().getValue(), value);

    compliance.getEOBD_OBD_and_OBDII().setValue(value);
    EXPECT_EQ(compliance.getEOBD_OBD_and_OBDII().getValue(), value);

    compliance.getJOBD().setValue(value);
    EXPECT_EQ(compliance.getJOBD().getValue(), value);

    compliance.getJOBDandOBDII().setValue(value);
    EXPECT_EQ(compliance.getJOBDandOBDII().getValue(), value);

    compliance.getJOBDandEOBD().setValue(value);
    EXPECT_EQ(compliance.getJOBDandEOBD().getValue(), value);

    compliance.getJOBD_EOBD_and_OBDII().setValue(value);
    EXPECT_EQ(compliance.getJOBD_EOBD_and_OBDII().getValue(), value);

    compliance.getEngineManufacturerDiagnostics().setValue(value);
    EXPECT_EQ(compliance.getEngineManufacturerDiagnostics().getValue(), value);

    compliance.getEngineManufacturerDiagnosticsEnhanced().setValue(value);
    EXPECT_EQ(compliance.getEngineManufacturerDiagnosticsEnhanced().getValue(), value);

    compliance.getHeavyDutyOn_BoardDiagnostics_OBD_C().setValue(value);
    EXPECT_EQ(compliance.getHeavyDutyOn_BoardDiagnostics_OBD_C().getValue(), value);

    compliance.getHeavyDutyOn_BoardDiagnostics().setValue(value);
    EXPECT_EQ(compliance.getHeavyDutyOn_BoardDiagnostics().getValue(), value);

    compliance.getWorldWideHarmonizedOBD().setValue(value);
    EXPECT_EQ(compliance.getWorldWideHarmonizedOBD().getValue(), value);

    compliance.getHeavyDutyEuroOBDStageIwithoutNOxcontrol().setValue(value);
    EXPECT_EQ(compliance.getHeavyDutyEuroOBDStageIwithoutNOxcontrol().getValue(), value);

    compliance.getHeavyDutyEuroOBDStageIwithNOxcontrol().setValue(value);
    EXPECT_EQ(compliance.getHeavyDutyEuroOBDStageIwithNOxcontrol().getValue(), value);

    compliance.getHeavyDutyEuroOBDStageIIwithoutNOxcontrol().setValue(value);
    EXPECT_EQ(compliance.getHeavyDutyEuroOBDStageIIwithoutNOxcontrol().getValue(), value);

    compliance.getHeavyDutyEuroOBDStageIIwithNOxcontrol().setValue(value);
    EXPECT_EQ(compliance.getHeavyDutyEuroOBDStageIIwithNOxcontrol().getValue(), value);

    compliance.getBrazilOBDPhase1().setValue(value);
    EXPECT_EQ(compliance.getBrazilOBDPhase1().getValue(), value);

    compliance.getBrazilOBDPhase2().setValue(value);
    EXPECT_EQ(compliance.getBrazilOBDPhase2().getValue(), value);

    compliance.getKoreanOBD().setValue(value);
    EXPECT_EQ(compliance.getKoreanOBD().getValue(), value);

    compliance.getIndiaOBDI().setValue(value);
    EXPECT_EQ(compliance.getIndiaOBDI().getValue(), value);

    compliance.getIndiaOBDII().setValue(value);
    EXPECT_EQ(compliance.getIndiaOBDII().getValue(), value);

    compliance.getHeavyDutyEuroOBDStageVI().setValue(value);
    EXPECT_EQ(compliance.getHeavyDutyEuroOBDStageVI().getValue(), value);
}

// EXPLICIT Implemented

TEST(OBDHandler, PID_00_PIDSupported01_20) {
    auto const pid = (byte) 0x00;
    vector<byte> request{RequestServiceID, pid};
    vector<byte> response{ResponseServiceID, pid, (byte) 0xbe, (byte) 0x7e, (byte) 0xb8, (byte) 0x13};
    doTest(request, response);
}

TEST(OBDHandler, PID_00_PIDSupported01_20_Single) {
    auto const pid = (byte) 0x00;
    vector<byte> request{RequestServiceID, pid};
    vector<byte> response{ResponseServiceID, pid, (byte) 0x80, (byte) 0x00, (byte) 0x00, (byte) 0x00};

    OBDHandler *handler = getHandler();

    vector<int> supported{0x01};

    for (auto const &value: supported) {
        handler->getVehicle()->getPidSupport().setPidSupported(value, true);
    }

    for (auto const &value: supported) {
        EXPECT_TRUE(handler->getVehicle()->getPidSupport().getPidSupported(value));
    }

    int dataSize = 0;
    byte *val = handler->createAnswerFrame(request.data(), dataSize);
    EXPECT_EQ(dataSize, response.size());
    compareResponse(response, val);
}

TEST(OBDHandler, PID_00_PIDSupported01_20_Setter) {
    auto const pid = (byte) 0x00;
    vector<byte> request{RequestServiceID, pid};
    vector<byte> response{ResponseServiceID, pid, (byte) 0xbe, (byte) 0x1f, (byte) 0xa8, (byte) 0x13};

    OBDHandler *handler = getHandler();

    vector<int> supported{0x01, 0x03, 0x04, 0x05, 0x06, 0x07, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x13, 0x15, 0x1C,
                          0x1F, 0x20};

    for (auto const &value: supported) {
        handler->getVehicle()->getPidSupport().setPidSupported(value, true);
    }

    for (auto const &value: supported) {
        EXPECT_TRUE(handler->getVehicle()->getPidSupport().getPidSupported(value));
    }

    int dataSize = 0;
    byte *val = handler->createAnswerFrame(request.data(), dataSize);
    EXPECT_EQ(dataSize, response.size());
    compareResponse(response, val);
}

TEST(OBDHandler, PID_00_PIDSupportedGeneric) {
    const int pidsPerCall = 32;
    int j, k, currentPid;

    vector<Service1Pids> pids = {
            SupportedPid01_20,
            SupportedPid21_40,
            SupportedPid41_60,
            SupportedPid61_80,
            SupportedPid81_A0,
            SupportedPidA1_C0,
            SupportedPidC1_E0};


    OBDHandler *handler = getHandler();
    auto vehicle = handler->getVehicle();
    currentPid = 0;

    for (const auto &pid: pids) {
        k = pidsPerCall;
        for (j = 1; j <= pidsPerCall; j++) {
            currentPid++;
            EXPECT_FALSE(vehicle->getPidSupport().getPidSupported(currentPid));

            vehicle->getPidSupport().setPidSupported(currentPid, true);
            EXPECT_TRUE(vehicle->getPidSupport().getPidSupported(currentPid));

            vector<byte> request = {RequestServiceID, (byte) pid};
            int dataSize = 0;
            byte *val = handler->createAnswerFrame(request.data(), dataSize);
            auto *response = (byte *) malloc(sizeof(byte) * 8);
            response[0] = ResponseServiceID;
            response[1] = request.at(1);

            unsigned int data = 0;
            data |= 1 << --k;

            response[5] = (byte) (data & 0xFF);
            response[4] = (byte) ((data >> 8U) & 0xFF);
            response[3] = (byte) ((data >> 16U) & 0xFF);
            response[2] = (byte) ((data >> 24U) & 0xFF);

            compareResponse(response, val, 8);
            vehicle->getPidSupport().setPidSupported(currentPid, false);
        }
    }
}

TEST(OBDHandler, PID_01_AND_40_MonitoringStatus) {
/*
 *  MIL: on
    dtc count: 113
    B7 = 0
    Engine = petrol
    components avail: 1 incomplete 1
    fuel avail: 1 incomplete 1
    misfire avail 1 incomplete 0
    test   A    i
    egr    1    0
    ox     1    1
    oxheat 1    1
    ac     1    1
    seca   1    0
    eva    0    0
    heatct 0    0
    cata   1    1

 */
    const vector<Service1Pids> pids = {MonitoringStatusSinceDTCsCleared, MonitorStatusThisDriveCycle};

    for (const auto &pid: pids) {
        vector<byte> request{(RequestServiceID), (byte) pid};
        vector<byte> response{ResponseServiceID, (byte) pid, (byte) 0xf1, (byte) 0x67, (byte) 0xe3, (byte) 0xf1};
// do test will check the can response.
        auto handler = doTest(request, response);
        MonitorStatus *monitoringStatus = nullptr;
        if (pid == MonitoringStatusSinceDTCsCleared) {
            monitoringStatus = &handler->getVehicle()->getMonitorStatusSinceDTCsCleared();
        } else {
            monitoringStatus = &handler->getVehicle()->getMonitorStatusThisDriveCycle();
        }

// validate object state
        EXPECT_EQ(monitoringStatus->getMil(), true);
        EXPECT_EQ(monitoringStatus->getDtcCount(), 113);

        EXPECT_EQ(monitoringStatus->getComponents().getAvailable().getValue(), true);
        EXPECT_EQ(monitoringStatus->getComponents().getIncomplete().getValue(), true);

        EXPECT_EQ(monitoringStatus->getFuelSystem().getAvailable().getValue(), true);
        EXPECT_EQ(monitoringStatus->getFuelSystem().getIncomplete().getValue(), true);

        EXPECT_EQ(monitoringStatus->getMisfire().getAvailable().getValue(), true);
        EXPECT_EQ(monitoringStatus->getMisfire().getIncomplete().getValue(), false);

        Engine &engine = monitoringStatus->getEngine();
        EXPECT_EQ(engine.getEngineType().getValue(), PETROL);

        EXPECT_EQ(engine.getEngineSystem1().getAvailable().getValue(), true);
        EXPECT_EQ(engine.getEngineSystem2().getAvailable().getValue(), true);
        EXPECT_EQ(engine.getEngineSystem3().getAvailable().getValue(), true);
        EXPECT_EQ(engine.getEngineSystem4().getAvailable().getValue(), false);
        EXPECT_EQ(engine.getEngineSystem5().getAvailable().getValue(), false);
        EXPECT_EQ(engine.getEngineSystem6().getAvailable().getValue(), false);
        EXPECT_EQ(engine.getEngineSystem7().getAvailable().getValue(), true);
        EXPECT_EQ(engine.getEngineSystem8().getAvailable().getValue(), true);

        EXPECT_EQ(engine.getEngineSystem1().getIncomplete().getValue(), true);
        EXPECT_EQ(engine.getEngineSystem2().getIncomplete().getValue(), true);
        EXPECT_EQ(engine.getEngineSystem3().getIncomplete().getValue(), true);
        EXPECT_EQ(engine.getEngineSystem4().getIncomplete().getValue(), true);
        EXPECT_EQ(engine.getEngineSystem5().getIncomplete().getValue(), false);
        EXPECT_EQ(engine.getEngineSystem6().getIncomplete().getValue(), false);
        EXPECT_EQ(engine.getEngineSystem7().getIncomplete().getValue(), false);
        EXPECT_EQ(engine.getEngineSystem8().getIncomplete().getValue(), true);
    }
}


// make sure that the application can generate the request on its own and does not need can frames to init.
TEST(OBDHandler, PID_01_Test_MIL) {
    OBDHandler *handler = getHandler();
    MonitorStatus &monitoringStatus = handler->getVehicle()->getMonitorStatusSinceDTCsCleared();
// validate object state
    monitoringStatus.setMil(true);
    const auto pid = (byte) 0x01;
    vector<byte> request{(RequestServiceID), pid};
    int dataSize = 0;
    byte *val = handler->createAnswerFrame(request.data(), dataSize);
    vector<byte> response{ResponseServiceID, pid, (byte) 0x80, (byte) 0x00, (byte) 0x00, (byte) 0x00};
    compareResponse(response, val);

}

// make sure that the application can generate the request on its own and does not need can frames to init.
TEST(OBDHandler, PID_01_MonitoringStatusInitViaVehicle) {
    OBDHandler *handler = getHandler();
    MonitorStatus &monitoringStatus = handler->getVehicle()->getMonitorStatusSinceDTCsCleared();

// validate object state
    monitoringStatus.setMil(true);
    monitoringStatus.setDtcCount(113);

    monitoringStatus.getComponents().getAvailable().setValue(true);
    monitoringStatus.getComponents().getIncomplete().setValue(true);

    monitoringStatus.getFuelSystem().getAvailable().setValue(true);
    monitoringStatus.getFuelSystem().getIncomplete().setValue(true);

    monitoringStatus.getMisfire().getAvailable().setValue(true);
    monitoringStatus.getMisfire().getIncomplete().setValue(false);

    Engine &engine = monitoringStatus.getEngine();
    engine.setEngineType(DIESEL);

    engine.getEngineSystem1().getAvailable().setValue(true);
    engine.getEngineSystem2().getAvailable().setValue(true);
    engine.getEngineSystem3().getAvailable().setValue(true);
    engine.getEngineSystem4().getAvailable().setValue(false);
    engine.getEngineSystem5().getAvailable().setValue(false);
    engine.getEngineSystem6().getAvailable().setValue(false);
    engine.getEngineSystem7().getAvailable().setValue(true);
    engine.getEngineSystem8().getAvailable().setValue(true);

    engine.getEngineSystem1().getIncomplete().setValue(true);
    engine.getEngineSystem2().getIncomplete().setValue(true);
    engine.getEngineSystem3().getIncomplete().setValue(true);
    engine.getEngineSystem4().getIncomplete().setValue(true);
    engine.getEngineSystem5().getIncomplete().setValue(false);
    engine.getEngineSystem6().getIncomplete().setValue(false);
    engine.getEngineSystem7().getIncomplete().setValue(false);
    engine.getEngineSystem8().getIncomplete().setValue(true);

    const auto pid = (byte) 0x01;
    vector<byte> request{(RequestServiceID), pid};
    int dataSize;
    byte *val = handler->createAnswerFrame(request.data(), dataSize);
    vector<byte> response{ResponseServiceID, pid, (byte) 0xf1, (byte) 0x6f, (byte) 0xe3, (byte) 0xf1};
    EXPECT_EQ(dataSize, response.size());
    compareResponse(response, val);
}

TEST(OBDHandler, PID_02_FreezeDTC) {
    const auto pid = (byte) FreezeDTCPid;
    vector<byte> request{(RequestServiceID), pid};
    vector<byte> response{ResponseServiceID, pid, (byte) 0xe5, (byte) 0x00};
    auto handler = doTest(request, response);

    auto code = handler->getVehicle()->getFreezeDTC().getValue();

    EXPECT_EQ("U2500", code.getSaeId());
    EXPECT_EQ("(CAN) Lack of Acknowledgement From Engine Management", code.getDescription());
    EXPECT_EQ(0xe500, code.getCanId());
}

TEST(OBDHandler, PID_02_FreezeDTC_Setter) {
    OBDHandler *handler = getHandler();
    FreezeDTC &freezeDTC = handler->getVehicle()->getFreezeDTC();

    const int codeID = 0x5751;
    freezeDTC.setValue(codeID);

    DataTroubleCode code = freezeDTC.getValue();
    EXPECT_EQ(codeID, code.getCanId());
    EXPECT_EQ("C1751", code.getSaeId());
    EXPECT_EQ("Vehicle Speed Sensor # 1 Output Circuit Short to Vbatt", code.getDescription());

    const auto pid = (byte) FreezeDTCPid;
    vector<byte> request{(RequestServiceID), pid};
    vector<byte> response{ResponseServiceID, pid, (byte) 0x57, (byte) 0x51};
    doTest(request, response);
}

TEST(OBDHandler, PID_03_FuelSystemState) {
    const auto pid = (byte) FuelSystemStatus;
    vector<byte> request{(RequestServiceID), pid};
    OBDHandler *handler;
    int i;
    for (i = -1; i <= 4; i++) {
        StateOfFuelSystem state;
        if (-1 == i) {
            state = StateOfFuelSystemDoesNotExist;
        } else {
            state = StateOfFuelSystem(pow(2, i));
        }

        vector<byte> response{ResponseServiceID, pid, (byte) state, (byte) state};
        handler = doTest(request, response);
        EXPECT_EQ(handler->getVehicle()->getFuelSystemStates().getFuelSystem1().getValue(), state);
        EXPECT_EQ(handler->getVehicle()->getFuelSystemStates().getFuelSystem2().getValue(), state);

        vector<byte> response2{ResponseServiceID, pid, (byte) state, (byte) 0};
        handler = doTest(request, response2);
        EXPECT_EQ(handler->getVehicle()->getFuelSystemStates().getFuelSystem1().getValue(), state);
        EXPECT_EQ(handler->getVehicle()->getFuelSystemStates().getFuelSystem2().getValue(),
                  StateOfFuelSystemDoesNotExist);
        handler->getVehicle()->getFuelSystemStates().getFuelSystem2().setValue(state);
        doTest(request, response);

        vector<byte> response3{ResponseServiceID, pid, (byte) 0, (byte) state};
        handler = doTest(request, response3);
        EXPECT_EQ(handler->getVehicle()->getFuelSystemStates().getFuelSystem1().getValue(),
                  StateOfFuelSystemDoesNotExist);
        EXPECT_EQ(handler->getVehicle()->getFuelSystemStates().getFuelSystem2().getValue(), state);
        handler->getVehicle()->getFuelSystemStates().getFuelSystem1().setValue(state);
        doTest(request, response);
    }
}

TEST(OBDHandler, PID_06_To_9_FuelTrimBanks) {
    vector<Service1Pids> pids{ShortTermFuelTrimBank1, LongTermFuelTrimBank1,
                              ShortTermFuelTrimBank2, LongTermFuelTrimBank2};

    for (auto &pid: pids) {
        vector<byte> request{(RequestServiceID), (byte) pid};
        vector<byte> response{ResponseServiceID, (byte) pid, (byte) 0x00};
        auto handler = doTest(request, response);

        auto &engine = handler->getVehicle()->getEngine();
        switch (pid) {
            case ShortTermFuelTrimBank1:
                EXPECT_EQ(engine.getShortTermFuelTrimBank1().getValue(), -100);
                break;
            case LongTermFuelTrimBank1:
                EXPECT_EQ(engine.getLongTermFuelTrimBank1().getValue(), -100);
                break;
            case ShortTermFuelTrimBank2:
                EXPECT_EQ(engine.getShortTermFuelTrimBank2().getValue(), -100);
                break;
            case LongTermFuelTrimBank2:
                EXPECT_EQ(engine.getLongTermFuelTrimBank2().getValue(), -100);
                break;
        }

        handler = getHandler();
        auto &engine2 = handler->getVehicle()->getEngine();
        switch (pid) {
            case ShortTermFuelTrimBank1:
                engine.getShortTermFuelTrimBank1().setValue(40);
                EXPECT_EQ(ceil(engine.getShortTermFuelTrimBank1().getValue()), 40);
                break;
            case LongTermFuelTrimBank1:
                engine.getLongTermFuelTrimBank1().setValue(40);
                EXPECT_EQ(ceil(engine.getLongTermFuelTrimBank1().getValue()), 40);
                break;
            case ShortTermFuelTrimBank2:
                engine.getShortTermFuelTrimBank2().setValue(40);
                EXPECT_EQ(ceil(engine.getShortTermFuelTrimBank2().getValue()), 40);
                break;
            case LongTermFuelTrimBank2:
                engine.getLongTermFuelTrimBank2().setValue(40);
                EXPECT_EQ(ceil(engine.getLongTermFuelTrimBank2().getValue()), 40);
                break;
        }
    }
}


TEST(OBDHandler, PID_12_CommandedSecondaryAirStatus) {
    const auto pid = (byte) CommandedSecondaryAirStatus;
    vector<byte> request{(RequestServiceID), pid};

    vector<byte> response{ResponseServiceID, pid, (byte) 0x02};
    auto handler = doTest(request, response);

    auto &vehicle = *handler->getVehicle();
    auto &system = vehicle.getCommandedSecondaryAirStatus();
    EXPECT_FLOAT_EQ(system.getValue(), ClosedLoopUsingOxygenSensor);

    vector<StateOfCommandedSecondaryAir> values{CommandedSecondaryAirStatusDoesNotExist,
                                                Upstream,
                                                DownstreamOfCatalyticConverter,
                                                FromTheOutsideAtmosphereOrOff,
                                                PumpCommandedOnForDiagnostics};
    for (auto const &val: values) {
        system.setValue(val);
        EXPECT_FLOAT_EQ(system.getValue(), val);
    }
}

TEST(OBDHandler, PID_13_OxygenSensorsPresent) {
    const auto pid = (byte) OxygenSensorsPresent;
    vector<byte> request{(RequestServiceID), pid};
    vector<byte> response{ResponseServiceID, pid, (byte) 0xca};
    auto handler = doTest(request, response);

    auto &vehicle = *handler->getVehicle();
    auto &system = vehicle.getOxygenSystem().getBankOxygenSensorsCollection();

    // [A0..A3] == Bank 1, Sensors 1-4.
    // [A4..A7] == Bank 2, Sensors 1-4.
    // BitIndex 76543210
    // 0xca =   11001010
    EXPECT_EQ(system.getBank1Sensor1present().getValue(), false);
    EXPECT_EQ(system.getBank1Sensor2present().getValue(), true);
    EXPECT_EQ(system.getBank1Sensor3present().getValue(), false);
    EXPECT_EQ(system.getBank1Sensor4present().getValue(), true);
    EXPECT_EQ(system.getBank2Sensor1present().getValue(), false);
    EXPECT_EQ(system.getBank2Sensor2present().getValue(), false);
    EXPECT_EQ(system.getBank2Sensor3present().getValue(), true);
    EXPECT_EQ(system.getBank2Sensor4present().getValue(), true);
}

TEST(OBDHandler, PID_13_OxygenSensorsPresentSetter) {
    auto handler = getHandler();

    auto &vehicle = *handler->getVehicle();
    auto &system = vehicle.getOxygenSystem().getBankOxygenSensorsCollection();

    system.getBank1Sensor1present().setValue(false);
    system.getBank1Sensor2present().setValue(true);
    system.getBank1Sensor3present().setValue(false);
    system.getBank1Sensor4present().setValue(true);
    system.getBank2Sensor1present().setValue(false);
    system.getBank2Sensor2present().setValue(false);
    system.getBank2Sensor3present().setValue(true);
    system.getBank2Sensor4present().setValue(true);


    EXPECT_EQ(system.getBank1Sensor1present().getValue(), false);
    EXPECT_EQ(system.getBank1Sensor2present().getValue(), true);
    EXPECT_EQ(system.getBank1Sensor3present().getValue(), false);
    EXPECT_EQ(system.getBank1Sensor4present().getValue(), true);
    EXPECT_EQ(system.getBank2Sensor1present().getValue(), false);
    EXPECT_EQ(system.getBank2Sensor2present().getValue(), false);
    EXPECT_EQ(system.getBank2Sensor3present().getValue(), true);
    EXPECT_EQ(system.getBank2Sensor4present().getValue(), true);
}

TEST(OBDHandler, PID_14_to_0x1B_BankOxygenSensor1_to_8) {
    // tested together because same logic with other pids
    const vector<Service1Pids> pids = {
            BankOxygenSensor1, BankOxygenSensor2, BankOxygenSensor3, BankOxygenSensor4,
            BankOxygenSensor5, BankOxygenSensor6, BankOxygenSensor7, BankOxygenSensor8};

    for (const auto &pid: pids) {
        vector<byte> request{(RequestServiceID), (byte) pid};
        vector<byte> response{ResponseServiceID, (byte) pid, (byte) 0xca, (byte) 0xfe};
        auto handler = doTest(request, response);


        auto &oxygenSystem = handler->getVehicle()->getOxygenSystem();
        BankOxygenSensor *sensor;
        switch (pid) {
            case BankOxygenSensor1:
                sensor = &oxygenSystem.getBankOxygenSensor1();
                break;
            case BankOxygenSensor2:
                sensor = &oxygenSystem.getBankOxygenSensor2();
                break;
            case BankOxygenSensor3:
                sensor = &oxygenSystem.getBankOxygenSensor3();
                break;
            case BankOxygenSensor4:
                sensor = &oxygenSystem.getBankOxygenSensor4();
                break;
            case BankOxygenSensor5:
                sensor = &oxygenSystem.getBankOxygenSensor5();
                break;
            case BankOxygenSensor6:
                sensor = &oxygenSystem.getBankOxygenSensor6();
                break;
            case BankOxygenSensor7:
                sensor = &oxygenSystem.getBankOxygenSensor7();
                break;
            case BankOxygenSensor8:
                sensor = &oxygenSystem.getBankOxygenSensor8();
                break;
            default:
                EXPECT_EQ(false, true);
                continue;
        }

        EXPECT_FLOAT_EQ(sensor->getVoltage().getValue(), (float) 0xca / 200);
        EXPECT_TRUE(sensor->isSensorUsedInTrimCalc());
        EXPECT_FLOAT_EQ(sensor->getShortTermFuelTrim().getValue(), (100.0f / 128.0f) * 0xfe - 100);

        sensor->getVoltage().setValue(1.275);
        EXPECT_FLOAT_EQ(sensor->getVoltage().getValue(), 1.275);

        sensor->getShortTermFuelTrim().setValue(-42.1875f);
        EXPECT_FLOAT_EQ(sensor->getShortTermFuelTrim().getValue(), -42.1875);
    }
}


TEST(OBDHandler, PID_1D_OxygenSensorsPresent4Banks) {
    const auto pid = (byte) OxygenSensorsPresent4Banks;
    vector<byte> request{(RequestServiceID), pid};
    vector<byte> response{ResponseServiceID, pid, (byte) 0xca};
    auto handler = doTest(request, response);

    auto &vehicle = *handler->getVehicle();
    auto &system = vehicle.getOxygenSystem().getBankOxygenSensor4BankCollection();

    // [A0..A3] == Bank 1, Sensors 1-4.
    // [A4..A7] == Bank 2, Sensors 1-4.
    // BitIndex 76543210
    // 0xca =   11001010
    EXPECT_EQ(system.getBank1Sensor1presentIn4Banks().getValue(), false);
    EXPECT_EQ(system.getBank1Sensor2presentIn4Banks().getValue(), true);
    EXPECT_EQ(system.getBank2Sensor1presentIn4Banks().getValue(), false);
    EXPECT_EQ(system.getBank2Sensor2presentIn4Banks().getValue(), true);
    EXPECT_EQ(system.getBank3Sensor1presentIn4Banks().getValue(), false);
    EXPECT_EQ(system.getBank3Sensor2presentIn4Banks().getValue(), false);
    EXPECT_EQ(system.getBank4Sensor1presentIn4Banks().getValue(), true);
    EXPECT_EQ(system.getBank4Sensor2presentIn4Banks().getValue(), true);
}

TEST(OBDHandler, PID_1D_OxygenSensorsPresent4Banks_Setter) {
    auto handler = getHandler();

    auto &vehicle = *handler->getVehicle();
    auto &system = vehicle.getOxygenSystem().getBankOxygenSensor4BankCollection();

    system.getBank1Sensor1presentIn4Banks().setValue(false);
    system.getBank1Sensor2presentIn4Banks().setValue(true);
    system.getBank2Sensor1presentIn4Banks().setValue(false);
    system.getBank2Sensor2presentIn4Banks().setValue(true);
    system.getBank3Sensor1presentIn4Banks().setValue(false);
    system.getBank3Sensor2presentIn4Banks().setValue(false);
    system.getBank4Sensor1presentIn4Banks().setValue(true);
    system.getBank4Sensor2presentIn4Banks().setValue(true);


    EXPECT_EQ(system.getBank1Sensor1presentIn4Banks().getValue(), false);
    EXPECT_EQ(system.getBank1Sensor2presentIn4Banks().getValue(), true);
    EXPECT_EQ(system.getBank2Sensor1presentIn4Banks().getValue(), false);
    EXPECT_EQ(system.getBank2Sensor2presentIn4Banks().getValue(), true);
    EXPECT_EQ(system.getBank3Sensor1presentIn4Banks().getValue(), false);
    EXPECT_EQ(system.getBank3Sensor2presentIn4Banks().getValue(), false);
    EXPECT_EQ(system.getBank4Sensor1presentIn4Banks().getValue(), true);
    EXPECT_EQ(system.getBank4Sensor2presentIn4Banks().getValue(), true);
}


TEST(OBDHandler, PID_1C_Supported_Standards) {
    const auto pid = (byte) OBDStandardsVehicleConformsTo;
    vector<byte> request{(RequestServiceID), pid};

    vector<byte> response{ResponseServiceID, pid, (byte) 0xca, (byte) 0x00, (byte) 0x00, (byte) 0x00};
    auto handler = doTest(request, response);

    auto &vehicle = *handler->getVehicle();
    auto &compliance = vehicle.getOBDCompliance();

    PID_1C_Supported_Standards_Setter(false, compliance);
    PID_1C_Supported_Standards_Setter(true, compliance);
}


TEST(OBDHandler, PID_24_to_0x2B_FuelRailOxygenSensor1_to_8) {
    // tested together because same logic with other pids
    const vector<Service1Pids> pids = {
            FuelRailOxygenSensor1, FuelRailOxygenSensor2, FuelRailOxygenSensor3, FuelRailOxygenSensor4,
            FuelRailOxygenSensor5, FuelRailOxygenSensor6, FuelRailOxygenSensor7, FuelRailOxygenSensor8};

    for (const auto &pid: pids) {
        vector<byte> request{(RequestServiceID), (byte) pid};
        vector<byte> response{ResponseServiceID, (byte) pid, (byte) 0xca, (byte) 0xfe, (byte) 0xba, (byte) 0xbe};
        auto handler = doTest(request, response);


        auto &oxygenSystem = handler->getVehicle()->getOxygenSystem();
        FuelRailOxygenSensor *sensor;
        switch (pid) {
            case FuelRailOxygenSensor1:
                sensor = &oxygenSystem.getFuelRailOxygenSensor1();
                break;
            case FuelRailOxygenSensor2:
                sensor = &oxygenSystem.getFuelRailOxygenSensor2();
                break;
            case FuelRailOxygenSensor3:
                sensor = &oxygenSystem.getFuelRailOxygenSensor3();
                break;
            case FuelRailOxygenSensor4:
                sensor = &oxygenSystem.getFuelRailOxygenSensor4();
                break;
            case FuelRailOxygenSensor5:
                sensor = &oxygenSystem.getFuelRailOxygenSensor5();
                break;
            case FuelRailOxygenSensor6:
                sensor = &oxygenSystem.getFuelRailOxygenSensor6();
                break;
            case FuelRailOxygenSensor7:
                sensor = &oxygenSystem.getFuelRailOxygenSensor7();
                break;
            case FuelRailOxygenSensor8:
                sensor = &oxygenSystem.getFuelRailOxygenSensor8();
                break;
            default:
                EXPECT_EQ(false, true);
                continue;
        }

        EXPECT_FLOAT_EQ(sensor->getFuelAirEquivalenceRatio().getValue(), (2.0f / 65536) * (256 * 0xca + 0xfe));
        EXPECT_FLOAT_EQ(sensor->getVoltage().getValue(), (8.0f / 65536) * (256 * 0xba + 0xbe));

        // min
        float value = 0.0f;
        sensor->getFuelAirEquivalenceRatio().setValue(value);
        EXPECT_FLOAT_EQ(sensor->getFuelAirEquivalenceRatio().getValue(), value);
        sensor->getVoltage().setValue(value);
        EXPECT_FLOAT_EQ(sensor->getVoltage().getValue(), value);

        value = 1.2f;
        sensor->getFuelAirEquivalenceRatio().setValue(value);
        EXPECT_NEAR(sensor->getFuelAirEquivalenceRatio().getValue(), value, 0.1);
        sensor->getVoltage().setValue(value);
        EXPECT_NEAR(sensor->getVoltage().getValue(), value, 0.1f);

        // max
        value = 1.9999f;
        sensor->getFuelAirEquivalenceRatio().setValue(value);
        EXPECT_NEAR(sensor->getFuelAirEquivalenceRatio().getValue(), value, 0.1f);

        value = 7.9999f;
        sensor->getVoltage().setValue(value);
        EXPECT_NEAR(sensor->getVoltage().getValue(), value, 0.1f);
    }
}


TEST(OBDHandler, PID_1E_AuxiliaryInputStatus) {
    const auto pid = (byte) AuxiliaryInputStatus;
    vector<byte> request{(RequestServiceID), pid};

    vector<byte> response{ResponseServiceID, pid, (byte) 0x01};
    auto handler = doTest(request, response);

    auto &vehicle = *handler->getVehicle();
    auto &system = vehicle.getAuxiliaryInputStatus();
    EXPECT_TRUE(system.getValue());

    system.setValue(false);
    EXPECT_FALSE(system.getValue());

    system.setValue(true);
    EXPECT_TRUE(system.getValue());
}

