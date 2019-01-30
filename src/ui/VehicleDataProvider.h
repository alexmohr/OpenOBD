//
// Created by me on 30/01/19.
//

#ifndef OPEN_OBD2_VEHICLEDATAPROVIDER_H
#define OPEN_OBD2_VEHICLEDATAPROVIDER_H

#include <thread>
#include <memory>
#include "../OBD/data/dataObject/DataObjectState.h"
#include "../OBD/Pid.h"
#include "../OBD/OBDHandler.h"
#include "../OBD/Service.h"
#include "CommandInfo.h"


class VehicleDataProvider {
private:
    shared_ptr<OBDHandler> obdHandler;
    shared_ptr<ICommunicationInterface> comInterface;

public:
    VehicleDataProvider(shared_ptr<OBDHandler> obdHandler,
                        shared_ptr<ICommunicationInterface> comInterface);

    ~VehicleDataProvider() = default;

public:
    /**
     * Queries the vehicle and updates internal stored object
     * @param pid The pid which will be queried
     * @param service The service to query.
     * @return Indicates state.
     */
    DataObjectState queryVehicle(Pid pid, Service service) const;

    vector<string> getSupportedPids() const;

    bool configureVehicle() const;
};


#endif //OPEN_OBD2_VEHICLEDATAPROVIDER_H
