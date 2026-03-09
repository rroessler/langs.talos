/// XPC Modules
#include "xpc/pipe/simplex.hpp"

#if $_PLATFORM_POSIX

/// Platform Modules
#include <sys/fcntl.h>
#include <unistd.h>

/// Forward Declarations
$_FWD(XPC::File, bool control(Pipe::Handle, int32_t, int32_t, int32_t, bool))

//  PUBLIC METHODS  //

bool XPC::File::control(Pipe::Handle handle, int32_t get, int32_t set, int32_t bit, bool state) {
    // ignore if the pipe is invalid at all
    if (handle == Pipe::Invalid()) return false;

    // attempt getting the required control flags
    auto flags = ::fcntl(handle, get);
    if (flags < 0) return false;

    // update the flags accordingly
    if (state) flags &= ~bit;
    else flags |= bit;

    // attempt setting the flags now
    return ::fcntl(handle, set, flags) != -1;
}

//  PRIVATE METHODS  //

bool XPC::Pipe::Simplex::m_close() noexcept { return !invalid() && ::close(m_handle) == 0; }

bool XPC::Pipe::Simplex::m_inherits(bool atomic) noexcept {
    return File::control(m_handle, F_GETFD, F_SETFD, FD_CLOEXEC, atomic);
}

bool XPC::Pipe::Simplex::m_blocking(bool state) noexcept {
    return File::control(m_handle, F_GETFL, F_SETFL, O_NONBLOCK, state);
}

ptrdiff_t XPC::Pipe::Reader::m_read(void* buffer, size_t size) {
    return invalid() ? -1 : ::read(*handle(), buffer, size);
}

ptrdiff_t XPC::Pipe::Writer::m_write(const void* buffer, size_t size) {
    return invalid() ? -1 : ::write(*handle(), buffer, size);
}

#endif
