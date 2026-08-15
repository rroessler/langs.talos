#ifndef _TALOS_STRING_LIMITS_HPP
#define _TALOS_STRING_LIMITS_HPP

/// Talos Includes
#include "talos/value/common.hpp"

namespace Talos::String::Limits {

/// @brief How big a small tagged string is.
static constexpr size_t SMALL = Pointer::Alignment::VALUE - 1;

} // namespace Talos::String::Limits

#endif
