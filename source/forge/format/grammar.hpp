#ifndef _FORGE_FORMAT_GRAMMAR_HPP
#define _FORGE_FORMAT_GRAMMAR_HPP

/// Forge Modules
#include "forge/format/reader.hpp"
#include "forge/syntax/grammar.hpp"

namespace Forge::Format::Grammar {

    /// @brief Expected infix handler.
    using Infix = Syntax::Grammar::Infix<Node, Reader>;

    /// @brief Expected prefix handler.
    using Prefix = Syntax::Grammar::Prefix<Node, Reader>;

    /// @brief The underlying grammar rule.
    using Rule = Syntax::Grammar::Rule<Node, Reader>;

    /// @brief The underlying grammar table.
    using Table = Syntax::Grammar::Table<Node, Reader>;

}  // namespace Forge::Format::Grammar

#endif
