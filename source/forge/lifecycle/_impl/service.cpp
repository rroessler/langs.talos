/// Forge Modules
#include "forge/globals/service.hpp"
#include "forge/async/service.hpp"
#include "forge/crate/constants.hpp"
#include "forge/dylib/registry.hpp"
#include "forge/engine/metadata.hpp"
#include "forge/lifecycle/service.hpp"
#include "forge/module/service.hpp"
#include "forge/runtime/container.hpp"
#include "forge/runtime/executor.hpp"
#include "forge/runtime/isolate.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/builtins.ipp"

//  CONSTRUCTORS  //

Forge::Lifecycle::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Forge::Lifecycle::Service::Service(XI::Container* services) : m_services(services) {}

//  PUBLIC METHODS  //

Forge::Lifecycle::Scope Forge::Lifecycle::Service::scope(Runtime::Isolate* isolate) {
    return Scope(m_services, isolate);
}

void Forge::Lifecycle::Service::preload(Runtime::Isolate* isolate) {
    // stop if the isolate is currently empty
    if (isolate == nullptr) return;

    // and instantiate all the necessary isolate-based services
    m_globals(isolate);
}

void Forge::Lifecycle::Service::unload(Runtime::Isolate*) {
    for (const auto& disposable : m_disposables | std::views::values) disposable();
    m_disposables.clear();  // and remove the disposables now as necessary
}

//  PRIVATE METHODS  //

void Forge::Lifecycle::Service::m_globals(Runtime::Isolate* isolate) {
    // ensure the globals actually exist to begin with
    auto* globals = m_services->when<Globals::Service>();

    // if they do not, then we do nothing here
    if (globals == nullptr) return;

    // otherwise we need to pre-instantiate the "Object" global
    isolate->global(Value::Symbol(Builtins::Proxy<Object::Instance>::name()));

    // and we need to register certain items for their GC roots
    auto* async = m_services->get<Async::Service>();
    auto* modules = m_services->get<Import::Service>();

    // register all the "dylib" modules as well
    globals->roots()->bind([](const Globals::Each& yield) { Dylib::Registry::each(yield); });

    // all runtime isolates must have access to their roots
    globals->roots()->bind([async](const Globals::Each& yield) {
        for (const auto& thread : async->scheduler()->threads()) {
            if (!thread->is<Runtime::Executor>()) continue;  // cast now
            reinterpret_cast<Runtime::Executor*>(thread->task())->roots(yield);
        }
    });

    // register all the modules with access to their roots
    globals->roots()->bind([modules](const Globals::Each& yield) {
        for (const auto& module : modules->drafts()->each()) {
            auto* exports = module->metadata<Module::Phase::EXPORTED>();
            for (auto& scope : exports->scopes()) yield(scope);

            auto* deferred = exports->deferred();  // resolve now
            if (!deferred->pending()) yield(deferred->immediate());
        }
    });
}
