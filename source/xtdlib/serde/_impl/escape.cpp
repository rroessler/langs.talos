/// Vendor Includes
#include <glaze/json.hpp>

/// Library Includes
#include "xtdlib/serde/escape.hpp"

//  PUBLIC METHODS  //

$::Serde::Result<$::Serde::Text> $::Serde::Escape(const String::View &value) { return Escape(Text(value)); }
$::Serde::Result<$::Serde::Text> $::Serde::Escape(const Text &value) {
  return glz::write_json(value).transform_error([](const glz::error_ctx &ec) { return glz::format_error(ec); });
}

$::Serde::Result<$::Serde::Text> $::Serde::Unescape(const String::View &value) { return Unescape(Text(value)); }
$::Serde::Result<$::Serde::Text> $::Serde::Unescape(const Text &value) {
  $::String::Buffer output = {}; // prepare storage
  auto ec = glz::read_json(output, '"' + value + '"');
  if (ec) return std::unexpected(glz::format_error(ec, value));
  return Result<Text>(output); // valid result to be returned
}
