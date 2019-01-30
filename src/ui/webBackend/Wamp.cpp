//
// Created by me on 27/01/19.
//

#include "Wamp.h"

void Wamp::foo() {
    try {
        /* Create the wampcc kernel. */

        wampcc::kernel the_kernel;

        /* Create an embedded wamp router. */

        wampcc::wamp_router router(&the_kernel);

        /* Accept clients on IPv4 port, without authentication. */

        auto fut = router.listen(wampcc::auth_provider::no_auth_required(), 55555);

        if (auto ec = fut.get()) {
            throw std::runtime_error(ec.message());
        }

        /* Provide an RPC named 'greeting' on realm 'default_realm'. */

        router.callable(REALM, "greeting",
                        [](
                                wampcc::wamp_router &, wampcc::wamp_session &caller, wampcc::call_info info) {
                            caller.result(info.request_id, {"hello"});
                        });

        /* Suspend main thread */
        std::promise<void> forever;
        forever.get_future().wait();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return;
    }
}
