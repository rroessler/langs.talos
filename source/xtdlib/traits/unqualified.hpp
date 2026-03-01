#ifndef _XTDLIB_TRAITS_UNQUALIFIED_HPP
#define _XTDLIB_TRAITS_UNQUALIFIED_HPP

/// C++ Modules
#include <type_traits>

namespace $::Traits {

    /// @brief Logical "OR" - Any of concept.
    template <class T>
    using Unqualified = typename std::remove_cvref_t<typename std::remove_pointer_t<T>>;

}  // namespace $::Traits

#endif
