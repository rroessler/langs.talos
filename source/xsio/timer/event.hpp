#ifndef _XSIO_TIMER_EVENT_HPP
#define _XSIO_TIMER_EVENT_HPP

/// XSIO Modules
#include "xsio/forward/context.hpp"
#include "xsio/forward/virtual.hpp"
#include "xsio/timer/action.hpp"

namespace XSIO::Timer {

    /// @brief Timer Event.
    class Event {
        //  PROPERTIES  //

        Point m_ts;       // Timestamp value.
        Identifier m_id;  // Timer identifier.

        /// @brief Bound event action.
        $::Ptr::Unique<Action> m_action;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a timer-event.
         * @param ts                Timestamp value.
         * @param action            Action to run.
         */
        explicit Event(const Point& ts, $::Ptr::Unique<Action>&& action) :
            m_ts(ts), m_id(m_next()), m_action(std::move(action)) {}

        //  PUBLIC METHODS  //

        inline constexpr Point timestamp() const noexcept { return m_ts; }
        inline constexpr Identifier identifier() const noexcept { return m_id; }

        /**
         * @brief Handles firing the event.
         * @param thread            Thread instance.
         * @param processor         Processor instance.
         */
        inline void fire(Virtual::Thread* thread, Virtual::Processor* processor) const noexcept {
            m_action->execute(thread, processor);
        }

       private:
        //  PRIVATE METHODS  //

        /// @brief Handles generating new timer identifiers.
        static inline Identifier m_next() {
            static $::Atomic<Identifier> s_identifier = 0;
            return s_identifier++;  // get the next identifier
        }
    };

    /// @brief Ranges Heap Comparator.
    struct Comparator {
        //  CONSTRUCTORS  //

        /// @brief Constructs a comparator function.
        explicit Comparator() = default;

        //  OPERATOR METHODS  //

        /// @brief Compares two events against their timestamp.
        constexpr bool operator()(const Event& left, const Event& right) const {
            return left.timestamp() > right.timestamp();
        }
    };

}  // namespace XSIO::Timer

#endif
