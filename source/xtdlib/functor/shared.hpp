#ifndef _XTDLIB_FUNCTOR_SHARED_HPP
#define _XTDLIB_FUNCTOR_SHARED_HPP

/// C++ Modules
#include <functional>

namespace $::Functor {

    /// @brief A copyable functor.
    template <class F>
    using Shared = std::function<F>;

}  // namespace $::Functor

#endif
