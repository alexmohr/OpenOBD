//
// Created by me on 28/12/18.
//

#ifndef OPEN_OBD2_OXYGENSYSTEM_H
#define OPEN_OBD2_OXYGENSYSTEM_H

#include "../dataObject/DataObject.h"
#include "BankOxygenSensor.h"
#include "FuelRailOxygenSensor.h"
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

    unique_ptr<DataObject<bool>> bank1Sensor1presentIn4Banks;
    unique_ptr<DataObject<bool>> bank1Sensor2presentIn4Banks;
    unique_ptr<DataObject<bool>> bank2Sensor1presentIn4Banks;
    unique_ptr<DataObject<bool>> bank2Sensor2presentIn4Banks;
    unique_ptr<DataObject<bool>> bank3Sensor1presentIn4Banks;
    unique_ptr<DataObject<bool>> bank3Sensor2presentIn4Banks;
    unique_ptr<DataObject<bool>> bank4Sensor1presentIn4Banks;
    unique_ptr<DataObject<bool>> bank4Sensor2presentIn4Banks;

    unique_ptr<BankOxygenSensor> bankOxygenSensor1;
    unique_ptr<BankOxygenSensor> bankOxygenSensor2;
    unique_ptr<BankOxygenSensor> bankOxygenSensor3;
    unique_ptr<BankOxygenSensor> bankOxygenSensor4;
    unique_ptr<BankOxygenSensor> bankOxygenSensor5;
    unique_ptr<BankOxygenSensor> bankOxygenSensor6;
    unique_ptr<BankOxygenSensor> bankOxygenSensor7;
    unique_ptr<BankOxygenSensor> bankOxygenSensor8;

    unique_ptr<FuelRailOxygenSensor> fuelRailOxygenSensor1;
    unique_ptr<FuelRailOxygenSensor> fuelRailOxygenSensor2;
    unique_ptr<FuelRailOxygenSensor> fuelRailOxygenSensor3;
    unique_ptr<FuelRailOxygenSensor> fuelRailOxygenSensor4;
    unique_ptr<FuelRailOxygenSensor> fuelRailOxygenSensor5;
    unique_ptr<FuelRailOxygenSensor> fuelRailOxygenSensor6;
    unique_ptr<FuelRailOxygenSensor> fuelRailOxygenSensor7;
    unique_ptr<FuelRailOxygenSensor> fuelRailOxygenSensor8;

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

    unsigned int getBankSensorsPresentToFrame(unsigned int &data);

    void getBankSensorsPresentFromFrame(byte *frame, int size);

    DataObject<bool> &getBank1Sensor1presentIn4Banks();

    DataObject<bool> &getBank1Sensor2presentIn4Banks();

    DataObject<bool> &getBank2Sensor1presentIn4Banks();

    DataObject<bool> &getBank2Sensor2presentIn4Banks();

    DataObject<bool> &getBank3Sensor1presentIn4Banks();

    DataObject<bool> &getBank3Sensor2presentIn4Banks();

    DataObject<bool> &getBank4Sensor1presentIn4Banks();

    DataObject<bool> &getBank4Sensor2presentIn4Banks();

    unsigned int getBankSensorsPresentIn4BanksToFrame(unsigned int &data);

    void getBankSensorsPresentIn4BanksFromFrame(byte *frame, int size);

    BankOxygenSensor &getBankOxygenSensor1();

    BankOxygenSensor &getBankOxygenSensor2();

    BankOxygenSensor &getBankOxygenSensor3();

    BankOxygenSensor &getBankOxygenSensor4();

    BankOxygenSensor &getBankOxygenSensor5();

    BankOxygenSensor &getBankOxygenSensor6();

    BankOxygenSensor &getBankOxygenSensor7();

    BankOxygenSensor &getBankOxygenSensor8();

    FuelRailOxygenSensor &getFuelRailOxygenSensor1();

    FuelRailOxygenSensor &getFuelRailOxygenSensor2();

    FuelRailOxygenSensor &getFuelRailOxygenSensor3();

    FuelRailOxygenSensor &getFuelRailOxygenSensor4();

    FuelRailOxygenSensor &getFuelRailOxygenSensor5();

    FuelRailOxygenSensor &getFuelRailOxygenSensor6();

    FuelRailOxygenSensor &getFuelRailOxygenSensor7();

    FuelRailOxygenSensor &getFuelRailOxygenSensor8();


};


#endif //OPEN_OBD2_OXYGENSYSTEM_H
