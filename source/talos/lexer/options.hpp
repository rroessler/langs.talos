#ifndef _TALOS_LEXER_OPTIONS_HPP
#define _TALOS_LEXER_OPTIONS_HPP

/// Talos Includes
#include "talos/forward/diagnostic.hpp"
#include "talos/forward/lexer.hpp"

namespace Talos::Lexer {

/// @brief Lexical Encoding Type.
using Encoding = XLSP::Encoding::Type;

/// @brief Lexical Options.
struct Options {
  //  PROPERTIES  //

  /// @brief Whether comments are preserved.
  bool comments = false;

  /// @brief The baseline diagnostic encoding.
  Encoding encoding = Encoding::UTF8;

  /// @brief The diagnostic reporter to use.
  Diagnostic::Reporter *reporter = nullptr;
};

} // namespace Talos::Lexer

#endif
