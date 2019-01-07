//
// Created by me on 14/12/18.
//


#include "../../../src/Config.h"
#include "OBDHandlerTest.h"
#include "../../../src/common/endian.h"
#include "gtest/gtest.h"
#include <random>

void checkDataCollection(DataObjectStateCollection co, ErrorType state) {
    for (const auto &doe : co.resultSet) {
        EXPECT_EQ(doe.type, state);
    }
}

template<class T>
OBDHandler *genericTest(Service1Pids pid, unsigned int &value) {
    vector<byte> response;
    vector<byte> request{(RequestServiceID), (byte) pid};
    if (sizeof(T) == sizeof(byte)) {
        response = {ResponseServiceID, (byte) pid, (byte) 0xca};
        value = 0xca;
    } else if (sizeof(T) == sizeof(short)) {
        response = {ResponseServiceID, (byte) pid, (byte) 0xca, (byte) 0xfe};
        value = 0xcafe;
    } else if (sizeof(T) == sizeof(int)) {
        response = {ResponseServiceID, (byte) pid, (byte) 0xca, (byte) 0xfe, (byte) 0xba, (byte) 0xbe};
        value = 0xcafebabe;
    }

    auto handler = doTest(request, response);
    return handler;
}


template<class T>
void dataTest(IDataObject<T> *system, vector<pair<T, ErrorType>> values, float offset) {
    for (auto const &val: values) {
        EXPECT_EQ(system->setValue(val.first).type, val.second);
        if (val.second == SUCCESS) {
            EXPECT_NEAR(system->getValue(), val.first, offset);
        }

        checkDataCollection(system->setValueFromString(to_string(val.first)), val.second);
        if (val.second == SUCCESS) {
            EXPECT_NEAR(system->getValue(), val.first, offset);
        }
    }

    EXPECT_GT(system->getDescriptions().size(), 0);
}



template<class T, class S>
void TestCalculatedData(Service1Pids pid,
                        function<CalculatedDataObject<T, S> *(Vehicle &vehicle)> dataCallback,
                        float offset, function<S(int)> dataConversion) {

    unsigned int value = 0;
    auto &vehicle = *genericTest<T>(pid, value)->getVehicle();
    auto system = dataCallback(vehicle);
    if (nullptr != dataConversion) {
        EXPECT_FLOAT_EQ(system->getValue(), dataConversion(value));
    }

    vector<pair<S, ErrorType>> values{
            {((S) system->getDescriptions().at(0)->getMin()),             SUCCESS},
            {(S) ((S) system->getDescriptions().at(0)->getMax() - 0.001), SUCCESS},
            {(S) ((S) system->getDescriptions().at(0)->getMax() / 2),     SUCCESS},
            {(S) ((S) system->getDescriptions().at(0)->getMax() / 3),     SUCCESS},
            {(S) ((S) system->getDescriptions().at(0)->getMax() / 4),     SUCCESS},
            {(S) ((S) system->getDescriptions().at(0)->getMax() / 5),     SUCCESS},
    };

    dataTest<S>(system, values, offset);
}


template<class T>
void TestDataObject(Service1Pids pid,
                    function<DataObject<T> *(Vehicle &vehicle)> dataCallback,
                    float offset = 0, function<T(int)> dataConversion = nullptr) {
    unsigned int value = 0;
    auto &vehicle = *genericTest<T>(pid, value)->getVehicle();
    auto system = dataCallback(vehicle);
    if (nullptr != dataConversion) {
        EXPECT_EQ(system->getValue(), dataConversion(value));
    }

    vector<pair<T, ErrorType>> values;
        values = {
                {(T) (system->getDescriptions().at(0)->getMin()),         SUCCESS},
                {(T) (system->getDescriptions().at(0)->getMax()),         SUCCESS},
                {(T) (system->getDescriptions().at(0)->getMax() / (T) 2), SUCCESS},
                {(T) (system->getDescriptions().at(0)->getMax() / (T) 3), SUCCESS},
                {(T) (system->getDescriptions().at(0)->getMax() / (T) 4), SUCCESS},
                {(T) (system->getDescriptions().at(0)->getMax() / (T) 5), SUCCESS}};

    dataTest<T>(system, values, offset);
}

