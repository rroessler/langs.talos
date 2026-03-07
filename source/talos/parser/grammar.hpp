#ifndef _TALOS_PARSER_GRAMMAR_HPP
#define _TALOS_PARSER_GRAMMAR_HPP

/// Talos Modules
#include "talos/parser/stream.hpp"
#include "talos/syntax/grammar.hpp"

namespace Talos::Parser::Grammar {

    /// @brief Expected infix handler.
    using Infix = Syntax::Grammar::Infix<Syntax::Expression, Stream>;

    /// @brief Expected prefix handler.
    using Prefix = Syntax::Grammar::Prefix<Syntax::Expression, Stream>;

    /// @brief The underlying grammar rule.
    using Rule = Syntax::Grammar::Rule<Syntax::Expression, Stream>;

    /// @brief The underlying grammar table.
    using Table = Syntax::Grammar::Table<Syntax::Expression, Stream>;

}  // namespace Talos::Parser::Grammar

#endif
