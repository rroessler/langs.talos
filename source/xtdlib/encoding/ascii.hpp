#ifndef _XTDLIB_ENCODING_ASCII_HPP
#define _XTDLIB_ENCODING_ASCII_HPP

/// C++ Modules
#include <cstdint>

//  MACROS  //

#define MM_BETWEEN(CP, A, B) ((CP) >= (A) && (CP) <= (B))

//  NAMESPACES  //

namespace $::Encoding::ASCII {

    //  PUBLIC METHODS  //

    inline bool is_digit(int64_t cp) { return MM_BETWEEN(cp, '0', '9'); }
    inline bool is_bin(int64_t cp) { return cp == '0' || cp == '1'; }
    inline bool is_oct(int64_t cp) { return MM_BETWEEN(cp, '0', '7'); }
    inline bool is_hex(int64_t cp) { return is_digit(cp) || MM_BETWEEN(cp, 'a', 'f') || MM_BETWEEN(cp, 'A', 'F'); }
    inline bool is_alpha(int64_t cp) { return MM_BETWEEN(cp, 'a', 'z') || MM_BETWEEN(cp, 'A', 'Z'); }
    inline bool is_ident(int64_t cp) { return is_alpha(cp) || cp == '_' || cp >= 0x80; }
    inline bool is_vws(int64_t cp) { return cp == ' ' || cp == '\t' || cp == '\v' || cp == '\r'; }

}  // namespace $::Encoding::ASCII

//  UNDEFINES  //

#undef MM_BETWEEN

#endif
