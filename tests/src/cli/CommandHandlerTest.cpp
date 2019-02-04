//
// Created by me on 04/01/19.
//


#include <gtest/gtest.h>
#include <vector>
#include "../../../src/ui/cli/CommandHandler.h"
#include "../../../src/communication/CanIsoTP.h"
#include "../MockCommInterface.h"
#include <random>


using namespace std;


double getRand(double lower, double upper) {
    std::random_device rd;

    return std::bind(
            std::uniform_real_distribution<>{lower, upper},
            std::default_random_engine{rd()})();
}

string vectorToString(vector<string> v) {
    string s;
    for (const auto &p : v) {
        s += p + " ";
    }
    return s;
}

void initCommandHandler(shared_ptr<MockCommInterface> mockComm, CommandHandler *cmdHandler) {
    mockComm->supportEverything = true;

    cmdHandler->start();

    while (!cmdHandler->isInitDone()) {
        usleep(1000);
    }

}

void TestCommandHandler(CLI_TYPE type) {
    shared_ptr<MockCommInterface> mockComm = make_shared<MockCommInterface>();
    shared_ptr<OBDHandler> obdHandler = OBDHandler::createInstance();
    auto *cmdHandler = new CommandHandler(type, mockComm, obdHandler);

    initCommandHandler(mockComm, cmdHandler);

    Pid pid;
    Service service;
    bool descriptionsNotNull;

    for (const auto &cmdMap: COMMAND_MAPPING) {
        vector<string> validData{"set_1", cmdMap.first};
        vector<string> smallData{"set_1", cmdMap.first};
        vector<string> largeData{"set_1", cmdMap.first};
        EXPECT_EQ(true, cmdHandler->getPid(validData, pid, service));
        auto *fo = pid.getFrameObject(cmdHandler->getObdHandler().getVehicle());
        if (nullptr == fo) {
            continue;
        }
        descriptionsNotNull = true;

        for (const auto &desc : fo->getDescriptions()) {
            EXPECT_FALSE(desc == nullptr);
            if (desc == nullptr) {
                cout << hex << "0x" << pid.id << " has no description!" << endl;
                descriptionsNotNull = false;
                break;
            }

            // do not overwrite supported pids
            if (cmdMap.first.find("SupportedPid") != std::string::npos) {
                validData.push_back(to_string(1));
                smallData.push_back(to_string(1));
                largeData.push_back(to_string(1));
            } else {
                validData.push_back(to_string(getRand(desc->getMin(), desc->getMax())));
                // offset because double and float would give under/overflow
                smallData.push_back(to_string(desc->getMin() + 0.01));
                largeData.push_back(to_string(desc->getMax() - 0.01));
            }


        }
        if (descriptionsNotNull) {
            cout << "testing command: " << vectorToString(validData) << endl;
            vector<pair<vector<string>, int>> commands{
                    {validData, SUCCESS},
                    {smallData, SUCCESS},
                    {largeData, SUCCESS}};

            byte *vehicleData = nullptr;
            byte *answerData = nullptr;
            for (auto &cmd : commands) {

                cout << "testing command: " << vectorToString(cmd.first) << endl;
                if (ECU == type) {
                    EXPECT_EQ(cmd.second, cmdHandler->setData(cmd.first).type); // only ecu does support setting.
                }

                int size = 0;

                vehicleData = pid.getVehicleData(service, cmdHandler->getObdHandler().getVehicle(), size);
                answerData = cmdHandler->getObdHandler().createAnswerFrame(service, pid, vehicleData, size);
                mockComm->setDataForNextReceiveCall(answerData, size);

                // modify command to make getter
                cmd.first.erase(cmd.first.begin() + 2, cmd.first.end());
                cmd.first.at(0) = "get_1";
                cout << "testing command: " << vectorToString(cmd.first) << endl;
                EXPECT_EQ(SUCCESS, cmdHandler->getData(cmd.first, false).type);
            }

            delete[] vehicleData;
            delete[] answerData;

        }
    }
}

TEST(CommandHandlerTest, setData_getData_TESTER) {
    TestCommandHandler(CLI_TYPE::TESTER);

}

TEST(CommandHandlerTest, setData_getData_ECU) {
    TestCommandHandler(CLI_TYPE::ECU);
}

TEST(CommandHandlerTest, setData_getData_WIFI_ELM) {
    TestCommandHandler(CLI_TYPE::WIFI_ELM);
}

TEST(CommandHandlerTest, setData_getData_SERIAL_ELM) {
    TestCommandHandler(CLI_TYPE::SERIAL_ELM);
}


