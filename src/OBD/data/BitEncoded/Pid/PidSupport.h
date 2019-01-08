//
// Created by me on 21/12/18.
//

#ifndef OPEN_OBD2_PIDSUPPORT_H
#define OPEN_OBD2_PIDSUPPORT_H


#include "../../dataObject/DataObject.h"
#include "../../../../common/endian.h"
#include "SupportedPidCollection.h"


class PidSupport {
private:

    unique_ptr<SupportedPidCollection> pidSupported01_20;
    unique_ptr<SupportedPidCollection> pidSupported21_40;
    unique_ptr<SupportedPidCollection> pidSupported41_60;
    unique_ptr<SupportedPidCollection> pidSupported61_80;
    unique_ptr<SupportedPidCollection> pidSupported81_A0;
    unique_ptr<SupportedPidCollection> pidSupportedA1_C0;
    unique_ptr<SupportedPidCollection> pidSupportedC1_E0;
public:
    PidSupport();

    void setPidSupported(int pid, bool supported);

    bool getPidSupported(int pid);


    SupportedPidCollection &getCollectionPid01_20();

    SupportedPidCollection &getCollectionPid21_40();

    SupportedPidCollection &getCollectionPid41_60();

    SupportedPidCollection &getCollectionPid61_80();

    SupportedPidCollection &getCollectionPid81_A0();

    SupportedPidCollection &getCollectionPidA1_C0();

    SupportedPidCollection &getCollectionPidC1_E0();


};


#endif //OPEN_OBD2_PIDSUPPORT_H
