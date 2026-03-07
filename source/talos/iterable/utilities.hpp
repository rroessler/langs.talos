#ifndef _TALOS_ITERABLE_UTILITIES_HPP
#define _TALOS_ITERABLE_UTILITIES_HPP

/// Talos Modules
#include "talos/iterable/list.hpp"

namespace Talos::Iterable {

    /// @brief Handles
    static inline struct {
        //  OPERATOR METHODS  //

        /**
         * @brief Handles unpacking a value to a span.
         * @param value                 Value to unpack.
         */
        inline constexpr std::span<Value::Any> operator()(Value::Any value) const noexcept {
            return value.is<List>() ? value.as<List>().span() : std::span<Value::Any>();
        }
    } Unpack;

}  // namespace Talos::Iterable

#endif
