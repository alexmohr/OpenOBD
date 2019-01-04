//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_OBDHANDLER_H
#define OPEN_OBD2_OBDHANDLER_H

#include "../Config.h"
#include "../Vehicle.h"

#define ANSWER_OFFSET 0x40

class OBDHandler{
private:

    unique_ptr<Vehicle> vehicle;
    unique_ptr<Vehicle> vehicleFreezeFrame;
    unique_ptr<map<Service, PidCollection>> pidConfig;
public:
    explicit OBDHandler(unique_ptr<map<Service, PidCollection>> pidConfig, map<int, DataTroubleCode> dtcMap);

    /**
     * Create a response for a request
     * @param request The data of the requst
     * @return data which can be send via can.
     */
    byte *createAnswerFrame(byte *request, int &size);

    byte *createAnswerFrame(Service service, Pid pid, byte *data, int &size);

    /**
     * Updates the vehicle with received data.
     * @param frame The CAN frame received which contains the data.
     */
    void updateFromFrame(byte *frame, int i);

    Vehicle * getVehicle();

    Vehicle *getVehicleFreezeFrame();

    int getFrameInfo(int pidId, int serviceId, Pid &pid, Service &service);


};

#endif //OPEN_OBD2_OBDHANDLER_H
