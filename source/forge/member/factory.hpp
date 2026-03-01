#ifndef _FORGE_MEMBER_FACTORY_HPP
#define _FORGE_MEMBER_FACTORY_HPP

/// Forge Modules
#include "forge/member/reference.hpp"
#include "forge/runtime/isolate.hpp"

/// Value Modules
#include "forge/value/_inline/value.ipp"

namespace Forge::Member::Factory {

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

}  // namespace Forge::Member::Factory

#endif
