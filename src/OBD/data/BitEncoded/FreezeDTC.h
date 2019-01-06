//
// Created by me on 21/12/18.
//

#ifndef OPEN_OBD2_FREEZEFRAME_H
#define OPEN_OBD2_FREEZEFRAME_H

#include "../../DataTroubleCode.h"

class FreezeDTC : public IFrameObject {
private:
    unique_ptr<DataObject<unsigned short>> dataObj;
    unique_ptr<DataTroubleCode> fallbackDTC;
    shared_ptr<map<int, DataTroubleCode>> dtcMap;
    int dtcId;
public:
    explicit FreezeDTC(shared_ptr<map<int, DataTroubleCode>> dtcMap);

    ~FreezeDTC();

    void setValue(unsigned short value);

    DataTroubleCode getValue();

public:// IFrameObject

    void fromFrame(byte *data, int size) override;

    unsigned int toFrame(unsigned int &data, int &size) override;

    string getPrintableData() override;

    DataObjectStateCollection setValueFromString(string data) override;

    vector<DataObjectDescription *> getDescriptions() override;

private:
    void setTroubleCode(unsigned short val);
};


#endif //OPEN_OBD2_FREEZEFRAME_H
