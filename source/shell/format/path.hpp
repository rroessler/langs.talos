#ifndef _SHELL_FORMAT_PATH_HPP
#define _SHELL_FORMAT_PATH_HPP

/// Vendor Includes
#include <xtdlib/xtdlib.hpp>

namespace Shell::Format {

/**
 * @brief Handles resolving format paths.
 * @param target                Target to resolve.
 */
std::vector<$::URI::Buffer> Path(const $::String::View &target);

} // namespace Shell::Format

#endif
