#ifndef _XTDLIB_RTTI_NAME_HPP
#define _XTDLIB_RTTI_NAME_HPP

/// Library Includes
#include "xtdlib/lambda/signature.hpp"
#include "xtdlib/macros/attributes.hpp"

namespace $::RTTI {

/// @brief Resolves given compile-time type-names.
template <class T> $_INLINE_FORCE static consteval String::View Name() noexcept {
  // prepare the baseline signature details to be used
  static constexpr auto s_prefix = Lambda::Signature::PREFIX;
  static constexpr auto s_suffix = Lambda::Signature::SUFFIX;

  // ensure that function-signatures can be validly deduced
  static_assert(!!s_prefix.size() && !!s_suffix.size(), "Cannot deduce name-of value");

  static constexpr auto signature = String::View($_FUNCSIG); // prepare
  static constexpr auto start = signature.find(s_prefix) + s_prefix.size();
  return signature.substr(start, signature.find(s_suffix) - start); // trim
}

} // namespace $::RTTI

#endif
