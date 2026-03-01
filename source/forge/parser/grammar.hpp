#ifndef _FORGE_PARSER_GRAMMAR_HPP
#define _FORGE_PARSER_GRAMMAR_HPP

/// Forge Modules
#include "forge/parser/stream.hpp"
#include "forge/syntax/grammar.hpp"

namespace Forge::Parser::Grammar {

    /// @brief Expected infix handler.
    using Infix = Syntax::Grammar::Infix<Syntax::Expression, Stream>;

    /// @brief Expected prefix handler.
    using Prefix = Syntax::Grammar::Prefix<Syntax::Expression, Stream>;

    /// @brief The underlying grammar rule.
    using Rule = Syntax::Grammar::Rule<Syntax::Expression, Stream>;

    /// @brief The underlying grammar table.
    using Table = Syntax::Grammar::Table<Syntax::Expression, Stream>;

}  // namespace Forge::Parser::Grammar

#endif
