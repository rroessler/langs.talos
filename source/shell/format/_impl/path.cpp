/// Shell Modules
#include "shell/format/path.hpp"

/// Forward Declarations
$_FWD(std::vector<$::URI::Buffer> file(const $::Filesystem::Path&), Shell::Format::Path)
$_FWD(std::vector<$::URI::Buffer> href(const $::Filesystem::Path&), Shell::Format::Path)

//  PUBLIC METHODS  //

std::vector<$::URI::Buffer> Shell::Format::Path::file(const $::Filesystem::Path& absolute) {
    if (!$::Path::is_file(absolute)) return {};
    return { $::URI::Buffer(absolute.string()) };
}

std::vector<$::URI::Buffer> Shell::Format::Path::href(const $::Filesystem::Path& relative) {
    return file($::Path::canonical(relative));
}

std::vector<$::URI::Buffer> Shell::Format::Path::resolve(const $::String::View& target) {
    // attempt parsing the incoming target now
    auto resource = $::URI::Codec::parse(target);

    // handle different types or resources as necessary
    switch (XH::FNV::U64(resource.scheme())) {
        // handle incomgin requests for files
        case XH::FNV::U64($::URI::Scheme::FILE): return file(resource.body());

        // handle incoming requests for resolution
        case XH::FNV::U64($::URI::Scheme::HREF): return href(resource.body());

        // stop on invalid references that are given
        default: return {};
    }
}
