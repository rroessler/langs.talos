/// Forge Includes
#include "forge/crate/service.hpp"
#include "forge/crate/registry.hpp"
#include "forge/dylib/registry.hpp"

//  PUBLIC METHODS  //

const Forge::Crate::Manifest* Forge::Crate::Service::resolve(const $::Filesystem::Path& file_path) {
    return resolve($::URI::Buffer(file_path.string()));
}

const Forge::Crate::Manifest* Forge::Crate::Service::resolve(const $::URI::View& resource) {
    // resolve the key to be used currently
    auto key = $::String::Buffer(resource.view());

    // check if the resource is currently available
    if (m_crates.contains(key)) return m_crates.at(key).get();

    // and emplace the crate-file now
    return m_crates.emplace(key, Registry::view(resource)).first->second.get();
}

Forge::Value::Any Forge::Crate::Service::dylib(Runtime::Isolate* isolate, const $::String::View& name) const noexcept {
    return Dylib::Registry::preload(isolate, name);
}
