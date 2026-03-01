#ifndef _XTDLIB_CHRONO_CLOCK_HPP
#define _XTDLIB_CHRONO_CLOCK_HPP

/// C++ Modules
#include <chrono>

/// Library Modules
#include "xtdlib/chrono/duration.hpp"
#include "xtdlib/functor/unique.hpp"

namespace $::Clock {

    //  TYPEDEFS  //

    /// @brief Internal Validation Concept.
    template <class T>
    concept Validate = requires {
        typename T::rep;
        typename T::period;
        typename T::duration;
        typename T::time_point;

        T::is_steady;
        T::now();
    };

    /// @brief Underlying Clock Time-Point.
    template <Validate C = std::chrono::high_resolution_clock, class D = C::duration>
    using Point = std::chrono::time_point<C>;

    /// @brief Default Clock Typing.
    using Default = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
        std::chrono::high_resolution_clock, std::chrono::steady_clock>;

    /// @brief Allows value introspection.
    template <Validate T>
    struct Tagged {
        //  CONSTRUCTORS  //

        /// @brief Constructs a tagged clock.
        explicit constexpr Tagged() = default;

        //  OPERATOR METHODS  //

        /// @brief Gets the current "now" time.
        inline constexpr T::time_point operator()() const noexcept { return T::now(); }
    };

    //  PROPERTIES  //

    static inline constexpr auto Steady = Tagged<std::chrono::steady_clock>();
    static inline constexpr auto System = Tagged<std::chrono::system_clock>();
    static inline constexpr auto Performance = Tagged<std::chrono::high_resolution_clock>();

}  // namespace $::Clock

#endif
