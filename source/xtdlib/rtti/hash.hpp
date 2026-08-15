#ifndef _XTDLIB_RTTI_HASH_HPP
#define _XTDLIB_RTTI_HASH_HPP

/// Vendor Includes
#include <xhash/xhash.hpp>

/// Library Includes
#include "xtdlib/rtti/name.hpp"
#include "xtdlib/system/switch.hpp"

namespace $::RTTI {

//  TYPEDEFS  //

/// @brief Internal Type Tagging.
using Tag = $_ARCH_TYPED(uint64_t, uint32_t);

//  PUBLIC METHODS  //

/**
 * @brief Resolves a named hash.
 * @param name                  Name to hash.
 */
static inline consteval Tag Hash(const String::View &name) {
  if constexpr ($_ARCH_TEST()) return XH::FNV::U64(name);
  else return XH::FNV::U32(name); // received 32-bit value
}

/// @brief Resolves a typed hash.
template <class T = void> static inline consteval Tag Hash() {
  if constexpr (std::same_as<T, void>) return Hash<struct Invalid>();
  else return Hash(Name<std::remove_cvref_t<T>>()); // resolve the hash
}

/**
 * @brief Handles asserting types.
 * @param hash                  Hash to check.
 */
template <class T> $_INLINE_PERF static constexpr void Assert($_UNUSED Tag hash) {
  // prepare some statically assigned items
  $_UNUSED auto s_name = Name<T>();
  $_UNUSED auto s_expect = Hash(s_name);

  // and we check in debugging only instances
  $_ASSERT(s_expect == hash, "Value is not of type '{0}'", s_name);
}

} // namespace $::RTTI

#endif
