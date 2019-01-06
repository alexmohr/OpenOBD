//
// Created by me on 01/01/19.
//

#ifndef OPEN_OBD2_BANKOXYGENSESNSORS4BANKCOLLECTION_H
#define OPEN_OBD2_BANKOXYGENSESNSORS4BANKCOLLECTION_H

#include "../../dataObject/DataObject.h"

class BankOxygenSensors4BankCollection : public IFrameObject {
private:
    unique_ptr<DataObject<bool>> bank1Sensor1presentIn4Banks;
    unique_ptr<DataObject<bool>> bank1Sensor2presentIn4Banks;
    unique_ptr<DataObject<bool>> bank2Sensor1presentIn4Banks;
    unique_ptr<DataObject<bool>> bank2Sensor2presentIn4Banks;
    unique_ptr<DataObject<bool>> bank3Sensor1presentIn4Banks;
    unique_ptr<DataObject<bool>> bank3Sensor2presentIn4Banks;
    unique_ptr<DataObject<bool>> bank4Sensor1presentIn4Banks;
    unique_ptr<DataObject<bool>> bank4Sensor2presentIn4Banks;

    vector<DataObject<bool>*> allSensors;

public:
    BankOxygenSensors4BankCollection();

    DataObject<bool> &getBank1Sensor1presentIn4Banks();

    DataObject<bool> &getBank1Sensor2presentIn4Banks();

    DataObject<bool> &getBank2Sensor1presentIn4Banks();

    DataObject<bool> &getBank2Sensor2presentIn4Banks();

    DataObject<bool> &getBank3Sensor1presentIn4Banks();

    DataObject<bool> &getBank3Sensor2presentIn4Banks();

    DataObject<bool> &getBank4Sensor1presentIn4Banks();

    DataObject<bool> &getBank4Sensor2presentIn4Banks();

public:// IFrameObject
    unsigned int toFrame(unsigned int &data, int &size) override;

    void fromFrame(byte *frame, int size) override;

    string getPrintableData() override;

    DataObjectStateCollection setValueFromString(string data) override;

    vector<DataObjectDescription *> getDescriptions() override;
};


#endif //OPEN_OBD2_BANKOXYGENSESNSORS4BANKCOLLECTION_H
