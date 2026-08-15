#ifndef _XHASH_WYXX_HPP
#define _XHASH_WYXX_HPP

/// Vendor Includes
#include <ankerl/unordered_dense.h>

/// Hash Includes
#include "xhash/forward/algorithms.hpp"

namespace XH::WY {

/// @brief Handles implementation of the "wyhash" algorithm.
static inline struct {
  //  OPERATOR METHODS  //

  /// @brief Handles hashing any values.
  template <class T> inline constexpr uint64_t operator()(const T &value) const noexcept {
    return ankerl::unordered_dense::hash<T>()(value);
  }
} XX;

} // namespace XH::WY

#endif
