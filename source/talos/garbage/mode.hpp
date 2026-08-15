#ifndef _TALOS_GARBAGE_MODE_HPP
#define _TALOS_GARBAGE_MODE_HPP

/// Talos Includes
#include "talos/forward/garbage.hpp"

namespace Talos::Garbage {

/// @brief Potential Collection Modes
enum class Mode : bool { MINOR, MAJOR };

} // namespace Talos::Garbage

#endif
