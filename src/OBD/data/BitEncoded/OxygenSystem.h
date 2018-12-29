//
// Created by me on 28/12/18.
//

#ifndef OPEN_OBD2_OXYGENSYSTEM_H
#define OPEN_OBD2_OXYGENSYSTEM_H

#include "../DataObject.h"
#include "BankOxygenSensor.h"

class OxygenSystem {
private:
    unique_ptr<DataObject<bool>> bank1Sensor1present;
    unique_ptr<DataObject<bool>> bank1Sensor2present;
    unique_ptr<DataObject<bool>> bank1Sensor3present;
    unique_ptr<DataObject<bool>> bank1Sensor4present;
    unique_ptr<DataObject<bool>> bank2Sensor1present;
    unique_ptr<DataObject<bool>> bank2Sensor2present;
    unique_ptr<DataObject<bool>> bank2Sensor3present;
    unique_ptr<DataObject<bool>> bank2Sensor4present;


    unique_ptr<BankOxygenSensor> bankOxygenSensor1;
    unique_ptr<BankOxygenSensor> bankOxygenSensor2;
    unique_ptr<BankOxygenSensor> bankOxygenSensor3;
    unique_ptr<BankOxygenSensor> bankOxygenSensor4;
    unique_ptr<BankOxygenSensor> bankOxygenSensor5;
    unique_ptr<BankOxygenSensor> bankOxygenSensor6;
    unique_ptr<BankOxygenSensor> bankOxygenSensor7;
    unique_ptr<BankOxygenSensor> bankOxygenSensor8;

public:

    OxygenSystem();

    DataObject<bool> &getBank1Sensor1present();

    DataObject<bool> &getBank1Sensor2present();

    DataObject<bool> &getBank1Sensor3present();

    DataObject<bool> &getBank1Sensor4present();

    DataObject<bool> &getBank2Sensor1present();

    DataObject<bool> &getBank2Sensor2present();

    DataObject<bool> &getBank2Sensor3present();

    DataObject<bool> &getBank2Sensor4present();

    unsigned int bankSensorsPresentToFrame(unsigned int &data);

    void bankSensorsPresentFromFrame(byte *frame, int size);

    BankOxygenSensor &getBankOxygenSensor1();

    BankOxygenSensor &getBankOxygenSensor2();

    BankOxygenSensor &getBankOxygenSensor3();

    BankOxygenSensor &getBankOxygenSensor4();

    BankOxygenSensor &getBankOxygenSensor5();

    BankOxygenSensor &getBankOxygenSensor6();

    BankOxygenSensor &getBankOxygenSensor7();

    BankOxygenSensor &getBankOxygenSensor8();
};


#endif //OPEN_OBD2_OXYGENSYSTEM_H
