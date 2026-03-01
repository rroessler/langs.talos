/// Forge Modules
#include "forge/runtime/container.hpp"

/// Forge Services
#include "forge/async/service.hpp"
#include "forge/builtins/service.hpp"
#include "forge/crate/service.hpp"
#include "forge/document/service.hpp"
#include "forge/lifecycle/service.hpp"
#include "forge/locale/service.hpp"
#include "forge/machine/service.hpp"
#include "forge/module/service.hpp"
#include "forge/relint/service.hpp"
#include "forge/shape/service.hpp"
#include "forge/signal/service.hpp"

//  CONSTRUCTORS  //

Forge::Runtime::Container::Container(const Options& options) {
    // bind the options to the service
    bind<Options>(options);

    // and bind all the common services (for "run", "test" and "serve")
    bind<Async::Service>();
    bind<Crate::Service>();
    bind<Shape::Service>();
    bind<Locale::Service>();
    bind<Import::Service>();
    bind<Relint::Service>();
    bind<Signal::Service>();
    bind<Machine::Service>();
    bind<Document::Service>();
    bind<Builtins::Service>();
    bind<Lifecycle::Service>();
}
