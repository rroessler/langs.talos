#ifndef _TALOS_MEMBER_FACTORY_HPP
#define _TALOS_MEMBER_FACTORY_HPP

/// Talos Includes
#include "talos/member/reference.hpp"
#include "talos/runtime/isolate.hpp"

/// Value Includes
#include "talos/value/_inline/value.ipp"

namespace Talos::Member::Factory {

/**
 * @brief Constructs a reference value.
 * @param args                  Arguments to bind.
 */
template <class... As> static inline $::Unique::Pointer<Reference> reference(As &&...args) {
  return $::Unique::New<Reference>(std::forward<As>(args)...);
}

/**
 * @brief Constructs a native descriptor.
 * @param isolate               Runtime isolate.
 * @param args                  Arguments to bind.
 */
template <class... As> static inline $::Unique::Pointer<Reference> native(Runtime::Isolate *isolate, As &&...args) {
  return reference(isolate->create<Function::Native>(std::forward<As>(args)...));
}

} // namespace Talos::Member::Factory

#endif
