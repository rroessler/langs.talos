#ifndef _XTDLIB_ENCODING_ASCII_HPP
#define _XTDLIB_ENCODING_ASCII_HPP

/// Library Includes
#include "xtdlib/portable/stdlib.hpp"

//  MACROS  //

#define MM_BETWEEN(CP, A, B) ((CP) >= (A) && (CP) <= (B))

//  NAMESPACES  //

namespace $::Encoding::ASCII {

//  PUBLIC METHODS  //

/// @brief Validates suitable binary characters.
inline bool bin(int64_t cp) { return cp == '0' || cp == '1'; }

/// @brief Validates suitable octal characters.
inline bool oct(int64_t cp) { return MM_BETWEEN(cp, '0', '7'); }

/// @brief Validates suitable numeric characters.
inline bool num(int64_t cp) { return MM_BETWEEN(cp, '0', '9'); }

/// @brief Validates suitable hexadecimal characters.
inline bool hex(int64_t cp) { return num(cp) || MM_BETWEEN(cp, 'a', 'f') || MM_BETWEEN(cp, 'A', 'F'); }

/// @brief Validates suitable alphabetical characters.
inline bool alpha(int64_t cp) { return MM_BETWEEN(cp, 'a', 'z') || MM_BETWEEN(cp, 'A', 'Z'); }

/// @brief Validates suitable identifier characters.
inline bool ident(int64_t cp) { return alpha(cp) || cp == '_' || cp >= 0x80; }

/// @brief Validates horizontal whitespace.
inline bool hws(int64_t cp) { return cp == ' ' || cp == '\t' || cp == '\v' || cp == '\r'; }

} // namespace $::Encoding::ASCII

//  UNDEFINES  //

#undef MM_BETWEEN

#endif
