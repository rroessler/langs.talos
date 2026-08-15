#ifndef _XSIO_TIMER_EVENT_HPP
#define _XSIO_TIMER_EVENT_HPP

/// XSIO Includes
#include "xsio/forward/virtual.hpp"
#include "xsio/timer/action.hpp"

namespace XSIO::Timer {

/// @brief Timer Event.
class Event {
  //  PROPERTIES  //

  /// @brief Timestamp value
  Point m_timestamp;

  /// @brief Timer identifier.
  Identifier m_identifier;

  /// @brief Bound event action.
  $::Unique::Pointer<Action> m_action;

  /// @brief Internal global identifier.
  static inline $::Async::Atomic<Identifier> s_identifier = 0;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a timer-event.
   * @param timestamp         Timestamp value.
   * @param action            Action to run.
   */
  explicit Event(const Point &timestamp, $::Unique::Pointer<Action> &&action)
      : m_timestamp(timestamp), m_identifier(m_next()), m_action(std::move(action)) {}

  //  PUBLIC METHODS  //

  /// @brief Gets the associated event timestamp.
  inline constexpr Point timestamp() const noexcept { return m_timestamp; }

  /// @brief Gets the identifier for the event.
  inline constexpr Identifier identifier() const noexcept { return m_identifier; }

  /**
   * @brief Handles firing the event.
   * @param thread            Thread instance.
   * @param processor         Processor instance.
   */
  inline void fire(Virtual::Thread *thread, Virtual::Processor *processor) const noexcept {
    m_action->execute(thread, processor);
  }

private:
  //  PRIVATE METHODS  //

  /// @brief Handles generating new timer identifiers.
  static inline Identifier m_next() { return s_identifier++; }
};

/// @brief Ranges Heap Comparator.
struct Comparator {
  //  CONSTRUCTORS  //

  /// @brief Constructs a comparator function.
  explicit Comparator() = default;

  //  OPERATOR METHODS  //

  /// @brief Compares two events against their timestamp.
  inline constexpr bool operator()(const Event &left, const Event &right) const {
    return left.timestamp() > right.timestamp();
  }
};

} // namespace XSIO::Timer

#endif
