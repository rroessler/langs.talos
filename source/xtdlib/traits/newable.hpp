#ifndef _XTDLIB_TRAITS_NEWABLE_HPP
#define _XTDLIB_TRAITS_NEWABLE_HPP

/// C++ Modules
#include <type_traits>

namespace $::Traits {

    /// @brief Checks if a type is newable with the given values.
    template <class T, class... As>
    concept Newable = requires(T, As... args) { new (args...) T; };

}  // namespace $::Traits

#endif
