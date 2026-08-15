/// Vendor Includes
#include <glaze/json.hpp>

/// Library Includes
#include "xtdlib/serde/json.hpp"

/// Library Inlines
#include "xtdlib/serde/_inline/reflect.ipp"

/// Forward Declarations
$_FWD($::JSON, template <bool = false> constexpr glz::opts options())
$_FWD($::JSON, template <bool> Serde::Result<Serde::Value> read(const String::View &))

//  PUBLIC METHODS  //

template <bool C> constexpr glz::opts $::JSON::options() { return {.comments = C}; }
template <bool C> $::Serde::Result<$::Serde::Value> $::JSON::read(const String::View &buffer) {
  Serde::Value value = Serde::Null(); // prepare value
  auto ec = glz::read<options<C>()>(value, buffer);
  if (ec) return std::unexpected(glz::format_error(ec, buffer));
  return Serde::Result<Serde::Value>(value); // valid result to return
}

$::Serde::Result<$::Serde::Value> $::JSON::Decode(const String::View &json, const Options &options) {
  return options.comments ? read<true>(json) : read<false>(json);
}

$::Serde::Result<$::Serde::Text> $::JSON::Encode(const Serde::Value &value, const Options &) {
  auto exposed = static_cast<const Serde::Reflect *>(&value); // prepare the exposed value
  auto result = glz::write<options<>()>(exposed->m_storage);  // and attempt writing now
  return result.transform_error([](const glz::error_ctx &ec) { return glz::format_error(ec); });
}
