#ifndef _FORGE_STATEMENT_BLOCK_HPP
#define _FORGE_STATEMENT_BLOCK_HPP

/// Forge Modules
#include "forge/syntax/node.hpp"

namespace Forge::Syntax {

    /// @brief Block Statement.
    class Block : public Abstract<Block, Statement> {
        //  PROPERTIES  //

        /// @brief Available statements to be parsed.
        std::vector<Node*> m_statements;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a block statement.
         * @param statements                Block nodes.
         * @param range                     Block range.
         */
        explicit Block(const std::vector<Node*>& statements = {}, const Bounds& location = {}) :
            Abstract(location), m_statements(statements) {}

        /**
         * @brief Constructs a block statement.
         * @param statement                 Block node.
         * @param range                     Block range.
         */
        explicit Block(Node* statement, const Bounds& location = {}) : Block(std::vector({ statement }), location) {}

        //  PUBLIC METHODS  //

        inline constexpr size_t size() const noexcept { return m_statements.size(); }
        inline constexpr bool empty() const noexcept { return m_statements.empty(); }

        inline constexpr std::vector<Node*>& statements() noexcept { return m_statements; }
        inline constexpr const std::vector<Node*>& statements() const noexcept { return m_statements; }
    };

}  // namespace Forge::Syntax

#endif
