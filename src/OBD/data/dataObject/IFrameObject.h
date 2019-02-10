//
// Created by me on 31/12/18.
//

#ifndef OPEN_OBD2_IFRAMEOBJECT_H
#define OPEN_OBD2_IFRAMEOBJECT_H

#include <cstddef>
#include "DataObjectDescription.h"
#include "DataObjectState.h"
#include "DataObjectStateFactory.h"
#include "DataObjectValue.h"

using namespace std;


class IFrameObject {
public:
    /**
     * Convert the object into a CAN frame.
     * @param data Reference to data were the values will be written to
     * @param size The size of the data. size is in BITS!
     * @return Modified data.
     */
    virtual unsigned int toFrame(unsigned int &data, int &size) = 0;

    /**
     * Reads the data from a frame.
     * @param data The data to read from
     * @param size size of the data buffer.
     */
    virtual void fromFrame(byte *data, int size) = 0;

    /**
     * Gets the object state in string form.
     * This is currently used in the CLI
     * @return A string representing the current state of the object
     */
    virtual shared_ptr<DataObjectValueCollection> getDataObjectValue() = 0;

    /**
     * Sets the object value from string.
     * @param data The data which is set.
     * @return 0 on Success; Number greater 0 for error due to wrong parameter count less than 0 due to other error.
     */
    virtual DataObjectStateCollection setValueFromString(string data) = 0;

    virtual vector<DataObjectDescription *> getDescriptions() = 0;
};

#endif //OPEN_OBD2_IFRAMEOBJECT_H