template<>
void TestDataObject<byte>(Service1Pids pid,
                          function<DataObject<byte> *(Vehicle &vehicle)> dataCallback,
                          float offset, function<byte(int)> dataConversion) {
    vector<byte> request{(RequestServiceID), (byte) pid};

    vector<byte> response = {ResponseServiceID, (byte) pid, (byte) 0xca};;
    unsigned int value = 0xca;;


    auto handler = doTest(request, response);

    auto &vehicle = *handler->getVehicle();
    auto system = dataCallback(vehicle);
    if (nullptr != dataConversion) {
        EXPECT_EQ(system->getValue(), dataConversion(value));
    }

    vector<pair<byte, ErrorType>> values{
            {(byte) (system->getDescriptions().at(0)->getMin()),           SUCCESS},
            {(byte) (system->getDescriptions().at(0)->getMax()),           SUCCESS},
            {(byte) ((int) system->getDescriptions().at(0)->getMax() / 2), SUCCESS},
            {(byte) ((int) system->getDescriptions().at(0)->getMax() / 3), SUCCESS},
            {(byte) ((int) system->getDescriptions().at(0)->getMax() / 4), SUCCESS},
            {(byte) ((int) system->getDescriptions().at(0)->getMax() / 5), SUCCESS}};
    for (auto const &val: values) {
        EXPECT_EQ(system->setValue(val.first).type, val.second);
        if (val.second == SUCCESS) {
            EXPECT_NEAR((double) system->getValue(), (double) val.first, offset);
        }

        checkDataCollection(system->setValueFromString(to_string(val.first)), val.second);
        if (val.second == SUCCESS) {
            EXPECT_NEAR((double) system->getValue(), (double) val.first, offset);
        }
    }
}
//
//template<>
//void TestDataObject<bool>(Service1Pids pid,
//                          function<DataObject<bool> *(Vehicle &vehicle)> dataCallback,
//                          float offset, function<bool(int)> dataConversion) {
//    vector<byte> request{(RequestServiceID), (byte) pid};
//
//    vector<byte> response = {ResponseServiceID, (byte) pid, (byte) 0xca};;
//    unsigned int value = 0xca;;
//
//
//    auto handler = doTest(request, response);
//
//    auto &vehicle = *handler->getVehicle();
//    auto system = dataCallback(vehicle);
//    if (nullptr != dataConversion) {
//        EXPECT_EQ(system->getValue(), dataConversion(value));
//    }
//
//    vector<pair<bool, ErrorType>>
//            values{{false, SUCCESS},
//                   {true,  SUCCESS},
//                   {false, SUCCESS},
//                   {true,  SUCCESS}};
//    dataTest<bool>(system, values, offset);
//}
//


TEST(OBDHandler, PID_0A_FuelPressure) {

    function<CalculatedDataObject<byte, unsigned short> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getEngine().getFuelPressure(); };

    function<unsigned short(int)> dc = [](int value) { return value * 3; };

    TestCalculatedData(FuelPressure, cb, 3, dc);
}

TEST(OBDHandler, PID_0B_IntakeManifoldAbsolutePressure) {
    function<DataObject<byte> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getEngine().getIntakeManifoldAbsolutePressure(); };

    function<byte(int)> dc = [](int value) { return (byte) value; };

    TestDataObject(IntakeManifoldAbsolutePressure, cb, 0, dc);
}

TEST(OBDHandler, PID_0C_EngineRPM) {
    function<CalculatedDataObject<unsigned short, float> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getEngine().getEngineRPM(); };

    function<float(int)> dc = [](int value) { return (float) value / 4; };

    TestCalculatedData(EngineRPM, cb, 4, dc);
}


TEST(OBDHandler, PID_0D_TestSpeed) {
    function<DataObject<byte> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getSpeed(); };

    function<byte(int)> dc = [](int value) { return (byte) 0xca; };

    TestDataObject(VehicleSpeed, cb, 0, dc);
}

TEST(OBDHandler, PID_0E_TimingAdvance) {

    function<CalculatedDataObject<byte, float> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getEngine().getTimingAdvance(); };

    function<float(int)> dc = [](int value) { return 37; };

    TestCalculatedData(TimingAdvance, cb, 1, dc);
}

TEST(OBDHandler, PID_0F_IntakeAirTemperature) {
    function<CalculatedDataObject<byte, short> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getEngine().getIntakeAirTemperature(); };

    function<short(int)> dc = [](int value) { return 162; };

    TestCalculatedData(IntakeAirTemperature, cb, 0, dc);
}

