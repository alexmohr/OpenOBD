//
// Created by me on 04/02/19.
//

#ifndef OPEN_OBD2_ERRORTYPE_H
#define OPEN_OBD2_ERRORTYPE_H
enum ErrorType {
    SUCCESS = 0,
    TOO_LARGE = 2,
    TOO_SMALL = 4,
    INVALID_NUMBER = 8,
    MISSING_ARGUMENTS = 16,
    NOT_SUPPORTED = 32,
    DATA_ERROR = 64,
    TIMEOUT = 128,
};

#endif //OPEN_OBD2_ERRORTYPE_H
