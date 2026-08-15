#ifndef _XLSP_PROTOCOL_ENCODING_HPP
#define _XLSP_PROTOCOL_ENCODING_HPP

/// XLSP Includes
#include "xlsp/forward/protocol.hpp"

//  X-MACROS  //

/// @brief Available LSP encoding types.
#define XX_ENCODING_TYPES(X) \
  X(INVALID, "invalid")      \
                             \
  X(UTF8, "utf-8")           \
  X(UTF16, "utf-16")         \
  X(UTF32, "utf-32")

//  NAMESPACES  //

namespace XLSP::Encoding {

//  TYPEDEFS  //

/// @brief Available encoding types.
$_XX_ENUM_CLASS(Type, uint8_t, XX_ENCODING_TYPES);

//  PUBLIC METHODS  //

/**
 * @brief Resolves a suitable UTF-8 encoding.
 * @param view                          Encoding string-view.
 */
static constexpr Type resolve(const $::String::View &view) {
#define X(N, S, ...)                    \
  case XH::FNV::U32(S): return Type::N;
  switch (XH::FNV::U32(view)) { XX_ENCODING_TYPES(X) default : return Type::INVALID; }
#undef X
}

/**
 * @brief Converts an encoding to a string.
 * @param encoding                      Encoding value.
 */
static constexpr $::String::View format(const Type &encoding) {
#define X(N, S, ...)      \
  case Type::N: return S;
  switch (encoding) { XX_ENCODING_TYPES(X) default : return "invalid"; }
#undef X
}

/**
 * @brief Handles measuring a given encoding.
 * @param view                          String-view.
 * @param units                         Units to count.
 * @param encoding                      Encoding value.
 */
size_t measure(const $::String::View &view, int32_t units, const Type &encoding);

} // namespace XLSP::Encoding

//  UNDEFINES  //

#undef XX_ENCODING_TYPES

#endif
