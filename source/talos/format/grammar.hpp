#ifndef _TALOS_FORMAT_GRAMMAR_HPP
#define _TALOS_FORMAT_GRAMMAR_HPP

/// Talos Modules
#include "talos/format/reader.hpp"
#include "talos/syntax/grammar.hpp"

namespace Talos::Format::Grammar {

    /// @brief Expected infix handler.
    using Infix = Syntax::Grammar::Infix<Node, Reader>;

    /// @brief Expected prefix handler.
    using Prefix = Syntax::Grammar::Prefix<Node, Reader>;

    /// @brief The underlying grammar rule.
    using Rule = Syntax::Grammar::Rule<Node, Reader>;

    /// @brief The underlying grammar table.
    using Table = Syntax::Grammar::Table<Node, Reader>;

}  // namespace Talos::Format::Grammar

#endif
