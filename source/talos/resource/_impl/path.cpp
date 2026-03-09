/// Talos Includes
#include "talos/resource/path.hpp"
#include "talos/crate/constants.hpp"
#include "talos/diagnostic/traits.hpp"

/// Forward Declarations
$_FWD(Talos::Resource::Path, template <class... As> Result failure(Diagnostic::Code, As&&...))

//  MACROS  //

#define MM_MISSING(_, ...) failure(8000100, $::String::Buffer(_) __VA_ARGS__)

//  PUBLIC METHODS  //

template <class... As>
Talos::Resource::Result Talos::Resource::Path::failure(Diagnostic::Code code, As&&... args) {
    return std::unexpected(Diagnostic::Traits::format(code, std::forward<As>(args)...));
}

Talos::Resource::Result Talos::Resource::Path::resolve(const $::URI::View& resource, const $::Filesystem::Path& hint) {
#define X(N, S, ...) \
    case XH::FNV::U32(S): return resolve<Scheme::N>(resource.body(), hint);
    switch (XH::FNV::U32(resource.scheme())) {
        TALOS_XX_RESOURCE_SCHEMES(X)  // valid resource schemes
        default: return failure(8000801, resource.scheme());
    }
#undef X
}

Talos::Resource::Result Talos::Resource::Path::resolve(const $::String::View& script, const $::Filesystem::Path& hint) {
    return resolve($::URI::Codec::parse(script), hint);
}

//  SPECIALIZATIONS  //

template <>
Talos::Resource::Result Talos::Resource::Path::resolve<Talos::Resource::Scheme::HREF>(
    const $::String::View& relative, const $::Filesystem::Path& hint) {
    if ($::Trim::both(relative).empty()) return failure(8000100, relative);
    auto absolute = $::Path::absolute(relative, hint);  // get absolute path here now
    return absolute.empty() ? MM_MISSING(relative) : resolve<Scheme::SCRIPT>(absolute.string());
}

template <>
Talos::Resource::Result Talos::Resource::Path::resolve<Talos::Resource::Scheme::SCRIPT>(
    const $::String::View& absolute, const $::Filesystem::Path&) {
    // prepare a suitable relative path
    auto relative = $::Path::relative(absolute);

    // ensure the file-path actually exists now
    if (!$::Path::exists(absolute)) return failure(8000100, relative.string());

    // check if we do not have a directory value now
    if (!$::Path::is_directory(absolute)) return $::URI::Buffer(absolute);

    // otherwise we attempt resolving as a crate-file now
    auto crate = $::Path::join(absolute, Crate::Constants::filename());

    // ensure that this one exists as well before we continue
    return $::Path::exists(crate) ? $::URI::Buffer(crate.string()) : MM_MISSING(relative.string());
}

template <>
Talos::Resource::Result Talos::Resource::Path::resolve<Talos::Resource::Scheme::ARCHIVE>(
    const $::String::View& relative, const $::Filesystem::Path&) {
    return $::URI::Buffer("arch", relative);  // should exist
}

template <>
Talos::Resource::Result Talos::Resource::Path::resolve<Talos::Resource::Scheme::DYNAMIC>(
    const $::String::View& name, const $::Filesystem::Path&) {
    return $::Trim::both(name).empty() ? failure(8000101) : $::URI::Buffer("dylib", name);
}

template <>
Talos::Resource::Result Talos::Resource::Path::resolve<Talos::Resource::Scheme::INTERNAL>(
    const $::String::View& name, const $::Filesystem::Path&) {
    if ($::Trim::both(name).empty()) return failure(8000101);  // ensure the path is non-empty
    auto crate = $::Path::join(Crate::Constants::internal(), name, Crate::Constants::filename());
    return $::Path::exists(crate) ? $::URI::Buffer(crate.string()) : MM_MISSING("talos:", +$::String::Buffer(name));
}

template <>
Talos::Resource::Result Talos::Resource::Path::resolve<Talos::Resource::Scheme::EXTERNAL>(
    const $::String::View& name, const $::Filesystem::Path&) {
    if ($::Trim::both(name).empty()) return failure(8000101);  // ensure the path is non-empty
    auto crate = $::Path::join(Crate::Constants::external(), name, Crate::Constants::filename());
    return $::Path::exists(crate) ? $::URI::Buffer(crate.string()) : MM_MISSING("crate:", +$::String::Buffer(name));
}
