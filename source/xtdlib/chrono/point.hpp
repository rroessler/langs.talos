#ifndef _XTDLIB_CHRONO_POINT_HPP
#define _XTDLIB_CHRONO_POINT_HPP

/// Library Includes
#include "xtdlib/chrono/clock.hpp"

namespace $::Chrono {

/// @brief Time-Point Alternative.
class Point {
  //  PROPERTIES  //

  /// @brief Encapsulated duration value.
  Duration m_duration;

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs a steady based point.
  constexpr Point() : Point(Clock::Tagged<Clock::Default>()) {}

  /**
   * @brief Constructs any clock based time-point.
   * @param clock                     Tagged clock instance.
   */
  template <Clock::Validate C> constexpr Point(const Clock::Tagged<C> &clock) : Point(clock()) {}

  /**
   * @brief Constructs a time-point.
   * @param point                     Underlying time-point.
   */
  template <Clock::Validate C, class D = C::duration>
  constexpr Point(const Clock::Point<C, D> &point)
      : Point(std::chrono::time_point_cast<Ticks>(point).time_since_epoch()) {}

  /**
   * @brief Constructs a time-point.
   * @param duration                  Time since epoch.
   */
  constexpr Point(const Duration &duration) : m_duration(duration) {}

  //  OPERATOR METHODS  //

  /// @brief Comparison operator for time-points.
  inline constexpr auto operator<=>(const Point &other) const noexcept { return m_duration <=> other.m_duration; }
  inline constexpr auto operator==(const Point &other) const noexcept { return m_duration == other.m_duration; }

  /// @brief Binary "+" operator.
  friend inline constexpr Duration operator+(const Point &left, const Point &right) {
    return {left.m_duration + right.m_duration};
  }

  /// @brief Binary "+" operator.
  friend inline constexpr Point operator+(const Point &point, const Duration &duration) {
    return {point.m_duration + duration};
  }

  /// @brief Binary "-" operator.
  friend inline constexpr Duration operator-(const Point &left, const Point &right) {
    return {left.m_duration - right.m_duration};
  }

  /// @brief Binary "-" operator.
  friend inline constexpr Point operator-(const Point &point, const Duration &duration) {
    return {point.m_duration - duration};
  }

  //  PUBLIC METHODS  //

  /// @brief Gets the time-since "epoch".
  inline constexpr Duration duration() const noexcept { return m_duration; }

  /// @brief Gets the underlying time-point.
  template <Clock::Validate C = Clock::Default>
  inline constexpr Clock::Point<C> underlying(const Clock::Tagged<C> & = Clock::Tagged<C>()) const noexcept {
    auto ticks = m_duration.underlying(); // prepare ticks initially
    auto duration = std::chrono::duration_cast<typename C::duration>(ticks);
    return Clock::Point<C>(duration); // should now be valid for the clock
  }
};

} // namespace $::Chrono

template <>
struct fmt::formatter<$::Chrono::Point, char> : fmt::formatter<$::Clock::Point<std::chrono::system_clock>, char> {
  //  TYPEDEFS  //

  /// @brief System Time-Point.
  using System = $::Clock::Point<std::chrono::system_clock>;

  //  PUBLIC METHODS  //

  /// @brief Handles printing time-points.
  auto format(const $::Chrono::Point &point, fmt::format_context &ctx) const -> decltype(ctx.out()) {
    return fmt::formatter<System, char>::format(point.underlying($::Clock::System), ctx);
  }
};

#endif
