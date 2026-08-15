#ifndef _TALOS_DYLIB_INLINE_IPP
#define _TALOS_DYLIB_INLINE_IPP

/// Talos Includes
#include "talos/dylib/registry.hpp"
#include "talos/member/factory.hpp"

/// Builtins Includes
#include "talos/builtins/_inline/assert.ipp"

//  MACROS  //

/// @brief Allows unwrapping dynamic library exports.
#define TALOS_MM_DYLIB_UNWRAP(N, ...)                                                  \
  exports.fields().emplace(#N, Member::Factory::native(isolate, m_##N, m_name(), #N));

/// @brief Exposes a dynamic library addon.
#define TALOS_MM_DYLIB_ADDON(P, L, ...)                                                                 \
  __attribute((used)) static const $_AUTO = Talos::Dylib::Registry::install<Talos::Package::P>();       \
  Talos::Package::P::P(Runtime::Isolate *isolate, Dylib::Exports &exports) { L(TALOS_MM_DYLIB_UNWRAP) }

/// @brief Exposes a dynamic library method.
#define TALOS_MM_DYLIB_DEFINE(N, ...)                                                                     \
  static Value::Any m_##N(Runtime::Isolate *isolate, const Function::Args &args $_PP_VARGS(__VA_ARGS__));

/// @brief Exposes a dynamic library method.
#define TALOS_MM_DYLIB_METHOD(P, N, I, A, ...)                                                                     \
  Talos::Value::Any Talos::Package::P::m_##N(Runtime::Isolate *I, const Function::Args &A $_PP_VARGS(__VA_ARGS__))

#endif
