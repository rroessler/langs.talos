/// Forge Includes
#include "forge/crate/registry.hpp"
#include "forge/crate/constants.hpp"
#include "forge/document/buffer.hpp"

//  PUBLIC METHODS  //

$::Ptr::Unique<Forge::Crate::Manifest> Forge::Crate::Registry::global() { return $::New().unique<Manifest>(); }

$::Ptr::Unique<Forge::Crate::Manifest> Forge::Crate::Registry::scan(const $::URI::View& hint) {
    return hint.scheme() == $::URI::Scheme::FILE ? scan(hint.body()) : global();
}

$::Ptr::Unique<Forge::Crate::Manifest> Forge::Crate::Registry::scan(const $::Filesystem::Path& hint) {
    // prepare the parent path to be used
    auto parent = hint;

    // attempt scanning upwards for a suitable crate-file
    auto query = hint / Crate::Constants::filename();
    auto root = $::Filesystem::Path().root_path();

    // iterate over the available paths now
    while (!$::Path::exists(query) && parent != root) {
        parent = $::Path::dirname(parent);  // jump
        query = parent / Crate::Constants::filename();
    }

    // and attempt resolving whether the query exists or not
    return $::Path::exists(query) ? view(query) : global();
}

$::Ptr::Unique<Forge::Crate::Manifest> Forge::Crate::Registry::view(const $::Filesystem::Path& file_path) {
    return view($::URI::Buffer(file_path.string()));
}

$::Ptr::Unique<Forge::Crate::Manifest> Forge::Crate::Registry::view(const $::URI::View& resource) {
    // prepare the buffer to be read now
    auto buffer = Document::Buffer(resource);
    auto json = $::JSON::parse(buffer.view(), true);

    // fail early if there are any JSONC errors found
    if (!json.has_value()) return nullptr;

    // and attempt decoding into our instance now
    auto path = $::Path::dirname(resource.body()).string();
    auto crate = $::Reflect::decode<Manifest>(json.value(), path);

    // and return the resulting crate instance now
    return $::New().unique<Manifest>(std::move(crate));
}
