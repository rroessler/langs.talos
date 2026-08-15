#ifndef _XTDLIB_STRING_CONVERT_HPP
#define _XTDLIB_STRING_CONVERT_HPP

/// Library Includes
#include "xtdlib/string/buffer.hpp"
#include "xtdlib/string/view.hpp"

namespace $::Convert {

/**
 * @brief Handles converting a string to lowercase.
 * @param buffer                Buffer to capitalize.
 */
static inline int32_t lowercase(int32_t ch) { return std::tolower(ch); }
static inline String::Buffer lowercase(const $::String::View &buffer) {
  String::Buffer output; // prepare the output string
  for (const auto &ch : buffer) output += lowercase(ch);
  return output; // and return the final output
}

/**
 * @brief Handles converting a string to uppercase.
 * @param buffer                Buffer to capitalize.
 */
static inline int32_t uppercase(int32_t ch) { return std::toupper(ch); }
static inline String::Buffer uppercase(const $::String::View &buffer) {
  String::Buffer output; // prepare the output string
  for (const auto &ch : buffer) output += uppercase(ch);
  return output; // and return the final output
}

/**
 * @brief Handles capitalizing a singular word.
 * @param buffer                Buffer to capitalize.
 */
static inline String::Buffer capitalize(const String::View &buffer) {
  if (buffer.empty()) return String::Buffer(buffer); // ignore if empty
  return uppercase(buffer.substr(0, 1)) + String::Buffer(buffer.substr(1));
}

} // namespace $::Convert

#endif
