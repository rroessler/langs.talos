#ifndef _TALOS_MEMBER_FACTORY_HPP
#define _TALOS_MEMBER_FACTORY_HPP

/// Talos Modules
#include "talos/member/reference.hpp"
#include "talos/runtime/isolate.hpp"

/// Value Modules
#include "talos/value/_inline/value.ipp"

namespace Talos::Member::Factory {

    /**
     * @brief Constructs a reference value.
     * @param args                  Arguments to bind.
     */
    template <class... As>
    static inline $::Ptr::Unique<Reference> reference(As&&... args) {
        return $::New().unique<Reference>(std::forward<As>(args)...);
    }

    /**
     * @brief Constructs a native descriptor.
     * @param isolate               Runtime isolate.
     * @param args                  Arguments to bind.
     */
    template <class... As>
    static inline $::Ptr::Unique<Reference> native(Runtime::Isolate* isolate, As&&... args) {
        return reference(isolate->create<Function::Native>(std::forward<As>(args)...));
    }

}  // namespace Talos::Member::Factory

#endif
