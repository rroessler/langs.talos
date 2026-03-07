#ifndef _TALOS_CRATE_REGISTRY_HPP
#define _TALOS_CRATE_REGISTRY_HPP

/// Talos Includes
#include "talos/crate/manifest.hpp"

namespace Talos::Crate::Registry {

    /// @brief Gets the global options that are available.
    $::Ptr::Unique<Manifest> global();

    /**
     * @brief Handles scanning for parent crates.
     * @param hint                      Hint to use.
     */
    $::Ptr::Unique<Manifest> scan(const $::URI::View& hint);
    $::Ptr::Unique<Manifest> scan(const $::Filesystem::Path& hint = $::System::cwd());

    /**
     * @brief Handles resolving crate package options.
     * @param file_path                 File path.
     */
    $::Ptr::Unique<Manifest> view(const $::URI::View& resource);
    $::Ptr::Unique<Manifest> view(const $::Filesystem::Path& file_path);

}  // namespace Talos::Crate::Registry

#endif
