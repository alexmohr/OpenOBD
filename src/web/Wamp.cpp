//
// Created by me on 27/01/19.
//

#include "Wamp.h"

void Wamp::foo() {
    /* Create the wampcc kernel. */

    wampcc::kernel the_kernel;

    /* Create an embedded wamp router. */

    wampcc::wamp_router router(&the_kernel);
}
