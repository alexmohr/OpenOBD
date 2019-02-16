//
// Created by me on 08/01/19.
//

#ifndef OPEN_OBD2_SupportedPidCollection_H
#define OPEN_OBD2_SupportedPidCollection_H


#include "../../dataObject/DataObject.h"


class SupportedPidCollection : public IFrameObject {
private:
    unique_ptr<vector<DataObject<bool>>> supportedPids;
public:
    SupportedPidCollection(int offset);

    vector<DataObject<bool>> &getSupportedPids();

public: // IFrameObject
    /**
   * Convert the object into a CAN frame.
   * @param data Reference to data were the values will be written to
   * @param size The size of the data. size is in BITS!
   * @return Modified data.
   */
    unsigned int toFrame(unsigned int &data, int &size) override;

    /**
     * Reads the data from a frame.
     * @param data The data to read from
     * @param size size of the data buffer.
     */
    void fromFrame(byte *data, int size) override;

    /**
     * Gets the object state in string form.
     * This is currently used in the CLI
     * @return A string representing the current state of the object
     */
    shared_ptr<DataObjectValueCollection> getDataObjectValue() override;

    /**
     * Sets the object value from string.
     * @param data The data which is set.
     * @return 0 on Success; Number greater 0 for error due to wrong parameter count less than 0 due to other error.
     */
    DataObjectStateCollection setValueFromString(string data) override;

    vector<DataObjectDescription *> getDescriptions() override;
};


#endif //OPEN_OBD2_SupportedPidCollection_H
