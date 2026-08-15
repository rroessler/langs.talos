/// Talos Includes
#include "talos/runtime/container.hpp"
#include "talos/runtime/options.hpp"
#include "talos/type/world.hpp"

/// Service Includes
#include "talos/async/service.hpp"
#include "talos/crate/service.hpp"
#include "talos/document/service.hpp"
#include "talos/garbage/service.hpp"
#include "talos/globals/service.hpp"
#include "talos/heap/service.hpp"
#include "talos/import/service.hpp"
#include "talos/lifecycle/service.hpp"
#include "talos/locale/service.hpp"
#include "talos/machine/service.hpp"
#include "talos/relint/service.hpp"
#include "talos/shape/service.hpp"
#include "talos/signal/service.hpp"

//  CONSTRUCTORS  //

Talos::Runtime::Container::Container() : Container({}) {}
Talos::Runtime::Container::Container(const Options &options) {
  // bind the options to the service
  bind<Options>(options);

  // bind all the common services for the container
  bind<Async::Service>();
  bind<Locale::Service>();
  bind<Signal::Service>();
  bind<Import::Service>();
  bind<Crate::Service>();
  bind<Shape::Service>();
  bind<Relint::Service>();
  bind<Document::Service>();
  bind<Lifecycle::Service>();

  // post-bind the runtime specialized services
  bind<Heap::Service>();
  bind<Garbage::Service>();
  bind<Globals::Service>();
  bind<Machine::Service>();
}