TEST(OBDHandler, PID_10_MAFAirFlowRate) {
    function<CalculatedDataObject<unsigned short, float> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getEngine().getMAFAirFlowRate(); };

    function<float(int)> dc = [](int value) { return ((float) value / 100); };

    TestCalculatedData(MAFAirFlowRate, cb, 2, dc);
}


TEST(OBDHandler, PID_11_ThrottlePosition) {
    function<CalculatedDataObject<byte, float> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getThrottle().getThrottlePosition(); };

    function<float(int)> dc = [](int value) { return 100.0f / 255 * value; };

    TestCalculatedData(ThrottlePosition, cb, 0.5, dc);
}


TEST(OBDHandler, PID_04_CalculatedEngineLoad) {

    function<CalculatedDataObject<byte, float> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getEngine().getLoad(); };

    function<float(int)> dc = [](int value) { return 100.0 / 255.0 * value; };

    TestCalculatedData(CalculatedEngineLoad, cb, 0.5f, dc);

}


TEST(OBDHandler, PID_05_EngineCooleantTemp) {

    function<CalculatedDataObject<byte, short> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getEngine().getCoolantTemperature(); };

    function<short(int)> dc = [](int value) { return value - 40; };

    TestCalculatedData(EngineCoolantTemperature, cb, 0, dc);
}


TEST(OBDHandler, PID_1F_RunTimeSinceEngineStart) {
    function<DataObject<unsigned short> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getRunTimeSinceEngineStart(); };

    TestDataObject(RunTimeSinceEngineStart, cb);
}

TEST(OBDHandler, PID_21_DistanceTraveledWithMilOn) {
    function<DataObject<unsigned short> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getDistanceTraveledWithMilOn(); };

    TestDataObject(DistanceTraveledWithMilOn, cb);
}

TEST(OBDHandler, PID_22_FuelRailPressure) {

    function<CalculatedDataObject<unsigned short, float> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getFuelRailPressure(); };

    function<float(int)> dc = [](int value) {
        return (float) (0.079 * value);
    };

    TestCalculatedData(FuelRailPressure, cb, 20, dc);
}


TEST(OBDHandler, PID_23_FuelRailGaugePressure) {

    function<CalculatedDataObject<unsigned short, unsigned int> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getFuelRailGaugePressure(); };

    function<unsigned int(int)> dc = [](int value) {
        return (unsigned int) (10 * value);
    };

    TestCalculatedData(FuelRailGaugePressure, cb, 10, dc);
}

TEST(OBDHandler, PID_2C_CommandedEGR) {

    function<CalculatedDataObject<byte, float> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getCommandedEGR(); };

    function<float(int)> dc = [](int value) { return 100.0 / 255.0 * 0xca; };

    TestCalculatedData(CommandedEGR, cb, 0.5, dc);
}

TEST(OBDHandler, PID_2D_EGRError) {
    function<CalculatedDataObject<byte, float> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getEGRError(); };

    function<float(int)> dc = [](int value) { return 100.0 / 128 * 0xca - 100; };

    TestCalculatedData(EGRError, cb, 0.8, dc);
}

TEST(OBDHandler, PID_2E_CommandedEvaporativePurge) {
    function<CalculatedDataObject<byte, float> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getCommandedEvaporativePurge(); };

    function<float(int)> dc = [](int value) { return 100.0 / 255.0 * 0xca; };

    TestCalculatedData(CommandedEvaporativePurge, cb, 0.5, dc);
}

TEST(OBDHandler, PID_2F_FuelTankLevelInput) {
    function<CalculatedDataObject<byte, float> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getFuelTankLevelInput(); };

    function<float(int)> dc = [](int value) { return 100.0 / 255.0 * 0xca; };

    TestCalculatedData(FuelTankLevelInput, cb, 0.5, dc);
}

TEST(OBDHandler, PID_30_WarmUpsSinceCodesCleared) {

    function<DataObject<byte> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getWarmUpsSinceCodesCleared(); };

    TestDataObject(WarmUpsSinceCodesCleared, cb);
}

TEST(OBDHandler, PID_31_DistanceTraveledSinceCodesCleared) {
    function<DataObject<unsigned short> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getDistanceTraveledSinceCodesCleared(); };

    TestDataObject(DistanceTraveledSinceCodesCleared, cb);
}

