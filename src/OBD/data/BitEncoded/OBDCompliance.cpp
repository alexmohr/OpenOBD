//
// Created by me on 29/12/18.
//

#include "OBDCompliance.h"

OBDCompliance::OBDCompliance() {
    oBD_II_CARB = make_unique<DataObject<bool>>(A, 1);
    oBD_EPA = make_unique<DataObject<bool>>(A, 2);
    oBD_and_OBD_II = make_unique<DataObject<bool>>(A, 3);
    oBD_I = make_unique<DataObject<bool>>(A, 4);
    notOBDcompliant = make_unique<DataObject<bool>>(A, 5);
    eOBD = make_unique<DataObject<bool>>(A, 6);
    eOBDandOBD_II = make_unique<DataObject<bool>>(A, 7);
    eOBDandOBD = make_unique<DataObject<bool>>(A, 8);
    eOBD_OBD_and_OBDII = make_unique<DataObject<bool>>(A, 9);
    jOBD = make_unique<DataObject<bool>>(A, 10);
    jOBDandOBDII = make_unique<DataObject<bool>>(A, 11);
    jOBDandEOBD = make_unique<DataObject<bool>>(A, 12);
    jOBD_EOBD_and_OBDII = make_unique<DataObject<bool>>(A, 13);
    engineManufacturerDiagnostics = make_unique<DataObject<bool>>(A, 17);
    engineManufacturerDiagnosticsEnhanced = make_unique<DataObject<bool>>(A, 18);
    heavyDutyOn_BoardDiagnostics_OBD_C = make_unique<DataObject<bool>>(A, 19);
    heavyDutyOn_BoardDiagnostics = make_unique<DataObject<bool>>(A, 20);
    worldWideHarmonizedOBD = make_unique<DataObject<bool>>(A, 21);
    heavyDutyEuroOBDStageIwithoutNOxcontrol = make_unique<DataObject<bool>>(A, 23);
    heavyDutyEuroOBDStageIwithNOxcontrol = make_unique<DataObject<bool>>(A, 24);
    heavyDutyEuroOBDStageIIwithoutNOxcontrol = make_unique<DataObject<bool>>(A, 25);
    heavyDutyEuroOBDStageIIwithNOxcontrol = make_unique<DataObject<bool>>(A, 26);
    brazilOBDPhase1 = make_unique<DataObject<bool>>(A, 28);
    brazilOBDPhase2 = make_unique<DataObject<bool>>(A, 29);
    koreanOBD = make_unique<DataObject<bool>>(A, 30);
    indiaOBDI = make_unique<DataObject<bool>>(A, 31);
    indiaOBDII = make_unique<DataObject<bool>>(A, 32);
    heavyDutyEuroOBDStageVI = make_unique<DataObject<bool>>(A, 33);
}

DataObject<bool> &OBDCompliance::getOBD_II_CARB() {
    return *oBD_II_CARB;
}

DataObject<bool> &OBDCompliance::getOBD_EPA() {
    return *oBD_EPA;
}

DataObject<bool> &OBDCompliance::getOBD_and_OBD_II() {
    return *oBD_and_OBD_II;
}

DataObject<bool> &OBDCompliance::getOBD_I() {
    return *oBD_I;
}

DataObject<bool> &OBDCompliance::getNotOBDcompliant() {
    return *notOBDcompliant;
}

DataObject<bool> &OBDCompliance::getEOBD() {
    return *eOBD;
}

DataObject<bool> &OBDCompliance::getEOBDandOBD_II() {
    return *eOBDandOBD_II;
}

DataObject<bool> &OBDCompliance::getEOBDandOBD() {
    return *eOBDandOBD;
}

DataObject<bool> &OBDCompliance::getEOBD_OBD_and_OBDII() {
    return *eOBD_OBD_and_OBDII;
}

DataObject<bool> &OBDCompliance::getJOBD() {
    return *jOBD;
}

DataObject<bool> &OBDCompliance::getJOBDandOBDII() {
    return *jOBDandOBDII;
}

DataObject<bool> &OBDCompliance::getJOBDandEOBD() {
    return *jOBDandEOBD;
}

DataObject<bool> &OBDCompliance::getJOBD_EOBD_and_OBDII() {
    return *jOBD_EOBD_and_OBDII;
}

DataObject<bool> &OBDCompliance::getEngineManufacturerDiagnostics() {
    return *engineManufacturerDiagnostics;
}

