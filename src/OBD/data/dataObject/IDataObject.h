//
// Created by me on 06/01/19.
//

#ifndef OPEN_OBD2_IDATAOBJECT_H
#define OPEN_OBD2_IDATAOBJECT_H

#include "DataObjectState.h"

template<class T>
class IDataObject {
public:
    virtual T getValue() = 0;

    virtual DataObjectState setValue(T value) = 0;

    /**
     * Sets the object value from string.
     * @param data The data which is set.
     * @return 0 on Success; Number greater 0 for error due to wrong parameter count less than 0 due to other error.
     */
    virtual DataObjectStateCollection setValueFromString(string data) = 0;

    virtual vector<DataObjectDescription *> getDescriptions() = 0;

};

#endif //OPEN_OBD2_IDATAOBJECT_H
