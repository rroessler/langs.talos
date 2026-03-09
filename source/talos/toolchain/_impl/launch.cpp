/// Talos Modules
#include "talos/toolchain/launch.hpp"
#include "talos/bundle/archive.hpp"
#include "talos/bundle/fuse.hpp"
#include "talos/module/service.hpp"
#include "talos/runtime/container.hpp"

/// Service Modules
#include "talos/garbage/service.hpp"
#include "talos/globals/service.hpp"
#include "talos/heap/service.hpp"
#include "talos/runtime/service.hpp"

/// Forward Declarations
$_FWD(Talos::Toolchain, int32_t launch(XI::Container*))

//  PUBLIC METHODS  //

/// @brief Handles bootstrapping the baseline runtime.
XI::Container* Talos::Toolchain::bootstrap(const Runtime::Options& options) {
    // prepare the services container to be used
    auto* services = $::Global::get<Runtime::Container>(options);

    // bind some additional "run" only services
    services->bind<Heap::Service>();
    services->bind<Garbage::Service>();
    services->bind<Globals::Service>();

    // and return the underlying services now
    return services;
}

int32_t Talos::Toolchain::launch(XI::Container* services) { return services->emplace<Runtime::Service>()->launch(); }
int32_t Talos::Toolchain::launch(const Runtime::Options& options) { return launch(bootstrap(options)); }
int32_t Talos::Toolchain::launch(int32_t argc, char** argv) {
    // prepare the archive and options
    auto archive = Bundle::Archive();
    auto options = Runtime::Options();

    // we want to decode the incoming filesystem
    auto filesystem = archive.decode(Fuse::BUNDLED);

    // prepare the baseline bundled options
    options.flags.typeless = true;

    // prepare the script entry to be used from the filesystem
    options.script.argv = { argv, argv + argc };
    options.script.entry = filesystem.resources.front().view();

    // bootstrap the runtime options now
    auto* services = bootstrap(options);

    // ensure we preload the archived modules
    auto* modules = services->get<Import::Service>();
    modules->preload(std::move(filesystem.scripts));

    // and attempt launching the runtime now
    return launch(services);
}