DataObject<bool> &OBDCompliance::getEngineManufacturerDiagnosticsEnhanced() {
    return *engineManufacturerDiagnosticsEnhanced;
}

DataObject<bool> &OBDCompliance::getHeavyDutyOn_BoardDiagnostics_OBD_C() {
    return *heavyDutyOn_BoardDiagnostics_OBD_C;
}

DataObject<bool> &OBDCompliance::getHeavyDutyOn_BoardDiagnostics() {
    return *heavyDutyOn_BoardDiagnostics;
}

DataObject<bool> &OBDCompliance::getWorldWideHarmonizedOBD() {
    return *worldWideHarmonizedOBD;
}

DataObject<bool> &OBDCompliance::getHeavyDutyEuroOBDStageIwithoutNOxcontrol() {
    return *heavyDutyEuroOBDStageIwithoutNOxcontrol;
}

DataObject<bool> &OBDCompliance::getHeavyDutyEuroOBDStageIwithNOxcontrol() {
    return *heavyDutyEuroOBDStageIwithNOxcontrol;
}

DataObject<bool> &OBDCompliance::getHeavyDutyEuroOBDStageIIwithoutNOxcontrol() {
    return *heavyDutyEuroOBDStageIIwithoutNOxcontrol;
}

DataObject<bool> &OBDCompliance::getHeavyDutyEuroOBDStageIIwithNOxcontrol() {
    return *heavyDutyEuroOBDStageIIwithNOxcontrol;
}

DataObject<bool> &OBDCompliance::getBrazilOBDPhase1() {
    return *brazilOBDPhase1;
}

DataObject<bool> &OBDCompliance::getBrazilOBDPhase2() {
    return *brazilOBDPhase2;
}

DataObject<bool> &OBDCompliance::getKoreanOBD() {
    return *koreanOBD;
}

DataObject<bool> &OBDCompliance::getIndiaOBDI() {
    return *indiaOBDI;
}

DataObject<bool> &OBDCompliance::getIndiaOBDII() {
    return *indiaOBDII;
}

DataObject<bool> &OBDCompliance::getHeavyDutyEuroOBDStageVI() {
    return *heavyDutyEuroOBDStageVI;
}

void OBDCompliance::fromFrame(byte *data, int size) {
    oBD_II_CARB->fromFrame(data, size);
    oBD_EPA->fromFrame(data, size);
    oBD_and_OBD_II->fromFrame(data, size);
    oBD_I->fromFrame(data, size);
    notOBDcompliant->fromFrame(data, size);
    eOBD->fromFrame(data, size);
    eOBDandOBD_II->fromFrame(data, size);
    eOBDandOBD->fromFrame(data, size);
    eOBD_OBD_and_OBDII->fromFrame(data, size);
    jOBD->fromFrame(data, size);
    jOBDandOBDII->fromFrame(data, size);
    jOBDandEOBD->fromFrame(data, size);
    jOBD_EOBD_and_OBDII->fromFrame(data, size);
    engineManufacturerDiagnostics->fromFrame(data, size);
    engineManufacturerDiagnosticsEnhanced->fromFrame(data, size);
    heavyDutyOn_BoardDiagnostics_OBD_C->fromFrame(data, size);
    heavyDutyOn_BoardDiagnostics->fromFrame(data, size);
    worldWideHarmonizedOBD->fromFrame(data, size);
    heavyDutyEuroOBDStageIwithoutNOxcontrol->fromFrame(data, size);
    heavyDutyEuroOBDStageIwithNOxcontrol->fromFrame(data, size);
    heavyDutyEuroOBDStageIIwithoutNOxcontrol->fromFrame(data, size);
    heavyDutyEuroOBDStageIIwithNOxcontrol->fromFrame(data, size);
    brazilOBDPhase1->fromFrame(data, size);
    brazilOBDPhase2->fromFrame(data, size);
    koreanOBD->fromFrame(data, size);
    indiaOBDI->fromFrame(data, size);
    indiaOBDII->fromFrame(data, size);
    heavyDutyEuroOBDStageVI->fromFrame(data, size);
}

