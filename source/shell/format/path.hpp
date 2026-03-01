#ifndef _SHELL_FORMAT_PATH_HPP
#define _SHELL_FORMAT_PATH_HPP

/// Vendor Modules
#include <talos/talos.hpp>

namespace Shell::Format::Path {

    /**
     * @brief Handles resolving format paths.
     * @param target                Target to resolve.
     */
    std::vector<$::URI::Buffer> resolve(const $::String::View& target);

}  // namespace Shell::Format::Path

#endif
