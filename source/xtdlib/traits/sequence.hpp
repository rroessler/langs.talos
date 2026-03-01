#ifndef _XTDLIB_TRAITS_SEQUENCE_HPP
#define _XTDLIB_TRAITS_SEQUENCE_HPP

/// C++ Modules
#include <type_traits>

namespace $::Traits {

    /// @brief Logical "OR" - Any of concept.
    template <class T, class... As>
    concept Disjunction = std::disjunction_v<std::is_same<T, As>...>;

    /// @brief Logical "AND" - All of concept.
    template <class T, class... As>
    concept Conjunction = std::conjunction_v<std::is_same<T, As>...>;

}  // namespace $::Traits

#endif
