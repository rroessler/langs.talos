#ifndef _XTDLIB_TERMINAL_A11Y_HPP
#define _XTDLIB_TERMINAL_A11Y_HPP

/// Library Includes
#include "xtdlib/system/environment.hpp"
#include "xtdlib/terminal/core.hpp"

namespace $::A11Y {

//  TYPEDEFS  //

/// @brief Baseline Accesibility Enablement.
class Enablement {
  //  PROPERTIES  //

  /// @brief Enabled by default.
  bool m_enabled = true;

  /// @brief Internal stream index.
  int32_t m_index = std::ios_base::xalloc();

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs a baseline enablement.
  constexpr Enablement() = default;

  /**
   * @brief Constructs an accessibility enablement.
   * @param enabled             Current state.
   */
  constexpr Enablement(bool enabled) : m_enabled(enabled) {}

  //  OPERATOR METHODS  //

  /// @brief Gets the global enablement value.
  inline constexpr bool &operator()() noexcept { return m_enabled; }
  inline constexpr bool operator()() const noexcept { return m_enabled; }

  /**
   * @brief Gets current stream enablement.
   * @param file            Internal file.
   */
  inline constexpr bool operator()(FILE *file) const noexcept { return m_enabled && Terminal::is(file); }

  /**
   * @brief Gets current stream enablement.
   * @param os              Output stream.
   */
  inline constexpr bool operator()(std::ostream &os) const noexcept {
    return m_enabled && (Terminal::is(os) || os.iword(m_index));
  }

  /**
   * @brief Allow overriding the stream enablement.
   * @param os              Output stream.
   * @param state           Enablement state.
   */
  inline constexpr void operator()(std::ostream &os, bool state) noexcept { os.iword(m_index) = state; }
};

//  PROPERTIES  //

/// @brief Handles checking for accessibilty environment variables.
static inline constexpr auto Variable = [](const $::String::Buffer &key) {
  auto value = $::Environ::get(key); // resolve the value
  return !value.has_value() || value->empty() || *value == "0";
};

} // namespace $::A11Y

#endif
