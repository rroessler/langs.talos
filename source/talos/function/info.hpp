#ifndef _TALOS_FUNCTION_INFO_HPP
#define _TALOS_FUNCTION_INFO_HPP

/// Talos Modules
#include "talos/forward/function.hpp"
#include "talos/linker/arena.hpp"
#include "talos/linker/view.hpp"

namespace Talos::Function {

    /// @brief Shared Function Information.
    class Info : public $::Printable {
        //  PROPERTIES  //

        /// @brief Internally linked code.
        Linker::View m_linkage = {};

        /// @brief Bound shared information.
        Bytecode::Shared m_info = {};

        /// @brief Associated bytecode arena.
        Linker::Arena* m_arena = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs shared function information.
         * @param arena                     Bytecode arena.
         * @param info                      Bytecode info.
         */
        explicit Info(Linker::Arena* arena = nullptr, const Bytecode::Shared& info = {}) :
            m_info(info), m_arena(arena) {}

        //  PUBLIC METHODS  //

        /// @brief Minimum/maximum argument counts.
        inline constexpr size_t arity() const noexcept { return m_info.arity; }
        inline constexpr size_t adicity() const noexcept { return m_info.adicity; }
        inline constexpr size_t argmax() const noexcept { return std::min(m_info.adicity, m_info.vargs); }

        /// @brief Associated variable counts.
        inline constexpr size_t locals() const noexcept { return m_info.locals; }
        inline constexpr size_t leaked() const noexcept { return m_info.leaked; }

        /// @brief Denotes if this is the "main" module function information.
        inline constexpr bool main() const noexcept { return m_arena->functions.front().get() == this; }

        /// @brief Gets the underlying shared information.
        inline constexpr Bytecode::Shared* shared() noexcept { return &m_info; }
        inline constexpr const Bytecode::Shared* shared() const noexcept { return &m_info; }

        /// @brief Gets the underlying linkage view.
        inline constexpr Linker::View& buffer() noexcept { return m_linkage; }
        inline constexpr const Linker::View& buffer() const noexcept { return m_linkage; }

        /// @brief Associated arena instance.
        inline constexpr const Linker::Arena* arena() const noexcept { return m_arena; }

        /// @brief Gets the bound resource value.
        inline constexpr $::URI::View resource() const noexcept { return m_arena->resource; }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles printing shared function information.
         * @param os                    Output stream.
         * @param self                  Info to print.
         */
        static void m_print($::Stream::Output& os, const Info& self);
    };

}  // namespace Talos::Function

#endif
