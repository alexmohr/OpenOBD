//
// Created by me on 28/12/18.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#ifndef OPEN_OBD2_COMMANDEDSECONDARYAIRSTATUS_H
#define OPEN_OBD2_COMMANDEDSECONDARYAIRSTATUS_H


enum StateOfCommandedSecondaryAir {
    CommandedSecondaryAirStatusDoesNotExist = 0,
    Upstream = 1,
    DownstreamOfCatalyticConverter = 2,
    FromTheOutsideAtmosphereOrOff = 4,
    PumpCommandedOnForDiagnostics = 8,
};


#endif //OPEN_OBD2_COMMANDEDSECONDARYAIRSTATUS_H

#pragma clang diagnostic pop