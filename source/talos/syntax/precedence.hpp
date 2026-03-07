#ifndef _TALOS_SYNTAX_PRECEDENCE_HPP
#define _TALOS_SYNTAX_PRECEDENCE_HPP

/// Talos Modules
#include "talos/forward/syntax.hpp"

namespace Talos::Syntax {

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

}  // namespace Talos::Syntax

#endif
