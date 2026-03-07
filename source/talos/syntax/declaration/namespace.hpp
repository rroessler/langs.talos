#ifndef _TALOS_DECLARATION_NAMESPACE_HPP
#define _TALOS_DECLARATION_NAMESPACE_HPP

/// Syntax Modules
#include "talos/syntax/declaration/preamble.hpp"
#include "talos/syntax/statement/block.hpp"

namespace Talos::Syntax {

    /// @brief Namespace Declaration Node.
    class Namespace : public Abstract<Namespace, Declaration> {
        //  PROPERTIES  //

        /// @brief Declaration block.
        Block* m_block;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a type declaration.
         * @param target                    Target name.
         * @param block                     Block statement.
         */
        explicit Namespace(const Lexer::Token* target, Block* block) : Abstract(target), m_block(block) {}

        /**
         * @brief Constructs a type declaration.
         * @param name                      Target name.
         * @param block                     Block statement.
         * @param location                  Resource location.
         */
        explicit Namespace(const $::String::View& name, Block* block, const Bounds& location = {}) :
            Abstract(name, location), m_block(block) {}

        //  PUBLIC METHODS  //

        /// @brief Namespace block statement.
        inline constexpr Block* block() const noexcept { return m_block; }
    };

}  // namespace Talos::Syntax

#endif
