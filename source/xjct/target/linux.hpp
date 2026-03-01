#ifndef _XJCT_TARGET_LINUX_HPP
#define _XJCT_TARGET_LINUX_HPP

/// XJCT Modules
#include "xjct/target/abstract.hpp"

namespace XJCT::Target {

    /// @brief Linux Imbuable Target.
    struct Linux : public Abstract {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;

       protected:
        //  PRIVATE METHODS  //

        /// @brief Gets the underlying format.
        inline constexpr Archive::Format m_format() const noexcept { return Archive::Format::DARWIN; }

#if $_PLATFORM_LINUX

        /**
         * @brief Gets an "ELF" resource.
         * @param name                  Resource name.
         */
        Archive::Blob m_resource(const $::String::View& name) const noexcept final;

#endif

        /**
         * @brief Handles imbuing "ELF" executables.
         * @param binary                Binary to imbue.
         * @param options               Imbument options.
         */
        bool m_imbue(Archive::Binary& binary, const Imbue::Options& options) const noexcept final;
    };

}  // namespace XJCT::Target

#endif
