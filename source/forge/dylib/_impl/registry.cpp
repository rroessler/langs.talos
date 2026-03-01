/// Forge Modules
#include "forge/dylib/registry.hpp"
#include "forge/runtime/isolate.hpp"

//  PUBLIC METHODS  //

Forge::Dylib::Addon *Forge::Dylib::Registry::install($::Ptr::Unique<Addon> &&addon) {
    // get the underlying name of the installer now
    auto *self = s_instance();
    auto name = addon->name();

    // ensure we lock emplacement
    $_UNUSED $_AUTO = $::Lock::guard(self->m_mutex);

    // ensure the emplacement is actually valid to be done
    $_ASSERT(!bound(name), "Library '{0}' already installed", name);
    $_TRACE("Dylib::Registry: Installing '{0}'", name);  // report

    // and register the library for use
    return self->m_addons.emplace(name, std::move(addon)).first->second.get();
}

Forge::Value::Any Forge::Dylib::Registry::preload(Runtime::Isolate *isolate, const $::String::View &name) {
    const auto *self = s_instance();  // get instance
    $_UNUSED $_AUTO = $::Lock::guard(self->m_mutex);

    // declare an error for missing libraries if necessary here
    if (!bound(name)) return isolate->panic(8000100, fmt::format("dylib:{0}", name));

    $_TRACE("Dylib::Registry: Loading '{0}'", name);
    return self->m_addons.at(name)->preload(isolate);
}

void Forge::Dylib::Registry::unload(Runtime::Isolate *isolate, const $::String::View &name) {
    const auto *self = s_instance();  // get instance
    $_UNUSED $_AUTO = $::Lock::guard(self->m_mutex);
    if (!bound(name)) return;  // ignore if not bound

    $_TRACE("Dylib::Registry: Unloading '{0}'", name);
    return self->m_addons.at(name)->unload(isolate);
}

//  PRIVATE METHODS  //

Forge::Lifecycle::Service *Forge::Dylib::Registry::m_lifecycle(Runtime::Isolate *isolate) {
    return isolate->service<Lifecycle::Service>();
}
