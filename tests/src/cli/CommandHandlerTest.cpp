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
    virtual int send(byte *buf, int buflen) {
        return buflen;
    }

    virtual int closeInterface() {
        return 0;
    }

    virtual int openInterface() {
        return 0;
    };


    virtual void receive(byte *buffer, int buffSize, int &readSize) {
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


void TestCommandHandler(CLI_TYPE type) {

    auto mockComm = new MockInterface();
    auto cmdHandler = CommandHandler(type, mockComm);

    Pid pid;
    Service service;
    bool descriptionsNotNull;
    cmdHandler.start();

    while (!cmdHandler.isInitDone()) {
        usleep(1000);
    }

    for (const auto &cmdMap: cmdHandler.commandMapping) {
        vector<string> validData{"set", cmdMap.first};
        vector<string> smallData{"set", cmdMap.first};
        vector<string> largeData{"set", cmdMap.first};
        EXPECT_EQ(true, cmdHandler.getPid(validData, pid, service));
        auto &fo = pid.getFrameObject(cmdHandler.getObdHandler().getVehicle());
        descriptionsNotNull = true;

        for (const auto &desc : fo.getDescriptions()) {
            EXPECT_FALSE(desc == nullptr);
            if (desc == nullptr) {
                cout << hex << "0x" << pid.id << " has no description!" << endl;
                descriptionsNotNull = false;
                break;
            }

            validData.push_back(to_string(getRand(desc->getMin(), desc->getMax())));

            // offset because double and float would give under/overflow
            smallData.push_back(to_string(desc->getMin() + 0.01));
            largeData.push_back(to_string(desc->getMax() - 0.01));
        }
        if (descriptionsNotNull) {
            cout << "testing command: " << vectorToString(validData) << endl;
            vector<pair<vector<string>, int>> commands{
                    {validData, SUCCESS},
                    {smallData, SUCCESS},
                    {largeData, SUCCESS}};


            for (auto &cmd : commands) {
                cout << "testing command: " << vectorToString(cmd.first) << endl;
                if (ELM != type) {
                    EXPECT_EQ(cmd.second, cmdHandler.setData(cmd.first).type); // no set support for elm.
                }

                int size = 0;

                byte *data = pid.getVehicleData(service, cmdHandler.getObdHandler().getVehicle(), size);
                data = cmdHandler.getObdHandler().createAnswerFrame(service, pid, data, size);
                mockComm->setNextReceive(data, size);
                delete data;

                // modify command to make getter
                cmd.first.erase(cmd.first.begin() + 2, cmd.first.end());
                cmd.first.at(0) = "get";
                cout << "testing command: " << vectorToString(cmd.first) << endl;
                EXPECT_EQ(0, cmdHandler.getData(cmd.first));
            }
        }
    }
    cmdHandler.stopHandler();
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


TEST(CommandHandlerTest, tryBreakStuff) {
    auto mockComm = new MockInterface();
    auto cmdHandler = CommandHandler(ECU, mockComm);
    vector<string> data = {"set"};
    cmdHandler.setData(data);

    data = {"set asdasd"};
    cmdHandler.setData(data);

    data = {"set BankOxygenSensor"};
    cmdHandler.setData(data);

    data = {"set VehicleSpeed"};
    cmdHandler.setData(data);

    data = {"set VehicleSpeed asdhasdlsad"};
    cmdHandler.setData(data);

    data = {"set"};
    cmdHandler.setData(data);

    data = {"get"};
    cmdHandler.getData(data);

    data = {"get adsas"};
    cmdHandler.getData(data);

    data = {"get VehicleSpeed"};
    cmdHandler.getData(data);

    data = {"get VehicleSpeed aasdasd"};
    cmdHandler.getData(data);
}