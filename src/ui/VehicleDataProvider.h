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


class VehicleDataProvider {
private:
    shared_ptr<OBDHandler> obdHandler;
    shared_ptr<ICommunicationInterface> comInterface;
private:
    vector<Service1Pids> pidIds{
            SupportedPid01_20, SupportedPid21_40, SupportedPid41_60, SupportedPid61_80,
            SupportedPid81_A0, SupportedPidA1_C0, SupportedPidC1_E0,
    };

    vector<Service> services{
            POWERTRAIN,
            FREEZE_FRAME,
//            CONFIRMED_DTCS,
//            CLEAR_DTCS,
//            OXYGEN_SENSOR,
//            ONBOARD_MONITORING_TESTS,
//            EMISSION_RELATED_DTC,
//            ENABLE_OFF_BOARD_DIAGNOSIS,
//            VEHICLE_INFORMATION,
            //         EMISSION_RELATED_PERMANENT_DTC,
    };

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

    bool configureVehicle() const;

    bool getPid(const string &pidName, Pid &pid, Service &service) const;

    DataObjectState getPrintableDataForPid(bool freezeFrameVehicle, Pid &pid, string &value) const;
};


#endif //OPEN_OBD2_VEHICLEDATAPROVIDER_H
