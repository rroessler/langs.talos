/// Talos Modules
#include "talos/toolchain/test.hpp"
#include "talos/runtime/container.hpp"
#include "talos/toolchain/launch.hpp"

/// Service Modules
#include "talos/garbage/service.hpp"
#include "talos/globals/service.hpp"
#include "talos/heap/service.hpp"
#include "talos/testing/registry.hpp"
#include "talos/testing/service.hpp"

//  PUBLIC METHODS  //

int32_t Talos::Toolchain::test(const Runtime::Options& options) {
    // prepare the services container to be used
    auto* services = bootstrap(options);

    // pre-build the testing options to be used
    auto* session = services->emplace<XT::Session::Options>();

    // override the session options to be used now
    session->bench = options.testing.bench;
    session->title = TALOS_MM_IDENTIFIER "/testing";
    session->spinner = [](XI::Container* services) {
        static $::Spinner::Options s_options = {};  // base options
        return services->get<Async::Service>()->spinner(s_options);
    };

    // bind the testing specific services
    services->bind<Testing::Session>();
    services->bind<Testing::Registry>();

    // get the underlying testing service to run
    return services->emplace<Testing::Service>()->launch();
}
