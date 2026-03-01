#ifndef _FORGE_BYTECODE_LOOP_HPP
#define _FORGE_BYTECODE_LOOP_HPP

/// Forge Modules
#include "forge/bytecode/binder.hpp"

namespace Forge::Bytecode {

    /// @brief Bytecode Loop Scope.
    class Loop {
        //  PROPERTIES  //

        Label m_head;  // Header label.
        Label m_exit;  // Exit label.

        /// @brief Associated labels binder.
        Binder* m_labels;

        /// @brief The underlying compiler instance.
        Compiler* m_compiler;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a loop instance.
         * @param compiler              Compiler to bind.
         */
        explicit Loop(Compiler* compiler);

        /// @brief Handles closing a loop instance.
        ~Loop();

        //  PUBLIC METHODS  //

        inline constexpr Label head() const noexcept { return m_head; }
        inline constexpr Label exit() const noexcept { return m_exit; }
    };

}  // namespace Forge::Bytecode

#endif
