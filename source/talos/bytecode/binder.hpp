#ifndef _TALOS_BYTECODE_BINDER_HPP
#define _TALOS_BYTECODE_BINDER_HPP

/// C++ Modules
#include <stack>

/// Talos Modules
#include "talos/bytecode/block.hpp"
#include "talos/bytecode/request.hpp"

namespace Talos::Bytecode {

    /// @brief Labels Allocator.
    class Binder {
        //  TYPEDEFS  //

        /// @brief Allow loops internal access.
        friend class Loop;

        /// @brief Allow the compiler internal access.
        friend class Compiler;

        //  PROPERTIES  //

        /// @brief Current block instance.
        Block* m_head = nullptr;

        /// @brief The current compilation request.
        Request** m_request = nullptr;

        /// @brief Current block references.
        $::Map<Label, Block*> m_blocks = {};

        std::stack<Label> m_breaks = {};     // Current break labels.
        std::stack<Label> m_returns = {};    // Current return labels.
        std::stack<Label> m_continues = {};  // Current continue labels.

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a label binder.
         * @param request               Request to bind.
         */
        explicit Binder(Request** request = nullptr) : m_request(request) {}

        //  PUBLIC METHODS  //

        inline constexpr Block* head() const noexcept { return m_head; }
        inline constexpr Label reserve() noexcept { return (*m_request)->routine()->head++; }

        inline constexpr $::Map<Label, Block*>& blocks() noexcept { return m_blocks; }
        inline constexpr const $::Map<Label, Block*>& blocks() const noexcept { return m_blocks; }

        inline constexpr Label breaks() const noexcept { return m_breaks.top(); }
        inline constexpr Label returns() const noexcept { return m_returns.top(); }
        inline constexpr Label continues() const noexcept { return m_continues.top(); }

        /// @brief Handles clearing the labels binder.
        inline constexpr void clear() noexcept { m_head = nullptr, m_blocks = {}; }

        /// @brief Constructs a new top-most block.
        inline constexpr Block* scope() {
            // ensure the underlying request actually exists
            $_ASSERT(m_request && *m_request, "Expected a compilation request");

            // ensure that every block has at least one label bound to represent it
            if (m_head && m_head->labels().empty()) m_head->labels().emplace(reserve());

            // push back a new block onto the current request
            return m_head = (*m_request)->routine()->blocks.emplace_back($::New().unique<Block>()).get();
        }

        /**
         * @brief Handles patching a label.
         * @param label                 Label to patch.
         */
        inline constexpr void patch() { patch(reserve()); }
        inline constexpr void patch(const Label& label) {
            // ensure that we have a top-most block available
            $_ASSERT(m_head, "Expected a top-most block");

            // prepare a block to be used currently as needed
            auto* head = m_head->empty() ? m_head : scope();

            // and bind our details as necessary onto the block
            head->labels().emplace(label), m_blocks.emplace(label, head);
        }
    };

}  // namespace Talos::Bytecode

#endif
