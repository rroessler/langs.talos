#ifndef _XJCT_SENTINEL_VIEW_HPP
#define _XJCT_SENTINEL_VIEW_HPP

/// Vendor Includes
#include <xtdlib/xtdlib.hpp>

namespace XJCT::Sentinel {

    /// @brief Encapsulates a sentinel view.
    class View {
        //  PROPERTIES  //

        /// @brief Underlying view instance.
        $::String::View m_fuse = ":0";

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted view.
        constexpr View() = default;

        /**
         * @brief Constructs a fuse view.
         * @param fuse              Fuse to view.
         */
        constexpr View(const $::String::View& fuse) : m_fuse(fuse) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the fuses prefix value.
        inline constexpr $::String::View prefix() const noexcept { return m_fuse.substr(0, m_fuse.size() - 2); }

        /// @brief Attempts getting a fuses name-component.
        inline constexpr $::String::View name(char separator = '/') const noexcept {
            auto name = prefix();  // prepare prefix
            return name.substr(0, name.find(separator));
        }

        /// @brief Checks for the existence of the sentinel resource.
        inline constexpr bool exists() const noexcept { return m_fuse[m_fuse.size() - 1] == '1'; }

        /// @brief Forces an expectation that the fuse exists.
        inline constexpr void expect() const noexcept { $_EXPECT(exists(), "Expected fuse '{0}' to exist", name()); }
    };

}  // namespace XJCT::Sentinel

#endif
