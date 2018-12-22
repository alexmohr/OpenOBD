//
// Created by me on 21/12/18.
//

#ifndef OPEN_OBD2_FREEZEFRAME_H
#define OPEN_OBD2_FREEZEFRAME_H

#include "../../DataTroubleCode.h"

class FreezeDTC {
private:
    DataTroubleCode *dtc;
    unique_ptr<DataObject<unsigned short>> dataObj;
    shared_ptr<map<int, DataTroubleCode>> dtcMap;

public:
    explicit FreezeDTC(shared_ptr<map<int, DataTroubleCode>> dtcMap);

    ~FreezeDTC();

    void fromFrame(byte *data, int size);

    unsigned int toFrame(unsigned int &data);

    void setValue(unsigned short value);

    DataTroubleCode getValue();

};


#endif //OPEN_OBD2_FREEZEFRAME_H
