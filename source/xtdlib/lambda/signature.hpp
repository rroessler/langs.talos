#ifndef _XTDLIB_LAMBDA_SIGNATURE_HPP
#define _XTDLIB_LAMBDA_SIGNATURE_HPP

/// Library Includes
#include "xtdlib/string/view.hpp"

namespace $::Lambda::Signature {

#if defined(__clang__)

#define $_FUNCSIG __PRETTY_FUNCTION__
static inline constexpr auto PREFIX = String::View("[T = ");
static inline constexpr auto SUFFIX = String::View("]");

#elif defined(__GNUC__)

#define $_FUNCSIG __PRETTY_FUNCTION__
static inline constexpr auto PREFIX = String::View("with T = ");
static inline constexpr auto SUFFIX = String::View("; ");

#elif defined(__FUNCSIG__)

#define $_FUNCSIG __FUNCSIG__
static inline constexpr auto PREFIX = String::View("get_type_name<");
static inline constexpr auto SUFFIX = String::View(">(void)");

#else

#define $_FUNCSIG __func__
static inline constexpr auto PREFIX = String::View();
static inline constexpr auto SUFFIX = String::View();

#endif

} // namespace $::Lambda::Signature

#endif
