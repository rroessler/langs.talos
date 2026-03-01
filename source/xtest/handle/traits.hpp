#ifndef _XTEST_HANDLE_TRAITS_HPP
#define _XTEST_HANDLE_TRAITS_HPP

/// XT Modules
#include "xtest/handle/bench.hpp"
#include "xtest/handle/case.hpp"
#include "xtest/handle/group.hpp"

namespace XT::Traits {

    /// @brief Denotes if a test is callable.
    template <class T>
    concept Callable = std::derived_from<T, Case> || std::derived_from<T, Bench>;

}  // namespace XT::Traits

#endif
