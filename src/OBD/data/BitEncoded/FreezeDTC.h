//
// Created by me on 21/12/18.
//

#ifndef OPEN_OBD2_FREEZEFRAME_H
#define OPEN_OBD2_FREEZEFRAME_H

#include "../../DataTroubleCode.h"

class FreezeDTC : public IFrameObject {
private:
    DataTroubleCode *dtc;
    unique_ptr<DataObject<unsigned short>> dataObj;
    shared_ptr<map<int, DataTroubleCode>> dtcMap;

public:
    explicit FreezeDTC(shared_ptr<map<int, DataTroubleCode>> dtcMap);

    ~FreezeDTC();

    void setValue(unsigned short value);

    DataTroubleCode getValue();

public:// IFrameObject

    void fromFrame(byte *data, int size) override;

    unsigned int toFrame(unsigned int &data, unsigned int &size) override;

    string getPrintableData() override;

    void setValueFromString(string data) override;

};


#endif //OPEN_OBD2_FREEZEFRAME_H
