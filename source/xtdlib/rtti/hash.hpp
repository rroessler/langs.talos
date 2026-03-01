#ifndef _XTDLIB_RTTI_HASH_HPP
#define _XTDLIB_RTTI_HASH_HPP

/// Vendor Modules
#include <xhash/xhash.hpp>

/// Library Modules
#include "xtdlib/rtti/name.hpp"

namespace $::RTTI {

    //  TYPEDEFS  //

    /// @brief Internal tag-typing.
    using Tag = uint64_t;

    /// @brief Allows tagging invalid types.
    struct $_ABSTRACT Invalid : public Never {};

    //  PUBLIC METHODS  //

    /// @brief Handles hashing type-names.
    template <class T = Invalid>
    $_INLINE_PERF static consteval Tag Hash() {
        return XH::FNV::U64(Name::of<T>());
    };

}  // namespace $::RTTI

#endif
