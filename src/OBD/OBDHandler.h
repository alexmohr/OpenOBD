//
// Created by me on 13/12/18.
//

#ifndef OPEN_OBD2_OBDHANDLER_H
#define OPEN_OBD2_OBDHANDLER_H

#include "../Config.h"
#include "../Vehicle.h"

#define ANSWER_OFFSET 0x40
#define NEGATIVE_RESPONSE 0x7F
#define SUB_FUNCTION_NOT_SUPPORTED 0x12
#define INCORRECT_MESSAGE_LENGTH_OR_FORMAT 0x13
#define CONDITIONS_NOT_CORRECT 0x22
#define SECURITY_ACCESS_DENIED 0x33


class OBDHandler {
private:

    unique_ptr<Vehicle> vehicle;
    unique_ptr<Vehicle> vehicleFreezeFrame;
    unique_ptr<map<Service, PidCollection>> pidConfig;
public:
    explicit OBDHandler(unique_ptr<map<Service, PidCollection>> pidConfig, map<int, DataTroubleCode> dtcMap);

    static shared_ptr<OBDHandler> createInstance();

    /**
     * Create a response for a request
     * @param request The data of the requst
     * @return data which can be send via can.
     */
    byte *createAnswerFrame(byte *request, int &size);

    byte *createAnswerFrame(Service service, Pid pid, byte *data, int &size);

    byte *createErrorFrame(int type, int &size, byte &attemptedFunction);

    /**
     * Updates the vehicle with received data.
     * @param frame The CAN frame received which contains the data.
     */
    void updateFromFrame(byte *frame, int i);

    Vehicle *getVehicle();

    Vehicle *getFreezeFrameVehicle();

    ErrorType getServiceAndPidInfo(int pidId, int serviceId, Pid &pid, Service &service);

    DataObjectState isPidSupported(Service service, int pid);
};

#endif //OPEN_OBD2_OBDHANDLER_H
