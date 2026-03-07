#ifndef _TALOS_SYNTAX_TREE_HPP
#define _TALOS_SYNTAX_TREE_HPP

/// Talos Modules
#include "talos/forward/lexer.hpp"
#include "talos/forward/parser.hpp"

/// Syntax Modules
#include "talos/syntax/literal/lambda.hpp"
#include "talos/syntax/statement/import.hpp"

namespace Talos::Syntax {

    /// @brief Syntax Tree Container.
    class Tree : public Abstract<Tree> {
        //  TYPEDEFS  //

        /// @brief Allow the parser internal access.
        friend class Parser::Stream;

        //  PROPERTIES  //

        /// @brief The underlying main function node.
        Lambda* m_main = nullptr;

        /// @brief The underlying module body.
        Block* m_block = nullptr;

        /// @brief Associated tree resource.
        $::URI::View m_resource = $::URI::Anonymous();

        /// @brief All available tree nodes.
        std::vector<$::Ptr::Unique<Node>> m_storage = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a defaulted tree instance.
         * @param resource              Resource URI.
         */
        explicit Tree(const $::URI::View& resource = $::URI::Anonymous());

        /**
         * @brief Constructs a syntax tree.
         * @param capacity              Initial capacity.
         * @param resource              Resource URI.
         */
        explicit Tree(size_t capacity, const $::URI::View& resource = $::URI::Anonymous()) : Tree(resource) {
            statements().reserve(capacity);  // reserve an initial capacity when given
            m_storage.reserve(capacity);     // and also fill the storage nodes as well
        }

        //  PUBLIC METHODS  //

        inline constexpr Lambda* main() const noexcept { return m_main; }
        inline constexpr $::URI::View resource() const noexcept { return m_resource; }

        inline constexpr std::vector<Node*>& statements() noexcept { return m_block->statements(); }
        inline constexpr const std::vector<Node*>& statements() const noexcept { return m_block->statements(); }

        /// @brief Gets a list of all viable syntax dependencies (unresolved).
        inline constexpr Dependencies dependencies() const noexcept {
            // prepare the output value to be used
            auto output = Dependencies();

            // iterate over the available storage
            for (const auto& node : m_storage) {
                if (!node->is<Import>()) continue;  // ignorable
                output.emplace_back(node->as<Import>()->path());
            }

            // return the final dependencies found
            return output;
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles allocating a syntax-node.
         * @param args                  Arguments to bind.
         */
        template <std::derived_from<Node> T, class... As>
        inline constexpr T* m_allocate(As&&... args) {
            auto node = $::New().unique<T>(std::forward<As>(args)...);
            return static_cast<T*>(m_storage.emplace_back(std::move(node)).get());
        }
    };

}  // namespace Talos::Syntax

#endif
