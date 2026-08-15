#ifndef _TALOS_BUILTINS_STORAGE_HPP
#define _TALOS_BUILTINS_STORAGE_HPP

/// Talos Includes
#include "talos/builtins/inspect.hpp"
#include "talos/member/storage.hpp"

namespace Talos::Builtins {

/**
 * @brief Allows constructing member storage.
 * @param initializer               Initializer to bind.
 */
template <class T>
static inline constexpr Member::Storage Storage(const Member::Storage::Initializer &initializer = {}) {
  return Member::Storage(Inspect<T>::name(), initializer);
}

} // namespace Talos::Builtins

#endif
