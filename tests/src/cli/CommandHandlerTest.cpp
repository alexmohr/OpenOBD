//
// Created by me on 04/01/19.
//


#include <gtest/gtest.h>
#include <vector>
#include "../../../src/cli/CommandHandler.h"
#include "../../../src/CAN/CanIsoTP.h"

#include <random>


using namespace std;

class MockInterface : public ICommunicationInterface {
    byte *data = (byte *) malloc(255);
    int size;
public:

    bool supportEverthing = false;

    byte responseSupportedPid01_20[6] =
            {(byte) 0x41, (byte) SupportedPid01_20, (byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0xff};
    byte responseSupportedPid21_40[6] =
            {(byte) 0x41, (byte) SupportedPid21_40, (byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0xff};
    byte responseSupportedPid41_60[6] =
            {(byte) 0x41, (byte) SupportedPid41_60, (byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0xff};
    byte responseSupportedPid61_80[6] =
            {(byte) 0x41, (byte) SupportedPid61_80, (byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0xff};
    byte responseSupportedPid81_A0[6] =
            {(byte) 0x41, (byte) SupportedPid81_A0, (byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0xff};
    byte responseSupportedPidA1_C0[6] =
            {(byte) 0x41, (byte) SupportedPidA1_C0, (byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0xff};
    byte responseSupportedPidC1_E0[6] =
            {(byte) 0x41, (byte) SupportedPidC1_E0, (byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0xff};

    virtual int send(byte *buf, int buflen) override {
        if (supportEverthing && buflen >= 2) {

            if (buf[1] == (byte) SupportedPid01_20) {
                setNextReceive(responseSupportedPid01_20, 6);
            } else if (buf[1] == (byte) SupportedPid21_40) {
                setNextReceive(responseSupportedPid21_40, 6);
            } else if (buf[1] == (byte) SupportedPid41_60) {
                setNextReceive(responseSupportedPid41_60, 6);
            } else if (buf[1] == (byte) SupportedPid61_80) {
                setNextReceive(responseSupportedPid61_80, 6);
            } else if (buf[1] == (byte) SupportedPid81_A0) {
                setNextReceive(responseSupportedPid81_A0, 6);
            } else if (buf[1] == (byte) SupportedPidA1_C0) {
                setNextReceive(responseSupportedPidA1_C0, 6);
            } else if (buf[1] == (byte) SupportedPidC1_E0) {
                setNextReceive(responseSupportedPidC1_E0, 6);
            }

        }

        return buflen;
    }

    virtual int closeInterface() override {
        return 0;
    }

    virtual int openInterface() override {
        return 0;
    };


    virtual void receive(byte *buffer, int buffSize, int &readSize) override {

        memcpy(buffer, data, size);
        readSize = size;
    }

    void setNextReceive(byte *data, int size) {
        memcpy(this->data, data, size);
        this->size = size;
    }


};

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

void initCommandHandler(MockInterface *mockComm, CommandHandler *cmdHandler) {
    mockComm->supportEverthing = true;

    cmdHandler->start();

    while (!cmdHandler->isInitDone()) {
        usleep(1000);
    }

}

void TestCommandHandler(CLI_TYPE type) {
    auto *mockComm = new MockInterface();
    auto *cmdHandler = new CommandHandler(type, mockComm);


    initCommandHandler(mockComm, cmdHandler);
    
    Pid pid;
    Service service;
    bool descriptionsNotNull;

    for (const auto &cmdMap: cmdHandler->commandMapping) {
        vector<string> validData{"set", cmdMap.first};
        vector<string> smallData{"set", cmdMap.first};
        vector<string> largeData{"set", cmdMap.first};
        EXPECT_EQ(true, cmdHandler->getPid(validData, pid, service));
        auto &fo = pid.getFrameObject(cmdHandler->getObdHandler().getVehicle());
        descriptionsNotNull = true;

        for (const auto &desc : fo.getDescriptions()) {
            EXPECT_FALSE(desc == nullptr);
            if (desc == nullptr) {
                cout << hex << "0x" << pid.id << " has no description!" << endl;
                descriptionsNotNull = false;
                break;
            }

            // do not overwrite supported pids
            if (cmdMap.first.find("SupportedPid") != std::string::npos) {
                validData.push_back(to_string(1));
                // offset because double and float would give under/overflow
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


            for (auto &cmd : commands) {

                cout << "testing command: " << vectorToString(cmd.first) << endl;
                if (ECU == type) {
                    EXPECT_EQ(cmd.second, cmdHandler->setData(cmd.first).type); // only ecu does support setting.
                }

                int size = 0;

                byte *data = pid.getVehicleData(service, cmdHandler->getObdHandler().getVehicle(), size);
                data = cmdHandler->getObdHandler().createAnswerFrame(service, pid, data, size);
                mockComm->setNextReceive(data, size);
                delete data;

                // modify command to make getter
                cmd.first.erase(cmd.first.begin() + 2, cmd.first.end());
                cmd.first.at(0) = "get";
                cout << "testing command: " << vectorToString(cmd.first) << endl;
                EXPECT_EQ(SUCCESS, cmdHandler->getData(cmd.first).type);
            }
        }
    }
    cmdHandler->stopHandler();
}

TEST(CommandHandlerTest, setData_getData_TESTER) {
    TestCommandHandler(CLI_TYPE::TESTER);

}

TEST(CommandHandlerTest, setData_getData_ECU) {
    TestCommandHandler(CLI_TYPE::ECU);
}

TEST(CommandHandlerTest, setData_getData_ELM) {
    TestCommandHandler(CLI_TYPE::ELM);

}

TEST(CommandHandlerTest, set_special) {
    auto *mockComm = new MockInterface();
    auto *cmdHandler = new CommandHandler(CLI_TYPE::ECU, mockComm);
    initCommandHandler(mockComm, cmdHandler);

    // invalid
    vector<string> cmd = {"set", "PidByNumber"};
    DataObjectState res = cmdHandler->setData(cmd);
    EXPECT_EQ(res.type, ErrorType::MISSING_ARGUMENTS);

    cmd = {"set", "PidByNumber", "123"};
    res = cmdHandler->setData(cmd);
    EXPECT_EQ(res.type, ErrorType::MISSING_ARGUMENTS);

    cmd = {"set", "PidByHexNumber"};
    res = cmdHandler->setData(cmd);
    EXPECT_EQ(res.type, ErrorType::MISSING_ARGUMENTS);

    cmd = {"set", "PidByNumber", "123"};
    res = cmdHandler->setData(cmd);
    EXPECT_EQ(res.type, ErrorType::MISSING_ARGUMENTS);

    cmd = {"set", "PidByHexNumber", "123"};
    res = cmdHandler->setData(cmd);
    EXPECT_EQ(res.type, ErrorType::MISSING_ARGUMENTS);

    cmd = {"set", "PidByNumber", "123", "test"};
    res = cmdHandler->setData(cmd);
    EXPECT_EQ(res.type, ErrorType::MISSING_ARGUMENTS);

    cmd = {"set", "PidByHexNumber", "123", "test"};
    res = cmdHandler->setData(cmd);
    EXPECT_EQ(res.type, ErrorType::MISSING_ARGUMENTS);

    // valid
    cmd = {"set", "PidByHexNumber", "1", "0x0D", "1"};
    res = cmdHandler->setData(cmd);
    EXPECT_EQ(res.type, ErrorType::SUCCESS);
    EXPECT_TRUE(cmdHandler->getObdHandler().getVehicle()->getPidSupport().getPidSupported(Service::POWERTRAIN, 0x0d));

    cmd = {"set", "PidByHexNumber", "1", "0x0D", "0"};
    EXPECT_EQ(res.type, ErrorType::SUCCESS);
    res = cmdHandler->setData(cmd);
    EXPECT_FALSE(cmdHandler->getObdHandler().getVehicle()->getPidSupport().getPidSupported(Service::POWERTRAIN, 0x0d));

    cmd = {"set", "PidByNumber", "1", "13", "1"};
    res = cmdHandler->setData(cmd);
    EXPECT_EQ(res.type, ErrorType::SUCCESS);
    EXPECT_TRUE(cmdHandler->getObdHandler().getVehicle()->getPidSupport().getPidSupported(Service::POWERTRAIN, 0x0d));

    cmd = {"set", "PidByNumber", "1", "13", "0"};
    EXPECT_EQ(res.type, ErrorType::SUCCESS);
    res = cmdHandler->setData(cmd);
    EXPECT_FALSE(cmdHandler->getObdHandler().getVehicle()->getPidSupport().getPidSupported(Service::POWERTRAIN, 0x0d));

    cmdHandler->stopHandler();
}



TEST(CommandHandlerTest, tryBreakStuff) {
    auto *mockComm = new MockInterface();
    auto *cmdHandler = new CommandHandler(CLI_TYPE::ECU, mockComm);
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
    EXPECT_EQ(MISSING_ARGUMENTS, cmdHandler->getData(data).type);

    data = {"get", "adsas"};
    EXPECT_EQ(DATA_ERROR, cmdHandler->getData(data).type);

    data = {"get", "VehicleSpeed"};
    EXPECT_EQ(NOT_SUPPORTED, cmdHandler->getData(data).type);

    data = {"get", "VehicleSpeed", "aasdasd"};
    EXPECT_EQ(NOT_SUPPORTED, cmdHandler->getData(data).type);


    initCommandHandler(mockComm, cmdHandler);
    data = {"get", "VehicleSpeed"};
    EXPECT_EQ(SUCCESS, cmdHandler->getData(data).type);

    // todo invalid int is not handled.
    data = {"set", "VehicleSpeed", "asdhasdlsad"};
    EXPECT_EQ(SUCCESS, cmdHandler->setData(data).type);

    cmdHandler->stopHandler();

}