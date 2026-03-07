#ifndef _TALOS_VALUE_PROXY_HPP
#define _TALOS_VALUE_PROXY_HPP

/// Talos Modules
#include "talos/builtins/traits.hpp"
#include "talos/forward/globals.hpp"
#include "talos/member/descriptor.hpp"
#include "talos/shape/lookup.hpp"

namespace Talos::Value {

    /// @brief Explicit Proxy Methods.
    template <std::derived_from<Any> T>
    struct Proxy : public T {
        //  PUBLIC METHODS  //

        /// @brief Gets the associated value name.
        static inline constexpr $::String::View name() { return Builtins::Traits<T>::name(); }

        /// @brief Gets the associated shape value.
        static inline constexpr Shape::Underlying shape() { return Shape::Lookup<T>(); }

        /**
         * @brief Handles validation of values.
         * @param traits                Tagged pointer traits.
         */
        static inline constexpr bool is(const Pointer::Traits& traits) { return T::m_is(traits); }

        /**
         * @brief Gets the associated pointers truthiness.
         * @param value                 Value to resolve.
         */
        static inline constexpr bool truthiness(const T& value) { return T::m_truthiness(value); }

        /**
         * @brief Handles iterating over object roots.
         * @param value                 Value to yield.
         * @param yield                 Yield callback.
         */
        static inline constexpr void yield(const T& value, const Globals::Each& yield) { T::m_yield(value, yield); }

        /**
         * @brief Handles printing values.
         * @param os                    Output stream.
         * @param value                 Value to be printed.
         */
        static inline constexpr void print($::Stream::Output& os, const T& value) { T::m_print(os, value); }
    };

}  // namespace Talos::Value

#endif
