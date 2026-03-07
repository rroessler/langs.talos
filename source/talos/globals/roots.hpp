#ifndef _TALOS_GLOBALS_ROOTS_HPP
#define _TALOS_GLOBALS_ROOTS_HPP

/// Talos Modules
#include "talos/forward/globals.hpp"
#include "talos/value/common.hpp"

namespace Talos::Globals {

    /// @brief Global Roots Generator.
    class Each {
        //  PROPERTIES  //

        /// @brief The underlying callback handler.
        Callback m_callback = [](Value::Any&) {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Default construction.
        explicit Each() = default;

        /**
         * @brief Constructs an each callback.
         * @param callback              Callback to bind.
         */
        explicit Each(Callback&& callback) : m_callback(callback) {}

        //  OPERATOR METHODS  //

        /**
         * @brief Handles yielding values.
         * @param value                 Values to yield.
         */
        inline constexpr void operator()(Value::Any& value) const noexcept { m_callback(value); }
        inline constexpr void operator()(const std::span<Value::Any>& values) const noexcept {
            for (auto& value : values) m_callback(value);  // iterate over the values now
        }
    };

    // using Each = std::generator<Value::Any, Value::Any>;

    /// @brief Available Global Roots.
    class Roots {
        //  PROPERTIES  //

        /// @brief Currently bound roots handlers.
        std::vector<$::Functor::Unique<void(const Each&)>> m_handlers = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted set of roots.
        explicit Roots() = default;

        //  PUBLIC METHODS  //

        /**
         * @brief Binds a roots callback.
         * @param handler                    Handler to bind.
         */
        inline constexpr void bind($::Functor::Unique<void(const Each&)>&& handler) {
            m_handlers.emplace_back(std::move(handler));
        }

        /// @brief Handles safely iterating over the roots.
        inline void each(Callback&& callback) const noexcept {
            // prepare the each iterator now
            auto each = Each(std::move(callback));

            // prepare the underlying each handler
            for (const auto& handler : m_handlers) handler(each);
        }
    };

}  // namespace Talos::Globals

#endif
