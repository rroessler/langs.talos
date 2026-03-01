#ifndef _XTDLIB_TRAITS_MOVABLE_HPP
#define _XTDLIB_TRAITS_MOVABLE_HPP

/// C++ Modules
#include <type_traits>

namespace $::Traits {

    /// @brief Movable Traits.
    template <class T>
    struct Move {
        using Assignable = std::enable_if_t<std::is_move_assignable_v<T>>;
        using Constructible = std::enable_if_t<std::is_move_constructible_v<T>>;
        using Enabled = std::enable_if_t<std::is_move_constructible_v<T> && std::is_move_assignable_v<T>>;
    };

}  // namespace $::Traits

#endif
