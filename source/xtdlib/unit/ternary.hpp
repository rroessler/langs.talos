#ifndef _XTDLIB_UNIT_TERNARY_HPP
#define _XTDLIB_UNIT_TERNARY_HPP

/// Library Includes
#include "xtdlib/portable/stdlib.hpp"

namespace $::Unit {

/// @brief Tribool-Like State.
class Ternary {
  //  TYPEDEFS  //

  /// @brief Expose the unknown constructor.
  friend constexpr Ternary Unknown() noexcept;

  /// @brief Available ternary states.
  enum class State : uint8_t { T, F, U };

  //  PROPERTIES  //

  /// @brief Underlying state value.
  State m_state;

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs an indeterminate ternary.
  constexpr Ternary() noexcept : m_state(State::U) {}

  /**
   * @brief Internally allow value construction.
   * @param state                 State to initially set.
   */
  constexpr Ternary(State state) noexcept : m_state(state) {}

  /**
   * @brief Constructs a stateful ternary.
   * @param state                 Boolean state to encapsulate.
   */
  constexpr Ternary(bool state) noexcept : m_state(state ? State::T : State::F) {}

  //  OPERATOR METHODS  //

  /// @brief Ensures explicit boolean conversion.
  constexpr operator bool() const noexcept { return m_state == State::T; }

  /// @brief Allow inversion of ternaries.
  friend constexpr inline Ternary operator!(Ternary self) noexcept {
    switch (self.m_state) {
    case State::T: return State::F;
    case State::F: return State::T;
    case State::U: return State::U;
    }
  }

  /// @brief Allow comparison between one-another.
  friend constexpr inline Ternary operator&&(Ternary a, Ternary b) noexcept {
    if (a.m_state == State::F || b.m_state == State::F) return State::F;
    return a.m_state == State::T && b.m_state == State::T ? State::T : State::U;
  }

  /// @brief Allow comparison between one-another.
  friend constexpr inline Ternary operator||(Ternary a, Ternary b) noexcept {
    if (a.m_state == State::F && b.m_state == State::F) return State::F;
    return a.m_state == State::T || b.m_state == State::T ? State::T : State::U;
  }

  /// @brief Allow comparison to one-another.
  friend constexpr inline Ternary operator==(Ternary a, Ternary b) noexcept {
    if (a.indeterminate() || b.indeterminate()) return State::U;
    return a.m_state == b.m_state ? State::T : State::F;
  }

  /// @brief Allow comparison to one-another.
  friend constexpr inline Ternary operator!=(Ternary a, Ternary b) noexcept {
    if (a.indeterminate() || b.indeterminate()) return State::U;
    return a.m_state == b.m_state ? State::F : State::T;
  }

  /// @brief Comparison overloads.
  friend constexpr inline Ternary operator&&(Ternary a, bool b) noexcept { return b ? a : Ternary(State::F); }
  friend constexpr inline Ternary operator&&(bool a, Ternary b) noexcept { return a ? b : Ternary(State::F); }
  friend constexpr inline Ternary operator||(Ternary a, bool b) noexcept { return b ? Ternary(State::T) : a; }
  friend constexpr inline Ternary operator||(bool a, Ternary b) noexcept { return a ? Ternary(State::T) : b; }

  friend constexpr inline Ternary operator==(Ternary a, bool b) noexcept { return a == Ternary(b); }
  friend constexpr inline Ternary operator==(bool a, Ternary b) noexcept { return Ternary(a) == b; }
  friend constexpr inline Ternary operator!=(Ternary a, bool b) noexcept { return a != Ternary(b); }
  friend constexpr inline Ternary operator!=(bool a, Ternary b) noexcept { return Ternary(a) != b; }

  //  PUBLIC METHODS  //

  /// @brief Denotes if currently indeterminate.
  inline constexpr bool indeterminate() const noexcept { return m_state == State::U; }

  /**
   * @brief Roughly checks internal.
   * @param state                 State to expect.
   */
  inline constexpr bool roughly(bool state) const noexcept { return state ? m_state == State::T : m_state == State::F; }

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles printing ternary values.
   * @param os                    Output stream.
   */
  static inline void m_print(std::ostream &os, const Ternary &self) {
    switch (self.m_state) {
    case State::T: os << "true"; break;
    case State::F: os << "false"; break;
    case State::U: os << "unknown"; break;
    }
  }
};

//  FACTORY METHODS  //

/// @brief Constructs an indeterminate ternary.
constexpr Ternary Unknown() noexcept { return Ternary(Ternary::State::U); }

} // namespace $::Unit

//  OPERATOR METHODS  //

#endif