TEST(CommandHandlerTest, set_special) {
    shared_ptr<MockCommInterface> mockComm = make_shared<MockCommInterface>();
    shared_ptr<OBDHandler> obdHandler = OBDHandler::createInstance();
    auto *cmdHandler = new CommandHandler(CLI_TYPE::ECU, mockComm, obdHandler);
    initCommandHandler(mockComm, cmdHandler);

    // invalid
    vector<string> cmd = {"set", "PidByNumber"};
    DataObjectState res = cmdHandler->setData(cmd);
    EXPECT_EQ(res.type, ErrorType::MISSING_ARGUMENTS);

    cmd = {"set", "PidByNumber_1", "123"};
    res = cmdHandler->setData(cmd);
    EXPECT_EQ(res.type, ErrorType::MISSING_ARGUMENTS);

    cmd = {"set", "PidByHexNumber_1"};
    res = cmdHandler->setData(cmd);
    EXPECT_EQ(res.type, ErrorType::MISSING_ARGUMENTS);

    cmd = {"set", "PidByNumber_1", "123"};
    res = cmdHandler->setData(cmd);
    EXPECT_EQ(res.type, ErrorType::MISSING_ARGUMENTS);

    cmd = {"set", "PidByHexNumber_1", "123"};
    res = cmdHandler->setData(cmd);
    EXPECT_EQ(res.type, ErrorType::MISSING_ARGUMENTS);

    cmd = {"set", "PidByNumber_1", "123", "test"};
    res = cmdHandler->setData(cmd);
    EXPECT_EQ(res.type, ErrorType::MISSING_ARGUMENTS);

    cmd = {"set", "PidByHexNumber_1", "123", "test"};
    res = cmdHandler->setData(cmd);
    EXPECT_EQ(res.type, ErrorType::MISSING_ARGUMENTS);

    // valid
    cmd = {"set", "PidByHexNumber_1", "1", "0x0D", "1"};
    res = cmdHandler->setData(cmd);
    EXPECT_EQ(res.type, ErrorType::SUCCESS);
    EXPECT_TRUE(cmdHandler->getObdHandler().getVehicle()->getPidSupport().getPidSupported(Service::POWERTRAIN, 0x0d));

    cmd = {"set", "PidByHexNumber_1", "1", "0x0D", "0"};
    EXPECT_EQ(res.type, ErrorType::SUCCESS);
    res = cmdHandler->setData(cmd);
    EXPECT_FALSE(cmdHandler->getObdHandler().getVehicle()->getPidSupport().getPidSupported(Service::POWERTRAIN, 0x0d));

    cmd = {"set", "PidByNumber_1", "1", "13", "1"};
    res = cmdHandler->setData(cmd);
    EXPECT_EQ(res.type, ErrorType::SUCCESS);
    EXPECT_TRUE(cmdHandler->getObdHandler().getVehicle()->getPidSupport().getPidSupported(Service::POWERTRAIN, 0x0d));

    cmd = {"set", "PidByNumber_1", "1", "13", "0"};
    EXPECT_EQ(res.type, ErrorType::SUCCESS);
    res = cmdHandler->setData(cmd);
    EXPECT_FALSE(cmdHandler->getObdHandler().getVehicle()->getPidSupport().getPidSupported(Service::POWERTRAIN, 0x0d));
}


TEST(CommandHandlerTest, tryBreakStuff) {
    shared_ptr<MockCommInterface> mockComm = make_shared<MockCommInterface>();
    shared_ptr<OBDHandler> obdHandler = OBDHandler::createInstance();
    auto *cmdHandler = new CommandHandler(CLI_TYPE::ECU, mockComm, obdHandler);
    vector<string> data = {"set"};
    cmdHandler->setData(data);

    data = {"set", "asdasd"};
    EXPECT_EQ(MISSING_ARGUMENTS, cmdHandler->setData(data).type);

    data = {"set", "BankOxygenSensor"};
    EXPECT_EQ(MISSING_ARGUMENTS, cmdHandler->setData(data).type);

    data = {"set", "VehicleSpeed"};
    EXPECT_EQ(MISSING_ARGUMENTS, cmdHandler->setData(data).type);

    data = {"set"};
    EXPECT_EQ(MISSING_ARGUMENTS, cmdHandler->setData(data).type);

    data = {"get"};
    EXPECT_EQ(MISSING_ARGUMENTS, cmdHandler->getData(data, false).type);

    data = {"get", "adsas"};
    EXPECT_EQ(DATA_ERROR, cmdHandler->getData(data, false).type);

    data = {"get", "VehicleSpeed"};
    EXPECT_EQ(NOT_SUPPORTED, cmdHandler->getData(data, false).type);

    data = {"get", "VehicleSpeed", "aasdasd"};
    EXPECT_EQ(NOT_SUPPORTED, cmdHandler->getData(data, false).type);


    initCommandHandler(mockComm, cmdHandler);
    data = {"get", "VehicleSpeed"};
    EXPECT_EQ(SUCCESS, cmdHandler->getData(data, false).type);

    // todo invalid int is not handled.
    data = {"set", "VehicleSpeed", "asdhasdlsad"};
    EXPECT_EQ(SUCCESS, cmdHandler->setData(data).type);

}