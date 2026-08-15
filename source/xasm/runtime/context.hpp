#ifndef _XASM_RUNTIME_CONTEXT_HPP
#define _XASM_RUNTIME_CONTEXT_HPP

/// XASM Modules
#include "xasm/compiler/scope.hpp"

namespace XASM::Runtime {

/// @brief Runtime Context Container.
class Context {
  //  PROPERTIES  //

  /// @brief The underlying runtime target.
  $::Unique::Pointer<Target> m_target = $::Unique::New<Target>();

  /// @brief The underlying logger instance.
  $::Unique::Pointer<Logger> m_logger = $::Unique::New<Logger>();

  /// @brief The underlying code-holder.
  $::Unique::Pointer<Compiler::Arena> m_arena = $::Unique::New<Compiler::Arena>();

  /// @brief The host compiler backend.
  $::Unique::Pointer<Compiler::Backend> m_backend = $::Unique::New<Compiler::Backend>();

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs a context instance.
  constexpr Context() = default;

  //  PUBLIC METHODS  //

  /// @brief Gets the underlying target details.
  inline constexpr Target *target() const noexcept { return m_target.get(); }

  /// @brief Gets the internal arena instance.
  inline constexpr const Compiler::Arena *arena() const noexcept { return m_arena.get(); }

  /// @brief Gets the available target hints.
  inline constexpr const Hints &hints() const noexcept { return m_target->_cpu_hints; }

  /// @brief Gets the available target features.
  inline constexpr const Features &features() const noexcept { return m_target->_cpu_features; }

  /// @brief Gets the available environment to be used.
  inline constexpr const Environment &environment() const noexcept { return m_target->environment(); }

  /// @brief Gets the current logger output.
  inline constexpr $::String::View content() const noexcept {
    return {m_logger->content().data(), m_logger->content().size()};
  }

  /// @brief Constructs a compilation scoping.
  template <class T> inline constexpr auto scope(bool logging = false) const noexcept {
    m_arena->reset(), m_arena->init(m_target->environment()), m_arena->attach(m_backend.get());
    if (logging) m_logger->clear(), m_arena->set_logger(m_logger.get()); // bind the logger now
    return $::Unique::New<Compiler::Typed<T>>(m_target.get(), m_arena.get(), m_backend.get());
  }
};

} // namespace XASM::Runtime

#endif
