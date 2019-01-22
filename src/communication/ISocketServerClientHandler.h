//
// Created by me on 22/01/19.
//

#ifndef OPEN_OBD2_ISOCKETSERVERCLIENTHANDLER_H
#define OPEN_OBD2_ISOCKETSERVERCLIENTHANDLER_H

class ISocketServerClientHandler {
public:
    virtual void handleClient(int clientSocketHandle) = 0;
};

#endif //OPEN_OBD2_ISOCKETSERVERCLIENTHANDLER_H
