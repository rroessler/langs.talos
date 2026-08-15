#ifndef _XPC_PIPE_HANDLE_HPP
#define _XPC_PIPE_HANDLE_HPP

/// XPC Includes
#include "xpc/forward/pipe.hpp"

namespace XPC::Pipe {

#if $_PLATFORM_WINDOWS
using Handle = HANDLE;
#else
using Handle = int32_t;
#endif

/// @brief Gets a bad pipe-handle.
Handle Invalid();

} // namespace XPC::Pipe

#endif
