#ifndef _XTDLIB_TRAITS_CONCEPTS_HPP
#define _XTDLIB_TRAITS_CONCEPTS_HPP

/// C++ Includes
#include <concepts>
#include <type_traits>

namespace std {

    //  TYPEDEFS  //

    /// @brief Alias "convertible_to" for use in templates.
    template <class T, class F>
    concept convertible_from = convertible_to<F, T>;

    /// @brief Denotes if a type is "function" like.
    template <class T>
    concept functor = is_function_v<T>;

    /// @brief Denotes if a type is arithmetic.
    template <class T>
    concept arithmetic = is_arithmetic_v<T>;

}  // namespace std

#endif
