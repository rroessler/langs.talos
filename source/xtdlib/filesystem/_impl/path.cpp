/// C++ Modules
#include <algorithm>

/// Library Includes
#include "xtdlib/filesystem/path.hpp"
#include "xtdlib/macros/processor.hpp"

/// Forward Declarations
$_FWD($::Path, static FS::Path outer(const FS::Path &))

//  PUBLIC METHODS  //

static $::FS::Path $::Path::outer(const FS::Path &hint) {
  return std::filesystem::is_directory(hint) ? hint : dirname(hint);
}

$::FS::Path $::Path::relative(const FS::Path &absolute, const FS::Path &hint) {
  return std::filesystem::relative(absolute, outer(hint));
}

$::FS::Path $::Path::absolute(const FS::Path &relative, const FS::Path &hint) {
  // stop if the path is already absolute
  if (relative.is_absolute()) return relative;

  auto ec = std::error_code(); // prepare an error code
  auto base = std::filesystem::absolute(outer(hint), ec);
  if (ec) return FS::Path(); // invalid absolute

  // attempt building our result value from the base given
  auto result = relative.has_root_name() ? relative.root_name() : base.root_name();
  result += relative.has_root_directory() ? relative.root_directory() : base.root_directory() / base.relative_path();

  // and append on the incoming relative path
  return (result / relative.relative_path()).lexically_normal();
}

$::FS::Path $::Path::canonical(const FS::Path &relative, const FS::Path &hint) {
  // get the relative value as an absolute
  auto source = absolute(relative, hint);

  auto ec = std::error_code(); // prepare an error code to be used
  auto result = source.empty() ? source : std::filesystem::weakly_canonical(source, ec);
  return ec ? FS::Path() : result.lexically_normal(); // found a valid result to return
}

$::FS::Compare $::Path::compare(const FS::Path &file_path, const FS::Path &base) {
  // always check for immediate matches to begin
  if (file_path == base) return FS::Compare::EXACT;

  // next we attempt checking against relative paths using "mismatch"
  auto mismatch = std::ranges::mismatch(file_path, base);

  // check against either condition being the subpath now
  if (mismatch.in2 == base.end()) return FS::Compare::SUBPATH;
  if (mismatch.in1 == file_path.end()) return FS::Compare::PARENT;

  // on fall-through we declare we have a complete mismatch
  return FS::Compare::MISMATCH;
}
