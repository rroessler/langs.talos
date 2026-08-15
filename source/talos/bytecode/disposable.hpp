#ifndef _TALOS_BYTECODE_DISPOSABLE_HPP
#define _TALOS_BYTECODE_DISPOSABLE_HPP

/// Talos Includes
#include "talos/forward/bytecode.hpp"

namespace Talos::Bytecode {

/// @brief Current disposable stack.
class Disposable {
  //  PROPERTIES  //

  /// @brief The disposable depth.
  size_t m_depth = 0;

  /// @brief Bound compiler instance.
  Compiler *m_compiler = nullptr;

  /// @brief The parent disposable.
  const Disposable *m_ancestor = nullptr;

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs an empty disposable.
  explicit Disposable() = default;

  /// @brief Constructs a disposable stack.
  explicit Disposable(Compiler *compiler);
  explicit Disposable(Compiler *compiler, const Disposable *ancestor);

  /// @brief Handles closing a disposable.
  ~Disposable();

  //  PUBLIC METHODS  //

  /// @brief Gets the underlying depth of the disposable stack.
  inline constexpr size_t depth() const noexcept { return m_depth; }

  /// @brief Denotes if there is no disposable instance.
  inline constexpr bool unset() const noexcept { return m_compiler == nullptr; }
};

} // namespace Talos::Bytecode

#endif
