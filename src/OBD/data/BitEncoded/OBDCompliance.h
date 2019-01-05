//
//Createdbymeon29/12/18.
//

#ifndef OPEN_OBD2_OBDCOMPLIANCE_H
#define OPEN_OBD2_OBDCOMPLIANCE_H

#include"../dataObject/DataObject.h"

class OBDCompliance : public IFrameObject {
private:
    unique_ptr<DataObject<bool>> oBD_II_CARB;
    unique_ptr<DataObject<bool>> oBD_EPA;
    unique_ptr<DataObject<bool>> oBD_and_OBD_II;
    unique_ptr<DataObject<bool>> oBD_I;
    unique_ptr<DataObject<bool>> notOBDcompliant;
    unique_ptr<DataObject<bool>> eOBD;
    unique_ptr<DataObject<bool>> eOBDandOBD_II;
    unique_ptr<DataObject<bool>> eOBDandOBD;
    unique_ptr<DataObject<bool>> eOBD_OBD_and_OBDII;
    unique_ptr<DataObject<bool>> jOBD;
    unique_ptr<DataObject<bool>> jOBDandOBDII;
    unique_ptr<DataObject<bool>> jOBDandEOBD;
    unique_ptr<DataObject<bool>> jOBD_EOBD_and_OBDII;
    unique_ptr<DataObject<bool>> engineManufacturerDiagnostics;
    unique_ptr<DataObject<bool>> engineManufacturerDiagnosticsEnhanced;
    unique_ptr<DataObject<bool>> heavyDutyOn_BoardDiagnostics_OBD_C;
    unique_ptr<DataObject<bool>> heavyDutyOn_BoardDiagnostics;
    unique_ptr<DataObject<bool>> worldWideHarmonizedOBD;
    unique_ptr<DataObject<bool>> heavyDutyEuroOBDStageIwithoutNOxcontrol;
    unique_ptr<DataObject<bool>> heavyDutyEuroOBDStageIwithNOxcontrol;
    unique_ptr<DataObject<bool>> heavyDutyEuroOBDStageIIwithoutNOxcontrol;
    unique_ptr<DataObject<bool>> heavyDutyEuroOBDStageIIwithNOxcontrol;
    unique_ptr<DataObject<bool>> brazilOBDPhase1;
    unique_ptr<DataObject<bool>> brazilOBDPhase2;
    unique_ptr<DataObject<bool>> koreanOBD;
    unique_ptr<DataObject<bool>> indiaOBDI;
    unique_ptr<DataObject<bool>> indiaOBDII;
    unique_ptr<DataObject<bool>> heavyDutyEuroOBDStageVI;
public:
    explicit OBDCompliance();

    DataObject<bool> &getOBD_II_CARB();

    DataObject<bool> &getOBD_EPA();

    DataObject<bool> &getOBD_and_OBD_II();

    DataObject<bool> &getOBD_I();

    DataObject<bool> &getNotOBDcompliant();

    DataObject<bool> &getEOBD();

    DataObject<bool> &getEOBDandOBD_II();

    DataObject<bool> &getEOBDandOBD();

    DataObject<bool> &getEOBD_OBD_and_OBDII();

    DataObject<bool> &getJOBD();

    DataObject<bool> &getJOBDandOBDII();

    DataObject<bool> &getJOBDandEOBD();

    DataObject<bool> &getJOBD_EOBD_and_OBDII();

    DataObject<bool> &getEngineManufacturerDiagnostics();

    DataObject<bool> &getEngineManufacturerDiagnosticsEnhanced();

    DataObject<bool> &getHeavyDutyOn_BoardDiagnostics_OBD_C();

    DataObject<bool> &getHeavyDutyOn_BoardDiagnostics();

    DataObject<bool> &getWorldWideHarmonizedOBD();

    DataObject<bool> &getHeavyDutyEuroOBDStageIwithoutNOxcontrol();

    DataObject<bool> &getHeavyDutyEuroOBDStageIwithNOxcontrol();

    DataObject<bool> &getHeavyDutyEuroOBDStageIIwithoutNOxcontrol();

    DataObject<bool> &getHeavyDutyEuroOBDStageIIwithNOxcontrol();

    DataObject<bool> &getBrazilOBDPhase1();

    DataObject<bool> &getBrazilOBDPhase2();

    DataObject<bool> &getKoreanOBD();

    DataObject<bool> &getIndiaOBDI();

    DataObject<bool> &getIndiaOBDII();

    DataObject<bool> &getHeavyDutyEuroOBDStageVI();

public:// IFrameObject

    void fromFrame(byte *data, int size) override;

    unsigned int toFrame(unsigned int &data, int &size) override;

    string getPrintableData() override;

    int setValueFromString(string data) override;

    vector<DataObjectDescription *> getDescriptions() override;
};


#endif//OPEN_OBD2_OBDCOMPLIANCE_H
