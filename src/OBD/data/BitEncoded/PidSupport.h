//
// Created by me on 21/12/18.
//

#ifndef OPEN_OBD2_PIDSUPPORT_H
#define OPEN_OBD2_PIDSUPPORT_H


#include "../dataObject/DataObject.h"
#include "../../../common/endian.h"

enum PidRange {
    Pid01_20,
    Pid21_40,
    Pid41_60,
    Pid61_80,
    Pid81_A0,
    PidA1_C0,
    PidC1_E0
};

class PidSupport {
private:
    void initPid(vector<DataObject<bool>> &data);

    unique_ptr<vector<DataObject<bool>>> pidSupported01_20;
    unique_ptr<vector<DataObject<bool>>> pidSupported21_40;
    unique_ptr<vector<DataObject<bool>>> pidSupported41_60;
    unique_ptr<vector<DataObject<bool>>> pidSupported61_80;
    unique_ptr<vector<DataObject<bool>>> pidSupported81_A0;
    unique_ptr<vector<DataObject<bool>>> pidSupportedA1_C0;
    unique_ptr<vector<DataObject<bool>>> pidSupportedC1_E0;
public:
    PidSupport();

    void setPidSupported(int pid, bool supported);

    bool getPidSupported(int pid);

    void setPidSupportedFromFrame(PidRange pid, byte *data, int size);

    unsigned int getPidSupportedRange(PidRange pid, unsigned int &data);

    void setPids(vector<DataObject<bool>> &pids, byte *data, int size);

    unsigned int getPids(vector<DataObject<bool>> &pids, unsigned int &data);
};


#endif //OPEN_OBD2_PIDSUPPORT_H
