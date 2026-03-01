#ifndef _XTDLIB_RANDOM_SIMPLE_HPP
#define _XTDLIB_RANDOM_SIMPLE_HPP

/// C++ Modules
#include <cstddef>
#include <ctime>

/// Library Modules
#include "xtdlib/random/interface.hpp"

namespace $::Random::Device {

    /// @brief Simple RNG Device.
    struct Simple {
        //  TYPEDEFS  //

        /// @brief Expected device output.
        using Output = size_t;

       private:
        //  PROPERTIES  //

        /// @brief Current RNG state.
        Output m_state = std::time(nullptr);

       public:
        //  PUBLIC METHODS  //

        /// @brief Gets the next RNG value.
        inline constexpr Output next() {
            Output x = m_state;
            x ^= x << 13;
            x ^= x >> 7;
            x ^= x << 17;
            return m_state = x;
        }

        /// @brief Declare entropy as deterministic.
        inline constexpr double entropy() const noexcept { return 0; }

        /// @brief Available numeric limits.
        inline constexpr auto limits() const noexcept { return std::numeric_limits<Output>(); }
    };

    // ensure the simple device is a valid instance
    static_assert(Interface<Simple>, "Invalid Random Device Interface");

}  // namespace $::Random::Device

#endif
