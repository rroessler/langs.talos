#ifndef _XJCT_SENTINEL_FUSE_HPP
#define _XJCT_SENTINEL_FUSE_HPP

/// XJCT Includes
#include "xjct/sentinel/view.hpp"

namespace XJCT::Sentinel {

    /// @brief Compile Time Fuse.
    template <$::String::Literal F>
    struct Fuse {
        //  TYPEDEFS  //

        /// @brief Ensure the sentinel has a suitable ending.
        static_assert(F.view().ends_with(":0"), "Fuse must end with ':0'");

        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted sentinel.
        constexpr Fuse() = default;

        //  PUBLIC METHODS  //

        /// @brief Constructs a view from the fuse.
        inline constexpr View view() const noexcept { return View(F.view()); }

        /// @brief Gets the underlying fuse value.
        inline constexpr volatile const char* data() const noexcept { return F.data(); }
    };

}  // namespace XJCT::Sentinel

#endif
