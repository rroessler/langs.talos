#ifndef _XTDLIB_UTILITY_GLOBAL_HPP
#define _XTDLIB_UTILITY_GLOBAL_HPP

/// Library Includes
#include "xtdlib/mutex/lock.hpp"
#include "xtdlib/mutex/types.hpp"
#include "xtdlib/pointer/shared.hpp"

namespace $::Global {

/// @brief Storage for global singletons.
template <class T> static inline constexpr std::pair<Shared::Pointer<T> &, Mutex::Auto &> storage() {
  static auto s_mutex = Mutex::Auto();
  static Shared::Pointer<T> s_instance = nullptr;
  return {s_instance, s_mutex}; // prepare output
}

/// @brief Allows accessing a globally initialized value.
template <class T, class... As> static inline constexpr T *get(As &&...args) {
  auto [instance, mutex] = storage<T>(); // get the storage
  $_UNUSED $_AUTO = Lock::guard(mutex);  // and lock the getter
  if ($_LIKELY(instance != nullptr)) return instance.get();
  return (instance = Shared::New<T>(std::forward<As>(args)...)).get();
}

} // namespace $::Global

#endif
