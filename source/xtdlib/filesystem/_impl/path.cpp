/// C++ Modules
#include <algorithm>

/// Library Modules
#include "xtdlib/filesystem/path.hpp"
#include "xtdlib/macros/processor.hpp"

/// Forward Declarations
$_FWD(static Filesystem::Path outer(const Filesystem::Path &), $::Path)

//  PUBLIC METHODS  //

static $::Filesystem::Path $::Path::outer(const Filesystem::Path &hint) {
    return std::filesystem::is_directory(hint) ? hint : dirname(hint);
}

$::Filesystem::Path $::Path::relative(const Filesystem::Path &absolute, const Filesystem::Path &hint) {
    return std::filesystem::relative(absolute, outer(hint));
}

$::Filesystem::Path $::Path::absolute(const Filesystem::Path &relative, const Filesystem::Path &hint) {
    // stop if the path is already absolute
    if (relative.is_absolute()) return relative;

    auto ec = std::error_code();  // prepare an error code
    auto base = std::filesystem::absolute(outer(hint), ec);
    if (ec) return Filesystem::Path();  // invalid absolute

    // attempt building our result value from the base given
    auto result = relative.has_root_name() ? relative.root_name() : base.root_name();
    result += relative.has_root_directory() ? relative.root_directory() : base.root_directory() / base.relative_path();

    // and append on the incoming relative path
    return result / relative.relative_path();
}

$::Filesystem::Path $::Path::canonical(const Filesystem::Path &relative, const Filesystem::Path &hint) {
    // get the relative value as an absolute
    auto source = absolute(relative, hint);

    auto ec = std::error_code();  // prepare an error code to be used
    auto result = source.empty() ? source : std::filesystem::weakly_canonical(source, ec);
    return ec ? Filesystem::Path() : result.lexically_normal();  // found a valid result
}

$::Filesystem::Compare $::Path::compare(const Filesystem::Path &file_path, const Filesystem::Path &base) {
    // always check for immediate matches to begin
    if (file_path == base) return Filesystem::Compare::EXACT;

    // next we attempt checking against relative paths using "mismatch"
    auto mismatch = std::ranges::mismatch(file_path, base);

    // check against either condition being the subpath now
    if (mismatch.in2 == base.end()) return Filesystem::Compare::SUBPATH;
    if (mismatch.in1 == file_path.end()) return Filesystem::Compare::PARENT;

    // on fall-through we declare we have a complete mismatch
    return Filesystem::Compare::MISMATCH;
}
