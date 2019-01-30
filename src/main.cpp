#include <iostream>

#include <map>
#include <string>
#include "easylogging++.h"
#include "ui/cli/CliHandler.h"


INITIALIZE_EASYLOGGINGPP

static int exit_code = EXIT_SUCCESS;
static bool exitRequested = false;

static void handleSignal(const int signum) {
    switch (signum) {

        case SIGUSR1:
            /* exit parent */
            exit(EXIT_SUCCESS);
            // no break needed due to exit
        case SIGALRM:
        case SIGCHLD:
            LOG(DEBUG) << "received signal " << signum;
            exit_code = EXIT_FAILURE;
            exitRequested = true;
            break;
        case SIGINT:
        case SIGTERM:
            LOG(DEBUG) << "received signal " << signum;
            exit_code = EXIT_SUCCESS;
            exitRequested = true;
            break;
        default:
            break;
    }
}


int main(int argc, char *argv[]) {
    /* Trap signals that we expect to receive */
    signal(SIGINT, handleSignal);
    signal(SIGTERM, handleSignal);

    CliHandler handler = CliHandler();
    if (EXIT_SUCCESS != handler.openCli(argc, argv)) {
        return EXIT_FAILURE;
    }

    while (handler.isOpen()) {
        if (exitRequested || handler.isExitRequested()) {
            handler.closeCli();
        }
        sleep(1);
    }

    return 0;
}
