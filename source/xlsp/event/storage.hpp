#ifndef _XLSP_EVENTS_CACHE_HPP
#define _XLSP_EVENTS_CACHE_HPP

/// C++ Includes
#include <deque>

/// XLSP Includes
#include "xlsp/event/responder.hpp"

namespace XLSP::Event {

    /// @brief Function Collection Mapping.
    template <class F>
    using Collection = $::Record<$::Functor::Unique<F>>;

    /// @brief Reply Answer Callback.
    using Answer = $::Functor::Unique<void(const Message::Result<$::Serde::Value>&)>;

    /// @brief Pending Response Typing.
    struct Pending {
        //  PROPERTIES  //

        /// @brief Bound answer value.
        Answer answer;

        /// @brief Response identifier.
        $::String::Buffer identifier;

        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a pending response.
         * @param identifier                Response identifier.
         * @param answer                    Answer to formulate.
         */
        constexpr Pending(const $::String::Buffer& identifier, Answer&& answer) :
            answer(answer), identifier(identifier) {}

        //  OPERATOR METHODS  //

        /// @brief Explicit operators available.
        inline constexpr bool operator==(const Pending& other) const noexcept { return identifier == other.identifier; }
        inline constexpr bool operator!=(const Pending& other) const noexcept { return identifier != other.identifier; }
    };

    /// @brief Events Storage Container.
    struct Storage {
        //  PROPERTIES  //

        /// @brief Current call-identifier.
        int64_t identifier = 0;

        /// @brief Available event mutexes.
        struct {
            mutable $::Mutex::Auto reply;   // Response mutex.
            mutable $::Mutex::Auto cancel;  // Cancellation mutex.
        } mutex;

        /// @brief Pending response callbacks.
        std::deque<Pending> responses = {};

        /// @brief Currently pending cancellations.
        $::Set<$::String::Buffer> cancellations = {};

        /// @brief Currently bound notifications.
        Collection<void(const $::Serde::Value&)> notifications = {};

        /// @brief Currently bound requests.
        Collection<void(const $::Serde::Value&, Answer&&)> requests = {};

        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted cache instance.
        explicit Storage() = default;
    };

}  // namespace XLSP::Event

#endif
