#ifndef _XTDLIB_ENCODING_HEX_HPP
#define _XTDLIB_ENCODING_HEX_HPP

/// Library Includes
#include "xtdlib/debug/assert.hpp"
#include "xtdlib/encoding/ascii.hpp"

namespace $::Encoding::HEX {

//  PUBLIC METHODS  //

/**
 * @brief Checks for hex digits.
 * @param cp                Codepoint.
 */
inline bool is(int64_t cp) { return ASCII::hex(cp); }

/**
 * @brief Converts a value to a hex-digit.
 * @param x                 Value to convert.
 * @param lower             Whether to lowercase.
 */
inline char encode(unsigned char x, bool lower = false) {
  static const char s_lut[] = "0123456789ABCDEF";
  return $_ASSERT(x < 16), s_lut[x] | (lower ? 32 : 0);
}

/**
 * @brief Converts a digit to a hex value.
 * @param ch                Character to convert.
 */
inline unsigned decode(char ch) {
  // clang-format off
  static const int16_t s_lut[256] = {
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
  -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
  }; // clang-format on

  // should be a valid hex value potentially
  return s_lut[static_cast<unsigned char>(ch)];
}

/**
 * @brief Casts a hex-digit from nibbles.
 * @param msb               Most significate bit.
 * @param lsb               Least significate bit.
 */
inline uint8_t from(char msb, char lsb) { return static_cast<uint8_t>((decode(msb) << 4) | decode(lsb)); }

} // namespace $::Encoding::HEX

#endif
