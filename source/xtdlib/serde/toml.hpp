#ifndef _XTDLIB_SERDE_TOML_HPP
#define _XTDLIB_SERDE_TOML_HPP

/// Library Includes
#include "xtdlib/serde/codec.hpp"

namespace $::TOML {

//  TYPEDEFS  //

/// @brief Available TOML Encoder Options.
struct Options {};

//  PUBLIC METHODS  //

/**
 * @brief Handles encoding values.
 * @param value                 Value to encode.
 * @param options               Encoding Options.
 */
Serde::Result<Serde::Text> Encode(const Serde::Value &value, const Options &options = {});
template <class T> inline constexpr Serde::Result<Serde::Text> Encode(const T &value, const Options &options = {}) {
  return Encode(Serde::Encode(value), options);
}

/**
 * @brief Handles decoding values.
 * @param input                 Input to decode.
 * @param options               Encoding Options.
 */
Serde::Result<Serde::Value> Decode(const String::View &input, const Options &options = {});
template <class T> inline constexpr Serde::Result<T> Decode(const String::View &input, const Options &options = {}) {
  return Decode(input, options).transform([](const Serde::Value &value) { return Serde::Decode<T>(value); });
}

} // namespace $::TOML

#endif
