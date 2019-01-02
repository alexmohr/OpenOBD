//
// Created by me on 01/01/19.
//

#ifndef OPEN_OBD2_BANKOXYGENSENSORSCOLLECTION_H
#define OPEN_OBD2_BANKOXYGENSENSORSCOLLECTION_H

#include "../../dataObject/DataObject.h"

class BankOxygenSensorsCollection : public IFrameObject {
private:
    unique_ptr<DataObject<bool>> bank1Sensor1present;
    unique_ptr<DataObject<bool>> bank1Sensor2present;
    unique_ptr<DataObject<bool>> bank1Sensor3present;
    unique_ptr<DataObject<bool>> bank1Sensor4present;
    unique_ptr<DataObject<bool>> bank2Sensor1present;
    unique_ptr<DataObject<bool>> bank2Sensor2present;
    unique_ptr<DataObject<bool>> bank2Sensor3present;
    unique_ptr<DataObject<bool>> bank2Sensor4present;
public:
    BankOxygenSensorsCollection();

    DataObject<bool> &getBank1Sensor1present();

    DataObject<bool> &getBank1Sensor2present();

    DataObject<bool> &getBank1Sensor3present();

    DataObject<bool> &getBank1Sensor4present();

    DataObject<bool> &getBank2Sensor1present();

    DataObject<bool> &getBank2Sensor2present();

    DataObject<bool> &getBank2Sensor3present();

    DataObject<bool> &getBank2Sensor4present();

public:// IFrameObject

    unsigned int toFrame(unsigned int &data, unsigned int &size) override;

    void fromFrame(byte *frame, int size) override;

    string getPrintableData() override;
};


#endif //OPEN_OBD2_BANKOXYGENSENSORSCOLLECTION_H
