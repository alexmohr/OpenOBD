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

unsigned int OBDCompliance::toFrame(unsigned int &data, int &size) {
    data |=
            oBD_II_CARB->toFrame(data, size) |
            oBD_EPA->toFrame(data, size) |
            oBD_and_OBD_II->toFrame(data, size) |
            oBD_I->toFrame(data, size) |
            notOBDcompliant->toFrame(data, size) |
            eOBD->toFrame(data, size) |
            eOBDandOBD_II->toFrame(data, size) |
            eOBDandOBD->toFrame(data, size) |
            eOBD_OBD_and_OBDII->toFrame(data, size) |
            jOBD->toFrame(data, size) |
            jOBDandOBDII->toFrame(data, size) |
            jOBDandEOBD->toFrame(data, size) |
            jOBD_EOBD_and_OBDII->toFrame(data, size) |
            engineManufacturerDiagnostics->toFrame(data, size) |
            engineManufacturerDiagnosticsEnhanced->toFrame(data, size) |
            heavyDutyOn_BoardDiagnostics_OBD_C->toFrame(data, size) |
            heavyDutyOn_BoardDiagnostics->toFrame(data, size) |
            worldWideHarmonizedOBD->toFrame(data, size) |
            heavyDutyEuroOBDStageIwithoutNOxcontrol->toFrame(data, size) |
            heavyDutyEuroOBDStageIwithNOxcontrol->toFrame(data, size) |
            heavyDutyEuroOBDStageIIwithoutNOxcontrol->toFrame(data, size) |
            heavyDutyEuroOBDStageIIwithNOxcontrol->toFrame(data, size) |
            brazilOBDPhase1->toFrame(data, size) |
            brazilOBDPhase2->toFrame(data, size) |
            koreanOBD->toFrame(data, size) |
            indiaOBDI->toFrame(data, size) |
            indiaOBDII->toFrame(data, size) |
            heavyDutyEuroOBDStageVI->toFrame(data, size);
    return data;
}

string OBDCompliance::getPrintableData() {
    return "OBD_II_CARB: " + oBD_II_CARB->getPrintableData() +
           "\nOBD_EPA: " + oBD_EPA->getPrintableData() +
           "\nOBD_and_OBD_II: " + oBD_and_OBD_II->getPrintableData() +
           "\nOBD_I: " + oBD_I->getPrintableData() +
           "\nNotOBDcompliant: " + notOBDcompliant->getPrintableData() +
           "\nEOBD: " + eOBD->getPrintableData() +
           "\nEOBDandOBD_II: " + eOBDandOBD_II->getPrintableData() +
           "\nEOBDandOBD: " + eOBDandOBD->getPrintableData() +
           "\nEOBD_OBD_and_OBDII: " + eOBD_OBD_and_OBDII->getPrintableData() +
           "\nJOBD: " + jOBD->getPrintableData() +
           "\nJOBDandOBDII: " + jOBDandOBDII->getPrintableData() +
           "\nJOBDandEOBD: " + jOBDandEOBD->getPrintableData() +
           "\nJOBD_EOBD_and_OBDII: " + jOBD_EOBD_and_OBDII->getPrintableData() +
           "\nEngineManufacturerDiagnostics: " + engineManufacturerDiagnostics->getPrintableData() +
           "\nEngineManufacturerDiagnosticsEnhanced: " + engineManufacturerDiagnosticsEnhanced->getPrintableData() +
           "\nHeavyDutyOn_BoardDiagnostics_OBD_C: " + heavyDutyOn_BoardDiagnostics_OBD_C->getPrintableData() +
           "\nHeavyDutyOn_BoardDiagnostics: " + heavyDutyOn_BoardDiagnostics->getPrintableData() +
           "\nWorldWideHarmonizedOBD: " + worldWideHarmonizedOBD->getPrintableData() +
           "\nHeavyDutyEuroOBDStageIwithoutNOxcontrol: " + heavyDutyEuroOBDStageIwithoutNOxcontrol->getPrintableData() +
           "\nHeavyDutyEuroOBDStageIwithNOxcontrol: " + heavyDutyEuroOBDStageIwithNOxcontrol->getPrintableData() +
           "\nHeavyDutyEuroOBDStageIIwithoutNOxcontrol: " +
           heavyDutyEuroOBDStageIIwithoutNOxcontrol->getPrintableData() +
           "\nHeavyDutyEuroOBDStageIIwithNOxcontrol: " + heavyDutyEuroOBDStageIIwithNOxcontrol->getPrintableData() +
           "\nBrazilOBDPhase1: " + brazilOBDPhase1->getPrintableData() +
           "\nBrazilOBDPhase2: " + brazilOBDPhase2->getPrintableData() +
           "\nKoreanOBD: " + koreanOBD->getPrintableData() +
           "\nIndiaOBDI: " + indiaOBDI->getPrintableData() +
           "\nIndiaOBDII: " + indiaOBDII->getPrintableData() +
           "\nHeavyDutyEuroOBDStageVI: " + heavyDutyEuroOBDStageVI->getPrintableData();
}

