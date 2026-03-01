#ifndef _XJCT_TARGET_WINDOWS_HPP
#define _XJCT_TARGET_WINDOWS_HPP

/// XJCT Modules
#include "xjct/target/abstract.hpp"

namespace XJCT::Target {

    /// @brief Windows Imbuable Target.
    struct Windows : public Abstract {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;

       protected:
        //  PRIVATE METHODS  //

        /// @brief Gets the underlying format.
        inline constexpr Archive::Format m_format() const noexcept { return Archive::Format::DARWIN; }

#if $_PLATFORM_WINDOWS

        /**
         * @brief Gets a "PE" resource.
         * @param name                  Resource name.
         */
        Archive::Blob m_resource(const $::String::View& name) const noexcept final;

#endif

        /**
         * @brief Handles imbuing "PE" executables.
         * @param binary                Binary to imbue.
         * @param options               Imbument options.
         */
        bool m_imbue(Archive::Binary& binary, const Imbue::Options& options) const noexcept final;
    };

}  // namespace XJCT::Target

#endif
