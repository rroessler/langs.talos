#ifndef _XTDLIB_ALLOCATOR_OBJECT_HPP
#define _XTDLIB_ALLOCATOR_OBJECT_HPP

/// Library Includes
#include "xtdlib/allocator/policy.hpp"

/// Policy Includes
#include "xtdlib/allocator/standard.hpp"

//  MACROS  //

#if $_ENABLE_MTRACE
#define $_ALLOCATOR_OBJECT(C) ::$::Allocator::Object<::$::Allocator::Tag::C>
#else
#define $_ALLOCATOR_OBJECT(C) ::$::Allocator::Base
#endif

//  NAMESPACES  //

namespace $::Allocator {

    /// @brief Internal Allocator Base Object.
    struct $_ABSTRACT Base {};

    /// @brief Explicit Object Instances.
    template <class C, Policy::Validate P = Policy::Default>
    struct $_ABSTRACT Object : public Base {
        //  OPERATOR METHODS  //

        inline void* operator new(size_t, void* pointer) { return pointer; }

        inline void* operator new(size_t size, const $::Location& location = $::Location()) {
            return P::allocate(size, location, Category($::RTTI::Name::of<C>()));
        }

        inline void* operator new[](size_t size, const $::Location& location = $::Location()) {
            return P::allocate(size, location, Category($::RTTI::Name::of<C>()));
        }

        inline void operator delete(void* pointer) { P::deallocate(pointer); }
        inline void operator delete(void* pointer, void*) { P::deallocate(pointer); }
        inline void operator delete[](void* pointer) { P::deallocate(pointer); }
    };

}  // namespace $::Allocator

#endif
