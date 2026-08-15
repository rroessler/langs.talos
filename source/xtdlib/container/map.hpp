#ifndef _XTDLIB_CONTAINER_MAP_HPP
#define _XTDLIB_CONTAINER_MAP_HPP

/// Vendor Includes
#include <ankerl/unordered_dense.h>

/// Library Includes
#include "xtdlib/string/buffer.hpp"
#include "xtdlib/string/view.hpp"

namespace $::Map {

/// @brief Baseline Map Typing.
template <class K, class T, class H = ankerl::unordered_dense::hash<K>>
using Base = ankerl::unordered_dense::map<K, T, H>;

/// @brief Explicit Set Typing (keys-only).
template <class K, class H = ankerl::unordered_dense::hash<K>> using Set = ankerl::unordered_dense::set<K, H>;

/// @brief Explicit Dictionary Typing (buffer).
template <class T, class H = ankerl::unordered_dense::hash<String::Buffer>> using Dict = Base<String::Buffer, T, H>;

/// @brief Explicit Record Typing (view).
template <class T, class H = ankerl::unordered_dense::hash<String::View>> using Record = Base<String::View, T, H>;

} // namespace $::Map

#endif
