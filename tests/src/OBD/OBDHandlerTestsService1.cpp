#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by me on 14/12/18.
//


#include "../../../src/Config.h"
#include "OBDHandlerTest.h"
#include "../../../src/common/endian.h"
#include "gtest/gtest.h"

const byte RequestServiceID = (byte) 0x01;
const byte ResponseServiceID = (byte) 0x41;

TEST(OBDHandler, PID_0_PIDSupported01_20) {
    auto const pid = (byte) 0x00;
    vector<byte> request{RequestServiceID, pid};
    vector<byte> response{ResponseServiceID, pid, (byte) 0xbe, (byte) 0x7e, (byte) 0xb8, (byte) 0x13};
    doTest(request, response);
}

TEST(OBDHandler, PID_0_PIDSupported01_20_Single) {
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

    byte *val = handler->createAnswerFrame(request.data());
    compareResponse(response, val);
}

TEST(OBDHandler, PID_0_PIDSupported01_20_Setter) {
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


    byte *val = handler->createAnswerFrame(request.data());
    compareResponse(response, val);
}

TEST(OBDHandler, PID_0_PIDSupportedGeneric) {
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
            byte *val = handler->createAnswerFrame(request.data());
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



TEST(OBDHandler, PID_1_MonitoringStatus) {
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
    const auto pid = (byte) 0x01;
    vector<byte> request{(RequestServiceID), pid};
    vector<byte> response{ResponseServiceID, pid, (byte) 0xf1, (byte) 0x67, (byte) 0xe3, (byte) 0xf1};
    // do test will check the can response.
    auto handler = doTest(request, response);
    MonitorStatus &monitoringStatus = handler->getVehicle()->getMonitorStatus();

    // validate object state
    EXPECT_EQ(monitoringStatus.getMil(), true);
    EXPECT_EQ(monitoringStatus.getDtcCount(), 113);

    EXPECT_EQ(monitoringStatus.getComponents().getAvailable().getValue(), true);
    EXPECT_EQ(monitoringStatus.getComponents().getIncomplete().getValue(), true);

    EXPECT_EQ(monitoringStatus.getFuelSystem().getAvailable().getValue(), true);
    EXPECT_EQ(monitoringStatus.getFuelSystem().getIncomplete().getValue(), true);

    EXPECT_EQ(monitoringStatus.getMisfire().getAvailable().getValue(), true);
    EXPECT_EQ(monitoringStatus.getMisfire().getIncomplete().getValue(), false);

    Engine &engine = monitoringStatus.getEngine();
    EXPECT_EQ(engine.getEngineType(), PETROL);

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


// make sure that the application can generate the request on its own and does not need can frames to init.
TEST(OBDHandler, PID_1_Test_MIL) {
    OBDHandler *handler = getHandler();
    MonitorStatus &monitoringStatus = handler->getVehicle()->getMonitorStatus();
    // validate object state
    monitoringStatus.setMil(true);
    const auto pid = (byte) 0x01;
    vector<byte> request{(RequestServiceID), pid};
    byte *val = handler->createAnswerFrame(request.data());
    vector<byte> response{ResponseServiceID, pid, (byte) 0x80, (byte) 0x00, (byte) 0x00, (byte) 0x00};
    compareResponse(response, val);

}

// make sure that the application can generate the request on its own and does not need can frames to init.
TEST(OBDHandler, PID_1_MonitoringStatusInitViaVehicle) {
    OBDHandler *handler = getHandler();
    MonitorStatus &monitoringStatus = handler->getVehicle()->getMonitorStatus();

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
    byte *val = handler->createAnswerFrame(request.data());
    vector<byte> response{ResponseServiceID, pid, (byte) 0xf1, (byte) 0x6f, (byte) 0xe3, (byte) 0xf1};
    compareResponse(response, val);
}

TEST(OBDHandler, PID_2_FreezeDTC) {
    const auto pid = (byte) FreezeDTCPid;
    vector<byte> request{(RequestServiceID), pid};
    vector<byte> response{ResponseServiceID, pid, (byte) 0xe5, (byte) 0x00};
    auto handler = doTest(request, response);

    auto code = handler->getVehicle()->getFreezeDTC().getValue();

    EXPECT_EQ("U2500", code.getSaeId());
    EXPECT_EQ("(CAN) Lack of Acknowledgement From Engine Management", code.getDescription());
    EXPECT_EQ(0xe500, code.getCanId());
}

TEST(OBDHandler, PID_2_FreezeDTC_Setter) {
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


TEST(OBDHandler, PID_3_FuelSystemState) {
    const auto pid = (byte) FuelSystemStatus;
    vector<byte> request{(RequestServiceID), pid};
    OBDHandler *handler;
    int i;
    for (i = -1; i <= 4; i++) {
        StateOfFuelSystem state;
        if (-1 == i) {
            state = DoesNotExist;
        } else {
            state = StateOfFuelSystem(pow(2, i));
        }

        vector<byte> response{ResponseServiceID, pid, (byte) state, (byte) state};
        handler = doTest(request, response);
        EXPECT_EQ(handler->getVehicle()->getFuelSystem1().getValue(), state);
        EXPECT_EQ(handler->getVehicle()->getFuelSystem2().getValue(), state);

        vector<byte> response2{ResponseServiceID, pid, (byte) state, (byte) 0};
        handler = doTest(request, response2);
        EXPECT_EQ(handler->getVehicle()->getFuelSystem1().getValue(), state);
        EXPECT_EQ(handler->getVehicle()->getFuelSystem2().getValue(), DoesNotExist);
        handler->getVehicle()->getFuelSystem2().setValue(state);
        doTest(request, response);

        vector<byte> response3{ResponseServiceID, pid, (byte) 0, (byte) state};
        handler = doTest(request, response3);
        EXPECT_EQ(handler->getVehicle()->getFuelSystem1().getValue(), DoesNotExist);
        EXPECT_EQ(handler->getVehicle()->getFuelSystem2().getValue(), state);
        handler->getVehicle()->getFuelSystem1().setValue(state);
        doTest(request, response);
    }
}

TEST(OBDHandler, PID_4_CalculatedEngineLoad) {
    const auto pid = (byte) CalculatedEngineLoad;
    vector<byte> request{(RequestServiceID), pid};
    vector<byte> response{ResponseServiceID, pid, (byte) 0x6b};
    auto handler = doTest(request, response);

    auto &engine = handler->getVehicle()->getEngine();
    EXPECT_EQ(ceil(engine.getLoad().getValue()), 42);
}

TEST(OBDHandler, PID_4_CalculatedEngineLoadSetter) {
    // no setting via can frame
    const auto pid = (byte) CalculatedEngineLoad;
    vector<byte> request{(RequestServiceID), pid};
    vector<byte> response{ResponseServiceID, pid, (byte) 0x6b};

    OBDHandler *handler = getHandler();
    auto &engine = handler->getVehicle()->getEngine();
    engine.getLoad().setValue(42);
    EXPECT_EQ(ceil(engine.getLoad().getValue()), 42);
}


TEST(OBDHandler, PID_5_EngineCooleantTemp) {
    const auto pid = (byte) EngineCoolantTemperature;
    vector<byte> request{(RequestServiceID), pid};
    vector<byte> response{ResponseServiceID, pid, (byte) 0x00};
    auto handler = doTest(request, response);

    auto &engine = handler->getVehicle()->getEngine();
    EXPECT_EQ(engine.getCoolantTemperature().getValue(), -40);
}

TEST(OBDHandler, PID_5_EngineCooleantTempSetter) {
    // no setting via can frame
    const auto pid = (byte) EngineCoolantTemperature;
    vector<byte> request{(RequestServiceID), pid};
    vector<byte> response{ResponseServiceID, pid, (byte) 0x00};

    OBDHandler *handler = getHandler();
    auto &engine = handler->getVehicle()->getEngine();
    engine.getCoolantTemperature().setValue(-40);
    EXPECT_EQ(ceil(engine.getCoolantTemperature().getValue()), -40);
}

TEST(OBDHandler, PID_6_To_9_FuelTrimBanks) {
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

TEST(OBDHandler, PID_A_FuelPressure) {
    const auto pid = (byte) FuelPressure;
    vector<byte> request{(RequestServiceID), pid};
    vector<byte> response{ResponseServiceID, pid, (byte) 0xff};
    auto handler = doTest(request, response);

    auto &engine = handler->getVehicle()->getEngine();
    EXPECT_EQ(engine.getFuelPressure().getValue(), (0xff) * 3);

    engine.getFuelPressure().setValue(30);
    EXPECT_EQ((int) engine.getFuelPressure().getValue(), 30);
}

TEST(OBDHandler, PID_B_IntakeManifoldAbsolutePressure) {
    const auto pid = (byte) IntakeManifoldAbsolutePressure;
    vector<byte> request{(RequestServiceID), pid};
    vector<byte> response{ResponseServiceID, pid, (byte) 42};
    auto handler = doTest(request, response);

    auto &engine = handler->getVehicle()->getEngine();
    EXPECT_EQ((int) engine.getIntakeManifoldAbsolutePressure().getValue(), 42);

    engine.getIntakeManifoldAbsolutePressure().setValue((byte) 84);
    EXPECT_EQ((int) engine.getIntakeManifoldAbsolutePressure().getValue(), 84);
}







/*


5
6
7
8
9
0A
0B
0C
0D
0E
0F
10
11
12
13
14
15
16
17
18
19
1A
1B
1C
1D
1E
1F
20
21
22
23
24
25
26
27
28
29
2A
2B
2C
2D
2E
2F
30
31
32
33
34
35
36
37
38
39
3A
3B
3C
3D
3E
3F
40
41
42
43
44
45
46
47
48
49
4A
4B
4C
4D
4E
4F
50
51
52
53
54
55
56
57
58
59
5A
5B
5C
5D
5E
5F
60
61
62
63
64
65
66
67
68
69
6A
6B
6C
6D
6E
6F
70
71
72
73
74
75
76
77
78
79
7A
7B
7C
7D
7E
7F
80
81
82
83
84
85
86
87
88
89
8A
8B
8C
8D
8E
8F
90
91
92
93
94
98
99
9A
9B
9C
9D
9E
9F
A0
A1
A2
A3
A4
A5
A6
C0
C3
C4
*/
#pragma clang diagnostic pop