/// Talos Includes
#include "talos/crate/service.hpp"
#include "talos/crate/registry.hpp"
#include "talos/dylib/registry.hpp"

//  PUBLIC METHODS  //

const Talos::Crate::Manifest* Talos::Crate::Service::resolve(const $::Filesystem::Path& file_path) {
    return resolve($::URI::Buffer(file_path.string()));
}

const Talos::Crate::Manifest* Talos::Crate::Service::resolve(const $::URI::View& resource) {
    // resolve the key to be used currently
    auto key = $::String::Buffer(resource.view());

    // check if the resource is currently available
    if (m_crates.contains(key)) return m_crates.at(key).get();

    // and emplace the crate-file now
    return m_crates.emplace(key, Registry::view(resource)).first->second.get();
}

Talos::Value::Any Talos::Crate::Service::dylib(Runtime::Isolate* isolate, const $::String::View& name) const noexcept {
    return Dylib::Registry::preload(isolate, name);
}
