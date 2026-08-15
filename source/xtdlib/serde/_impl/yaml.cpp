/// Vendor Includes
#include <glaze/yaml.hpp>

/// Library Includes
#include "xtdlib/serde/yaml.hpp"

/// Library Inlines
#include "xtdlib/serde/_inline/reflect.ipp"

//  PUBLIC METHODS  //

$::Serde::Result<$::Serde::Value> $::YAML::Decode(const String::View &buffer, const Options &) {
  Serde::Value value = Serde::Null();
  auto ec = glz::read_yaml<glz::yaml::yaml_opts{}>(value, buffer);
  if (ec) return std::unexpected(glz::format_error(ec, buffer));
  return Serde::Result<Serde::Value>(value);
}

$::Serde::Result<$::Serde::Text> $::YAML::Encode(const Serde::Value &value, const Options &) {
  auto exposed = static_cast<const Serde::Reflect *>(&value);
  auto result = glz::write_yaml<glz::yaml::yaml_opts{}>(exposed->m_storage);
  return result.transform_error([](const glz::error_ctx &ec) { return glz::format_error(ec); });
}