TEST(OBDHandler, PID_32_EvaporativePurgeSystemVaporPressure) {
    function<CalculatedDataObject<unsigned short, float> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getEvaporativePurgeSystemVaporPressure(); };

    function<float(int)> dc = [](int value) {
        return getTwoComplement(value) / 4.0f;
    };

    TestCalculatedData(EvaporativePurgeSystemVaporPressure, cb, 0.3, dc);
}

TEST(OBDHandler, PID_33_AbsoluteBarometricPressure) {
    function<DataObject<byte> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getAbsoluteBarometricPressure(); };
    TestDataObject(AbsoluteBarometricPressure, cb);
    }


TEST(OBDHandler, PID_42_ControlModuleVoltage) {
    function<CalculatedDataObject<unsigned short, float> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getControlModuleVoltage(); };

    function<float(int)> dc = [](int value) { return (float) value / 1000; };

    TestCalculatedData(ControlModuleVoltage, cb, 0.2, dc);
}


TEST(OBDHandler, PID_43_AbsoluteLoadValue) {
    function<CalculatedDataObject<unsigned short, unsigned short> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getAbsoluteLoadValue(); };

    function<unsigned short(int)> dc = [](int value) { return (unsigned short) value * (100.0f / 255.0f); };

    TestCalculatedData(AbsoluteLoadValue, cb, 1, dc);
}

TEST(OBDHandler, PID_44_FuelAirCommandedEquivalenceRatio) {
    function<CalculatedDataObject<unsigned short, float> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getFuelAirCommandedEquivalenceRatio(); };

    function<float(int)> dc = [](int value) { return (float) value * 2 / (pow(2, 16)); };

    TestCalculatedData(FuelAirCommandedEquivalenceRatio, cb, 1, dc);
}

TEST(OBDHandler, PID_45_RelativeThrottlePosition) {
    function<CalculatedDataObject<byte, float> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getThrottle().getRelativeThrottlePosition(); };

    function<float(int)> dc = [](int value) { return (value * (100.0f / 255.0f)); };

    TestCalculatedData(RelativeThrottlePosition, cb, 1, dc);
}

TEST(OBDHandler, PID_46_AmbientAirTemperature) {
    function<CalculatedDataObject<byte, short> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getAmbientAirTemperature(); };

    function<short(int)> dc = [](int value) { return value - 40; };

    TestCalculatedData(AmbientAirTemperature, cb, 1, dc);
}


TEST(OBDHandler, PID_47_AbsoluteThrottlePositionB){
    function<CalculatedDataObject<byte,float> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getThrottle().getAbsoluteThrottlePositionB(); };

    function<float(int)> dc = [](int value) { return 100.0f / 255 * value; };

    TestCalculatedData(AbsoluteThrottlePositionB, cb, 0.5f, dc);
}
TEST(OBDHandler, PID_48_AbsoluteThrottlePositionC){
    function<CalculatedDataObject<byte, float> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getThrottle().getAbsoluteThrottlePositionC(); };

    function<float(int)> dc = [](int value) { return 100.0f / 255 * value; };

    TestCalculatedData(AbsoluteThrottlePositionC, cb, 0.5f, dc);
}
TEST(OBDHandler, PID_49_AcceleratorPedalPositionD){
    function<CalculatedDataObject<byte, float> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getThrottle().getAcceleratorPedalPositionD(); };

    function<float(int)> dc = [](int value) { return 100.0f / 255 * value; };

    TestCalculatedData(AcceleratorPedalPositionD, cb, 0.5f, dc);
}
TEST(OBDHandler, PID_4A_AcceleratorPedalPositionE){
    function<CalculatedDataObject<byte, float> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getThrottle().getAcceleratorPedalPositionE(); };

    function<float(int)> dc = [](int value) { return 100.0f / 255 * value; };

    TestCalculatedData(AcceleratorPedalPositionE, cb, 0.5f, dc);
}
TEST(OBDHandler, PID_4B_AcceleratorPedalPositionF){
    function<CalculatedDataObject<byte, float> *(Vehicle &vehicle)> cb =
            [](Vehicle &vehicle) { return &vehicle.getThrottle().getAcceleratorPedalPositionF(); };

    function<float(int)> dc = [](int value) { return 100.0f / 255 * value; };

    TestCalculatedData(AcceleratorPedalPositionF, cb, 0.5f, dc);
}


