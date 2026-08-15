/// Talos Includes
#include "talos/lifecycle/service.hpp"
#include "talos/async/service.hpp"
#include "talos/dylib/registry.hpp"
#include "talos/globals/service.hpp"
#include "talos/import/service.hpp"
#include "talos/runtime/container.hpp"
#include "talos/runtime/executor.hpp"

/// Builtin Includes
#include "talos/builtins/_inline/builtins.ipp"

//  CONSTRUCTORS  //

Talos::Lifecycle::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Talos::Lifecycle::Service::Service(XI::Container *services) : m_services(services) {}

//  PUBLIC METHODS  //

Talos::Lifecycle::Scope Talos::Lifecycle::Service::scope(Runtime::Isolate *isolate) {
  return Scope(m_services, isolate);
}

void Talos::Lifecycle::Service::preload(Runtime::Isolate *isolate) {
  // get the available global service now
  Async::Service *async = *m_services;
  Import::Service *modules = *m_services;
  Globals::Service *globals = *m_services;

  // we need to pre-instantiate the "Object" global (to ensure class ordering)
  globals->get(isolate, Builtins::Inspect<Object::Instance>::name());

  // we need our roots service for help with garbage collection
  auto *roots = globals->roots();

  // register all the "dylib" modules as well
  roots->bind([](Globals::Each &yield) { Dylib::Registry::each(yield); });

  // all runtime isolates must have access to their roots
  roots->bind([async](Globals::Each &yield) {
    for (const auto &thread : async->scheduler()->threads()) {
      if (!thread->is<Runtime::Executor>()) continue; // cast now as needed
      reinterpret_cast<Runtime::Executor *>(thread->task())->roots(yield);
    }
  });

  // register all the modules with access to their roots
  roots->bind([modules](Globals::Each &yield) {
    for (const auto &module : modules->storage()->each()) {
      auto *exports = module->metadata<Module::Phase::EXPORTED>();
      for (auto &scope : exports->scopes()) yield(scope);
      auto *deferred = exports->thenable(); // resolve now
      if (!deferred->pending()) yield(deferred->immediate());
    }
  });
}

void Talos::Lifecycle::Service::unload(Runtime::Isolate *) {
  for (const auto &disposable : m_disposables | std::views::values) disposable();
  m_disposables.clear(); // and remove the disposables now since all finalized
}
