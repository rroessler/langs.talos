#ifndef _XTDLIB_POINTER_UNIQUE_HPP
#define _XTDLIB_POINTER_UNIQUE_HPP

/// C++ Modules
#include <memory>

namespace $::Ptr {

    /// @brief Encompasses a unique pointer.
    template <class T, class D = std::default_delete<T>>
    using Unique = std::unique_ptr<T, D>;

}  // namespace $::Ptr

#endif
