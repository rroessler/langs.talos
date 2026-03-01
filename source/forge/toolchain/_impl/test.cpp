/// Forge Modules
#include "forge/toolchain/test.hpp"
#include "forge/runtime/container.hpp"
#include "forge/toolchain/launch.hpp"

/// Service Modules
#include "forge/garbage/service.hpp"
#include "forge/globals/service.hpp"
#include "forge/heap/service.hpp"
#include "forge/testing/registry.hpp"
#include "forge/testing/service.hpp"

//  PUBLIC METHODS  //

int32_t Forge::Toolchain::test(const Runtime::Options& options) {
    // prepare the services container to be used
    auto* services = bootstrap(options);

    // pre-build the testing options to be used
    auto* session = services->emplace<XT::Session::Options>();

    // override the session options to be used now
    session->bench = options.testing.bench;
    session->title = FORGE_MM_IDENTIFIER "/testing";
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