unsigned int OBDCompliance::toFrame(unsigned int &data) {
    data |=
            oBD_II_CARB->toFrame(data) |
            oBD_EPA->toFrame(data) |
            oBD_and_OBD_II->toFrame(data) |
            oBD_I->toFrame(data) |
            notOBDcompliant->toFrame(data) |
            eOBD->toFrame(data) |
            eOBDandOBD_II->toFrame(data) |
            eOBDandOBD->toFrame(data) |
            eOBD_OBD_and_OBDII->toFrame(data) |
            jOBD->toFrame(data) |
            jOBDandOBDII->toFrame(data) |
            jOBDandEOBD->toFrame(data) |
            jOBD_EOBD_and_OBDII->toFrame(data) |
            engineManufacturerDiagnostics->toFrame(data) |
            engineManufacturerDiagnosticsEnhanced->toFrame(data) |
            heavyDutyOn_BoardDiagnostics_OBD_C->toFrame(data) |
            heavyDutyOn_BoardDiagnostics->toFrame(data) |
            worldWideHarmonizedOBD->toFrame(data) |
            heavyDutyEuroOBDStageIwithoutNOxcontrol->toFrame(data) |
            heavyDutyEuroOBDStageIwithNOxcontrol->toFrame(data) |
            heavyDutyEuroOBDStageIIwithoutNOxcontrol->toFrame(data) |
            heavyDutyEuroOBDStageIIwithNOxcontrol->toFrame(data) |
            brazilOBDPhase1->toFrame(data) |
            brazilOBDPhase2->toFrame(data) |
            koreanOBD->toFrame(data) |
            indiaOBDI->toFrame(data) |
            indiaOBDII->toFrame(data) |
            heavyDutyEuroOBDStageVI->toFrame(data);
    return data;
}

string OBDCompliance::getPrintableData() {
    return "OBD_II_CARB" + oBD_II_CARB->getPrintableData() +
           "\nOBD_EPA" + oBD_EPA->getPrintableData() +
           "\nOBD_and_OBD_II" + oBD_and_OBD_II->getPrintableData() +
           "\nOBD_I" + oBD_I->getPrintableData() +
           "\nNotOBDcompliant" + notOBDcompliant->getPrintableData() +
           "\nEOBD" + eOBD->getPrintableData() +
           "\nEOBDandOBD_II" + eOBDandOBD_II->getPrintableData() +
           "\nEOBDandOBD" + eOBDandOBD->getPrintableData() +
           "\nEOBD_OBD_and_OBDII" + eOBD_OBD_and_OBDII->getPrintableData() +
           "\nJOBD" + jOBD->getPrintableData() +
           "\nJOBDandOBDII" + jOBDandOBDII->getPrintableData() +
           "\nJOBDandEOBD" + jOBDandEOBD->getPrintableData() +
           "\nJOBD_EOBD_and_OBDII" + jOBD_EOBD_and_OBDII->getPrintableData() +
           "\nEngineManufacturerDiagnostics" + engineManufacturerDiagnostics->getPrintableData() +
           "\nEngineManufacturerDiagnosticsEnhanced" + engineManufacturerDiagnosticsEnhanced->getPrintableData() +
           "\nHeavyDutyOn_BoardDiagnostics_OBD_C" + heavyDutyOn_BoardDiagnostics_OBD_C->getPrintableData() +
           "\nHeavyDutyOn_BoardDiagnostics" + heavyDutyOn_BoardDiagnostics->getPrintableData() +
           "\nWorldWideHarmonizedOBD" + worldWideHarmonizedOBD->getPrintableData() +
           "\nHeavyDutyEuroOBDStageIwithoutNOxcontrol" + heavyDutyEuroOBDStageIwithoutNOxcontrol->getPrintableData() +
           "\nHeavyDutyEuroOBDStageIwithNOxcontrol" + heavyDutyEuroOBDStageIwithNOxcontrol->getPrintableData() +
           "\nHeavyDutyEuroOBDStageIIwithoutNOxcontrol" + heavyDutyEuroOBDStageIIwithoutNOxcontrol->getPrintableData() +
           "\nHeavyDutyEuroOBDStageIIwithNOxcontrol" + heavyDutyEuroOBDStageIIwithNOxcontrol->getPrintableData() +
           "\nBrazilOBDPhase1" + brazilOBDPhase1->getPrintableData() +
           "\nBrazilOBDPhase2" + brazilOBDPhase2->getPrintableData() +
           "\nKoreanOBD" + koreanOBD->getPrintableData() +
           "\nIndiaOBDI" + indiaOBDI->getPrintableData() +
           "\nIndiaOBDII" + indiaOBDII->getPrintableData() +
           "\nHeavyDutyEuroOBDStageVI" + heavyDutyEuroOBDStageVI->getPrintableData();
}
