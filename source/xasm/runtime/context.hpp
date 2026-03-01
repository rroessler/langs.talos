#ifndef _XASM_RUNTIME_CONTEXT_HPP
#define _XASM_RUNTIME_CONTEXT_HPP

/// XASM Modules
#include "xasm/compiler/scope.hpp"
#include "xasm/forward/runtime.hpp"

namespace XASM::Runtime {

    /// @brief Runtime Context Container.
    class Context {
        //  PROPERTIES  //

        /// @brief The underlying runtime target.
        $::Ptr::Unique<Target> m_target = $::New().unique<Target>();

        /// @brief The underlying logger instance.
        $::Ptr::Unique<Logger> m_logger = $::New().unique<Logger>();

        /// @brief The underlying code-holder.
        $::Ptr::Unique<Compiler::Arena> m_arena = $::New().unique<Compiler::Arena>();

        /// @brief The host compiler backend.
        $::Ptr::Unique<Compiler::Backend> m_backend = $::New().unique<Compiler::Backend>();

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a context instance.
        constexpr Context() = default;

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying target details.
        inline constexpr Target* target() const noexcept { return m_target.get(); }

        /// @brief Gets the available target hints.
        inline constexpr const Hints& hints() const noexcept { return m_target->_cpu_hints; }

        /// @brief Gets the available target features.
        inline constexpr const Features& features() const noexcept { return m_target->_cpu_features; }

        /// @brief Gets the available environment to be used.
        inline constexpr const Environment& environment() const noexcept { return m_target->environment(); }

        /// @brief Gets the current logger output.
        inline constexpr $::String::View content() const noexcept {
            return { m_logger->content().data(), m_logger->content().size() };
        }

        /// @brief Constructs a compilation scoping.
        template <class T>
        inline constexpr Compiler::Scope<T> scope(bool logging = false) const noexcept {
            return Compiler::Scope<T>(target(), m_arena.get(), m_backend.get(), logging ? m_logger.get() : nullptr);
        }
    };

}  // namespace XASM::Runtime

#endif
