#ifndef _TALOS_SYNTAX_PRECEDENCE_HPP
#define _TALOS_SYNTAX_PRECEDENCE_HPP

/// Talos Includes
#include "talos/forward/syntax.hpp"

namespace Talos::Syntax {

/// @brief Operator/Types Precedence Ranks.
enum class Precedence : uint8_t {
  NONE = 0,

  COMMA, // ,

  ASSIGN,           // =
  TERNARY = ASSIGN, // a ? b : c

  COAL,       // ??
  LOR = COAL, // ||

  LAND, // &&
  BOR,  // |
  XOR,  // ^
  BAND, // &

  EQUAL,   // ==, !=
  COMPARE, // < > <= >=

  SHIFT,    // << >>
  TERM,     // + -
  FACTOR,   // * / %
  EXPONENT, // **

  UNARY, // ! - ++ -- ~

  INFER, // as is
  CALL,  // . ?. :: ()
  TMPL,  // []
};

} // namespace Talos::Syntax

#endif
