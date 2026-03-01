/// XPC Modules
#include "xpc/pipe/duplex.hpp"

#if $_PLATFORM_POSIX

/// Platform Modules
#include <unistd.h>

//  PRIVATE METHODS  //

XPC::Pipe::Duplex XPC::Pipe::Duplex::m_create(Atomic inherit) noexcept {
    int s_fd[2];  // output file-descriptors to be used

    // ensure we can actually construct our pipes here
    $_EXPECT(::pipe(s_fd) == 0, "Failed to create pipe");

    // define the underlying pipes now
    auto duplex = Duplex(s_fd[0], s_fd[1]);

    // set the inheritable properties as necessary
    if (!static_cast<bool>(inherit)) duplex.m_input.atomic(false), duplex.m_output.atomic(false);

    // and resolve the final result
    return duplex;
}

#endif
