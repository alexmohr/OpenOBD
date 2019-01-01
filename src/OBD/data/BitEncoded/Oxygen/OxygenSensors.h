//
// Created by me on 28/12/18.
//

#ifndef OPEN_OBD2_OXYGENSYSTEM_H
#define OPEN_OBD2_OXYGENSYSTEM_H

#include "../../dataObject/DataObject.h"
#include "BankOxygenSensorsCollection.h"
#include "BankOxygenSensors4BankCollection.h"
#include "BankOxygenSensor.h"
#include "FuelRailOxygenSensor.h"
#include "ExtendedRangeOxygenSensor.h"

class OxygenSensors {
private:

    unique_ptr<BankOxygenSensorsCollection> bankOxygenSensorCollection;
    unique_ptr<BankOxygenSensors4BankCollection> bankOxygenSensor4BankCollection;


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


    unique_ptr<ExtendedRangeOxygenSensor> extendedRangeOxygenSensor1;
    unique_ptr<ExtendedRangeOxygenSensor> extendedRangeOxygenSensor2;
    unique_ptr<ExtendedRangeOxygenSensor> extendedRangeOxygenSensor3;
    unique_ptr<ExtendedRangeOxygenSensor> extendedRangeOxygenSensor4;
    unique_ptr<ExtendedRangeOxygenSensor> extendedRangeOxygenSensor5;
    unique_ptr<ExtendedRangeOxygenSensor> extendedRangeOxygenSensor6;
    unique_ptr<ExtendedRangeOxygenSensor> extendedRangeOxygenSensor7;
    unique_ptr<ExtendedRangeOxygenSensor> extendedRangeOxygenSensor8;

public:

    OxygenSensors();



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

    ExtendedRangeOxygenSensor &getExtendedRangeOxygenSensor1();

    ExtendedRangeOxygenSensor &getExtendedRangeOxygenSensor2();

    ExtendedRangeOxygenSensor &getExtendedRangeOxygenSensor3();

    ExtendedRangeOxygenSensor &getExtendedRangeOxygenSensor4();

    ExtendedRangeOxygenSensor &getExtendedRangeOxygenSensor5();

    ExtendedRangeOxygenSensor &getExtendedRangeOxygenSensor6();

    ExtendedRangeOxygenSensor &getExtendedRangeOxygenSensor7();

    ExtendedRangeOxygenSensor &getExtendedRangeOxygenSensor8();

    BankOxygenSensorsCollection &getBankOxygenSensorsCollection();

    BankOxygenSensors4BankCollection &getBankOxygenSensor4BankCollection();

};


#endif //OPEN_OBD2_OXYGENSYSTEM_H