int OBDCompliance::setValueFromString(string data) {
    auto parts = splitString(const_cast<char *>(data.c_str()));
    const int paramCount = 28;
    if (paramCount > parts.size()) {
        LOG(ERROR) << "Insufficient parameter count expected " << paramCount;
        return paramCount;
    }


    oBD_II_CARB->setValueFromString(parts.at(0));
    oBD_EPA->setValueFromString(parts.at(1));
    oBD_and_OBD_II->setValueFromString(parts.at(2));
    oBD_I->setValueFromString(parts.at(3));
    notOBDcompliant->setValueFromString(parts.at(4));
    eOBD->setValueFromString(parts.at(5));
    eOBDandOBD_II->setValueFromString(parts.at(6));
    eOBDandOBD->setValueFromString(parts.at(7));
    eOBD_OBD_and_OBDII->setValueFromString(parts.at(8));
    jOBD->setValueFromString(parts.at(9));
    jOBDandOBDII->setValueFromString(parts.at(10));
    jOBDandEOBD->setValueFromString(parts.at(11));
    jOBD_EOBD_and_OBDII->setValueFromString(parts.at(12));
    engineManufacturerDiagnostics->setValueFromString(parts.at(13));
    engineManufacturerDiagnosticsEnhanced->setValueFromString(parts.at(14));
    heavyDutyOn_BoardDiagnostics_OBD_C->setValueFromString(parts.at(15));
    heavyDutyOn_BoardDiagnostics->setValueFromString(parts.at(16));
    worldWideHarmonizedOBD->setValueFromString(parts.at(17));
    heavyDutyEuroOBDStageIwithoutNOxcontrol->setValueFromString(parts.at(18));
    heavyDutyEuroOBDStageIwithNOxcontrol->setValueFromString(parts.at(19));
    heavyDutyEuroOBDStageIIwithoutNOxcontrol->setValueFromString(parts.at(20));
    heavyDutyEuroOBDStageIIwithNOxcontrol->setValueFromString(parts.at(21));
    brazilOBDPhase1->setValueFromString(parts.at(22));
    brazilOBDPhase2->setValueFromString(parts.at(23));
    koreanOBD->setValueFromString(parts.at(24));
    indiaOBDI->setValueFromString(parts.at(25));
    indiaOBDII->setValueFromString(parts.at(26));
    heavyDutyEuroOBDStageVI->setValueFromString(parts.at(27));

    return 0;
}

vector<DataObjectDescription *> OBDCompliance::getDescriptions() {
    return vector<DataObjectDescription *>{
            oBD_II_CARB->getDescriptions().at(0),
            oBD_EPA->getDescriptions().at(0),
            oBD_and_OBD_II->getDescriptions().at(0),
            oBD_I->getDescriptions().at(0),
            notOBDcompliant->getDescriptions().at(0),
            eOBD->getDescriptions().at(0),
            eOBDandOBD_II->getDescriptions().at(0),
            eOBDandOBD->getDescriptions().at(0),
            eOBD_OBD_and_OBDII->getDescriptions().at(0),
            jOBD->getDescriptions().at(0),
            jOBDandOBDII->getDescriptions().at(0),
            jOBDandEOBD->getDescriptions().at(0),
            jOBD_EOBD_and_OBDII->getDescriptions().at(0),
            engineManufacturerDiagnostics->getDescriptions().at(0),
            engineManufacturerDiagnosticsEnhanced->getDescriptions().at(0),
            heavyDutyOn_BoardDiagnostics_OBD_C->getDescriptions().at(0),
            heavyDutyOn_BoardDiagnostics->getDescriptions().at(0),
            worldWideHarmonizedOBD->getDescriptions().at(0),
            heavyDutyEuroOBDStageIwithoutNOxcontrol->getDescriptions().at(0),
            heavyDutyEuroOBDStageIwithNOxcontrol->getDescriptions().at(0),
            heavyDutyEuroOBDStageIIwithoutNOxcontrol->getDescriptions().at(0),
            heavyDutyEuroOBDStageIIwithNOxcontrol->getDescriptions().at(0),
            brazilOBDPhase1->getDescriptions().at(0),
            brazilOBDPhase2->getDescriptions().at(0),
            koreanOBD->getDescriptions().at(0),
            indiaOBDI->getDescriptions().at(0),
            indiaOBDII->getDescriptions().at(0),
            heavyDutyEuroOBDStageVI->getDescriptions().at(0)};
}