#ifndef _XTDLIB_TRAITS_COPYABLE_HPP
#define _XTDLIB_TRAITS_COPYABLE_HPP

/// C++ Modules
#include <type_traits>

namespace $::Traits {

    /// @brief Copyable Traits.
    template <class T>
    struct Copy {
        using Assignable = std::enable_if_t<std::is_copy_assignable_v<T>>;
        using Constructible = std::enable_if_t<std::is_copy_constructible_v<T>>;
        using Enabled = std::enable_if_t<std::is_copy_constructible_v<T> && std::is_copy_assignable_v<T>>;
    };

}  // namespace $::Traits

#endif
