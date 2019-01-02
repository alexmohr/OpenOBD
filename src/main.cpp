#include <iostream>
#include <map>
#include <string>
#include "easylogging++.h"
#include "Config.h"
#include "CAN/CanIsoTP.h"

#include "OBD/OBDHandler.h"

INITIALIZE_EASYLOGGINGPP

int exit_code = EXIT_SUCCESS;
bool exitRequested = false;

static void handleSignal(const int signum) {
    switch (signum) {

        case SIGUSR1:
            /* exit parent */
            exit(EXIT_SUCCESS);
            // no break needed due to exit
        case SIGALRM:
        case SIGCHLD:
            LOG(INFO) << "received signal " << signum;
            exit_code = EXIT_FAILURE;
            exitRequested = true;
            break;
        case SIGINT:
        case SIGTERM:
            LOG(INFO) << "received signal " << signum;
            exit_code = EXIT_SUCCESS;
            exitRequested = true;
            break;
        default:
            break;
    }
}


int main() {
    /* Trap signals that we expect to receive */
    signal(SIGINT, handleSignal);
    signal(SIGTERM, handleSignal);


    return 0;
}
