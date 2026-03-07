/// Talos Modules
#include "talos/toolchain/serve.hpp"
#include "talos/lifecycle/service.hpp"
#include "talos/runtime/container.hpp"
#include "talos/server/connection.hpp"

//  PUBLIC METHODS  //

int32_t Talos::Toolchain::serve(const Runtime::Options& options) {
    // prepare the services container to be used
    auto* services = $::Global::get<Runtime::Container>(options);

    // ensure we scope a lifecycle for preloading certain functionality
    $_UNUSED $_AUTO = services->get<Lifecycle::Service>()->scope();

    // get the underlying connection instance to be run
    return services->emplace<Server::Connection>()->listen();
}
