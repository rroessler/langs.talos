#ifndef _TALOS_ITERABLE_INTERVAL_HPP
#define _TALOS_ITERABLE_INTERVAL_HPP

/// Talos Includes
#include "talos/forward/iterable.hpp"
#include "talos/number/tagged.hpp"

namespace Talos::Iterable {

/// @brief Range Interval Typing.
class Interval {
  //  PROPERTIES  //

  Number::Floating m_start = 0;
  Number::Floating m_stop = 0;
  Number::Floating m_step = 1;

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs an empty interval.
  constexpr Interval() = default;

  /**
   * @brief Constructs an interval.
   * @param stop                Ending value.
   */
  constexpr Interval(Number::Floating stop) : m_stop(stop), m_step(stop < 0 ? -1 : 1) {}

  /**
   * @brief Constructs an interval.
   * @param start               Starting value.
   * @param stop                Ending value.
   */
  constexpr Interval(Number::Floating start, Number::Floating stop) :
      m_start(start), m_stop(stop), m_step(m_start < m_stop ? -1 : 1) {}

  /**
   * @brief Constructs an interval.
   * @param start               Starting value.
   * @param stop                Ending value.
   * @param step                Stepping value.
   */
  constexpr Interval(Number::Floating start, Number::Floating stop, Number::Floating step) :
      m_start(start), m_stop(stop), m_step(step) {}

  //  PUBLIC METHODS  //

  /// @brief Get the core details for the interval.
  inline constexpr Number::Floating start() const noexcept { return m_start; }
  inline constexpr Number::Floating stop() const noexcept { return m_stop; }
  inline constexpr Number::Floating step() const noexcept { return m_step; }

  /// @brief Denotes if an interval has steppable conclusion.
  inline constexpr bool finite() const noexcept { return (forward() && m_step > 0) || (backward() && m_step < 0); }

  /// @brief Denotes the direction of the interval (ignoring steps).
  inline constexpr bool forward() const noexcept { return m_start < m_stop; }
  inline constexpr bool backward() const noexcept { return m_start > m_stop; }
};

/**
 * @brief Constructs an interval from given arguments.
 * @param isolate                   Runtime isolate.
 * @param args                      Function arguments.
 */
std::optional<Interval> Stepper(Runtime::Isolate *isolate, const Function::Args &args);

} // namespace Talos::Iterable

#endif
