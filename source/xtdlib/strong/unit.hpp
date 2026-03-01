#ifndef _XTDLIB_STRONG_UNIT_HPP
#define _XTDLIB_STRONG_UNIT_HPP

/// C++ Modules
#include <limits>

/// Library Modules
#include "xtdlib/strong/infer.hpp"
#include "xtdlib/traits/concepts.hpp"

namespace $::Strong {

    /// @brief Encapsulates strongly-typed numerics.
    template <std::arithmetic T, class P>
    class Unit : public Base<T, P> {
        //  PROPERTIES  //

        /// @brief The encapsulated value.
        T m_value = m_minimum();

       public:
        //  CONSTRUCTORS  //

        /// @brief Allow default construction.
        constexpr Unit() = default;

        /// @brief Allow copy/move constructors/
        constexpr Unit(const T& value) : m_value(value) {}
        constexpr Unit(T&& value) : m_value(std::move(value)) {}

        //  OPERATOR METHODS  //

        inline constexpr operator T&() noexcept { return m_value; }
        inline constexpr operator const T&() const noexcept { return m_value; }

        inline constexpr Unit& operator=(const T& value) { return m_value = value, *this; }
        inline constexpr Unit& operator=(T&& value) { return m_value = std::move(value), *this; }

       protected:
        //  PRIVATE METHODS  //

        inline constexpr T& m_underlying() noexcept { return m_value; }
        inline constexpr const T& m_underlying() const noexcept { return m_value; }

        static inline constexpr T m_minimum() noexcept { return std::numeric_limits<T>::min(); }
        static inline constexpr T m_maximum() noexcept { return std::numeric_limits<T>::max(); }
    };

}  // namespace $::Strong

#endif
