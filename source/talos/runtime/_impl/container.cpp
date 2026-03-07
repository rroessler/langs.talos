/// Talos Modules
#include "talos/runtime/container.hpp"

/// Talos Services
#include "talos/async/service.hpp"
#include "talos/builtins/service.hpp"
#include "talos/crate/service.hpp"
#include "talos/document/service.hpp"
#include "talos/lifecycle/service.hpp"
#include "talos/locale/service.hpp"
#include "talos/machine/service.hpp"
#include "talos/module/service.hpp"
#include "talos/relint/service.hpp"
#include "talos/shape/service.hpp"
#include "talos/signal/service.hpp"

//  CONSTRUCTORS  //

Talos::Runtime::Container::Container(const Options& options) {
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
