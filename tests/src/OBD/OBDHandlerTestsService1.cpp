//
// Created by me on 14/12/18.
//


#include "../../../src/Config.h"
#include "OBDHandlerTest.h"
#include "gtest/gtest.h"

const byte RequestServiceID = (byte) 0x01;
const byte ResponseServiceID = (byte) 0x41;

TEST(OBDHandler, PID_0_PIDSupported01_20) { // NOLINT(cert-err58-cpp)
    auto const pid = (byte) 0x00;
    vector<byte> request{RequestServiceID, pid};
    vector<byte> response{ResponseServiceID, pid, (byte) 0xbe, (byte) 0x7e, (byte) 0xb8, (byte) 0x13};
    doTest(request, response);
}

TEST(OBDHandler, PID_1_MonitoringStatus) { // NOLINT(cert-err58-cpp)
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

        answer 71 F9 67 F1

     */
    const auto pid = (byte) 0x01;
    vector<byte> request{(RequestServiceID), pid};
    vector<byte> response{ResponseServiceID, pid, (byte) 0xf1, (byte) 0xf9, (byte) 0x67, (byte) 0xf1};
    auto handler = doTest(request, response);
    auto monitoringStatus = handler->getVehicle()->getMonitorStatus();
    EXPECT_EQ(monitoringStatus->getMil(), true);
    EXPECT_EQ(monitoringStatus->getDtcCount(), 113);


    auto engine = monitoringStatus->getEngine();
    EXPECT_EQ(engine->getEngineType(), PETROL);


}


/*
0
1
2
3
4
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