#ifndef _XTDLIB_CONTAINER_MAP_HPP
#define _XTDLIB_CONTAINER_MAP_HPP

/// Vendor Includes
#include <ankerl/unordered_dense.h>

/// Library Includes
#include "xtdlib/string/buffer.hpp"
#include "xtdlib/string/view.hpp"

namespace $ {

    /// @brief Explicit Map Typing.
    template <class K, class T, class H = ankerl::unordered_dense::hash<K>>
    using Map = ankerl::unordered_dense::map<K, T, H>;

    template <class T, class H = ankerl::unordered_dense::hash<String::Buffer>>
    using Dict = Map<String::Buffer, T, H>;

    /// @brief Explicit Dictionrary Typing.
    template <class T, class H = ankerl::unordered_dense::hash<String::View>>
    using Record = Map<String::View, T, H>;

}  // namespace $

#endif
