#ifndef _FORGE_SYNTAX_PRECEDENCE_HPP
#define _FORGE_SYNTAX_PRECEDENCE_HPP

/// Forge Modules
#include "forge/forward/syntax.hpp"

namespace Forge::Syntax {

    /// @brief Operator/Types Precedences.
    enum class Precedence : uint8_t {
        NONE = 0,

        COMMA,  // ,

        ASSIGN,            // =
        TERNARY = ASSIGN,  // a ? b : c

        COAL,        // ??
        LOR = COAL,  // ||

        LAND,  // &&
        BOR,   // |
        XOR,   // ^
        BAND,  // &

        EQUALITY,    // ==, !=
        COMPARISON,  // < > <= >=

        SHIFT,     // << >>
        TERM,      // + -
        FACTOR,    // * / %
        EXPONENT,  // **

        UNARY,           // ! - ++ -- ~
        TYPEOF = UNARY,  // typeof

        CAST,          // as
        INFER = CAST,  // is

        CALL,  // . ?. () []
        TMPL,  // ::
    };

}  // namespace Forge::Syntax

#endif
