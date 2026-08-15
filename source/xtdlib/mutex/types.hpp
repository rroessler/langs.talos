#ifndef _XTDLIB_MUTEX_TYPES_HPP
#define _XTDLIB_MUTEX_TYPES_HPP

/// Library Includes
#include "xtdlib/portable/stdlib.hpp"

namespace $::Mutex {

//  TYPEDEFS  //

using Auto = std::mutex;
using Shared = std::shared_mutex;
using Recursive = std::recursive_mutex;

} // namespace $::Mutex

#endif
