/// XPC Includes
#include "xpc/pipe/handle.hpp"

//  PUBLIC METHODS  //

#if $_PLATFORM_WINDOWS
XPC::Pipe::Handle XPC::Pipe::Invalid() { return INVALID_HANDLE_VALUE; }
#else
XPC::Pipe::Handle XPC::Pipe::Invalid() { return static_cast<Handle>(-1); }
#endif
