#ifndef _XTDLIB_CONTAINER_SET_HPP
#define _XTDLIB_CONTAINER_SET_HPP

/// Vendor Includes
#include <ankerl/unordered_dense.h>

namespace $ {

    /// @brief Explicit Set Typing.
    template <class K, class H = ankerl::unordered_dense::hash<K>>
    using Set = ankerl::unordered_dense::set<K, H>;

}  // namespace $

#endif
