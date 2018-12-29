//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_OBDHANDLER_H
#define OPEN_OBD2_OBDHANDLER_H

#include "../Config.h"
#include "../Vehicle.h"


class OBDHandler{
private:
    const int ANSWER_OFFSET = 0x40;
    Vehicle *vehicle;
    Vehicle *vehicleFreezeFrame;
    unique_ptr<map<Service, PidCollection>> pidConfig;
public:
    OBDHandler(Vehicle *vehicle, Vehicle *vehicleFreezeFrame, unique_ptr<map<Service, PidCollection>> pidConfig);

    /**
     * Create a response for a request
     * @param frame The data of the requst
     * @return data which can be send via can.
     */
    byte* createAnswerFrame(byte *frame);

    /**
     * Updates the vehicle with received data.
     * @param frame The CAN frame received which contains the data.
     */
    void updateFromFrame(byte *frame, int i);

    Vehicle * getVehicle();

    void getFrameInfo(const byte *frame, int serviceId, Pid &pid, Service &service);
};

#endif //OPEN_OBD2_OBDHANDLER_H
