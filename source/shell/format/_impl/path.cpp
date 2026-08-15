/// Shell Includes
#include "shell/format/path.hpp"

/// Forward Declarations
$_FWD(Shell::Format::URI, std::vector<$::URI::Buffer> file(const $::FS::Path &))
$_FWD(Shell::Format::URI, std::vector<$::URI::Buffer> href(const $::FS::Path &))

//  PUBLIC METHODS  //

std::vector<$::URI::Buffer> Shell::Format::URI::file(const $::FS::Path &absolute) {
  if (!$::Path::is_file(absolute)) return {};
  return {$::URI::Buffer(absolute.string())};
}

std::vector<$::URI::Buffer> Shell::Format::URI::href(const $::FS::Path &relative) {
  return file($::Path::canonical(relative));
}

std::vector<$::URI::Buffer> Shell::Format::Path(const $::String::View &target) {
  // attempt parsing the incoming target now
  auto resource = $::URI::Parse(target);

  // handle different types or resources as necessary
  switch (XH::FNV::U32(resource.scheme())) {
  // handle incomgin requests for files
  case XH::FNV::U32($::URI::Scheme::FILE): return URI::file(resource.body());

  // handle incoming requests for resolution
  case XH::FNV::U32($::URI::Scheme::HREF): return URI::href(resource.body());

  // stop on invalid references that are given
  default: return {};
  }
}
