#include <iostream>

#include <map>
#include <string>
#include "easylogging++.h"
#include "cli/CliHandling.h"


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
            LOG(ERROR) << "bar";
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

    CliHandling handler = CliHandling();
    if (EXIT_SUCCESS != handler.openCli(argc, argv)) {
        return EXIT_FAILURE;
    }

    while (handler.isOpen()) {
        if (exitRequested) {
            handler.closeCli();
        }
        sleep(1);
    }

    return 0;
}
