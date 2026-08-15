#ifndef _XPC_PROCESS_IDENTIFIER_HPP
#define _XPC_PROCESS_IDENTIFIER_HPP

/// XPC Includes
#include "xpc/forward/process.hpp"

namespace XPC::Process {

/// @brief Process Identifier Container.
class Identifier {
  //  PROPERTIES  //

  /// @brief The underlying encoded identifier.
  int64_t m_pid = 0;

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs a defaulted identifier.
  constexpr Identifier() = default;

  /**
   * @brief Constructs an identifier from any numeric value.
   * @param pid                   Identifier to encapsulate.
   */
  template <class T>
    requires std::is_arithmetic_v<T>
  constexpr Identifier(T pid) : m_pid(pid) {}

  //  OPERATOR METHODS  //

  inline constexpr operator int64_t() const noexcept { return m_pid; }
  inline constexpr operator bool() const noexcept { return m_pid > 0; }

  //  PUBLIC METHODS  //

  /// @brief Gets the underlying identifier value.
  inline constexpr int64_t value() const noexcept { return m_pid; }

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Helper for printing process identifier.
   * @param os                    Output stream.
   * @param self                  Identifier instance.
   */
  static inline void m_print(std::ostream &os, const Identifier &self) { os << self.m_pid; }
};

} // namespace XPC::Process

#endif
