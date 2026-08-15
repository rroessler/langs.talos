/// Vendor Includes
#include <glaze/toml.hpp>

/// Library Includes
#include "xtdlib/serde/toml.hpp"

/// Library Inlines
#include "xtdlib/serde/_inline/reflect.ipp"

//  PUBLIC METHODS  //

$::Serde::Result<$::Serde::Value> $::TOML::Decode(const String::View &buffer, const Options &) {
  Serde::Value value = Serde::Null();
  auto ec = glz::read_toml(value, buffer);
  if (ec) return std::unexpected(glz::format_error(ec, buffer));
  return Serde::Result<Serde::Value>(value);
}

$::Serde::Result<$::Serde::Text> $::TOML::Encode(const Serde::Value &value, const Options &) {
  auto exposed = static_cast<const Serde::Reflect *>(&value);
  auto result = glz::write_toml(exposed->m_storage);
  return result.transform_error([](const glz::error_ctx &ec) { return glz::format_error(ec); });
}
