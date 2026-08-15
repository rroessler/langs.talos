/// XPC Includes
#include "xpc/pipe/simplex.hpp"

#if $_PLATFORM_WINDOWS

//  PUBLIC METHODS  //

//  PRIVATE METHODS  //

bool XPC::Pipe::Simplex::m_close() noexcept { return !invalid() && ::CloseHandle(m_handle); }

bool XPC::Pipe::Simplex::m_inherits(bool atomic) noexcept {
  return !invalid() && ::SetHandleInformation(m_handle, HANDLE_FLAG_INHERIT, atomic ? HANDLE_FLAG_INHERIT : 0);
}

bool XPC::Pipe::Simplex::m_blocking(bool state) noexcept {
  // ignore if the handle is invalid
  if (invalid()) return false;

  // prepare the flags that we will update here
  DWORD flags = 0;

  // get the current pipe flags now
  if (!::GetNamedPipeHandleState(m_handle, &flags, nullptr, nullptr, nullptr, nullptr, 0)) return false;

  // update the current flags being used now
  flags = state ? flags & ~PIPE_NOWAIT : flags | PIPE_NOWAIT;

  // and actually set the new flags to be used
  return ::SetNamedPipeHandleState(m_handle, &flags, nullptr, nullptr);
}

ptrdiff_t XPC::Pipe::Reader::m_read(void *buffer, size_t size) {
  // ignore if the pipe is invalid at all
  if (invalid()) return 0;

  // prepare a suitable output bytes
  DWORD bytes = 0;

  // attempt reading the instance now
  bool result = ::ReadFile(*handle(), buffer, static_cast<DWORD>(size), &bytes, nullptr);

  // if successful, then return bytes read
  if (result) return bytes;

  // check for common errors
  switch (::GetLastError()) {
  case ERROR_NO_DATA: return 0; // valid
  default: return static_cast<ptrdiff_t>(-1);
  }
}

ptrdiff_t XPC::Pipe::Writer::m_write(const void *buffer, size_t size) {
  // ignore if the pipe is invalid at all
  if (invalid()) return 0;

  // prepare a suitable output bytes
  DWORD bytes = 0;

  // attempt writing a result now
  return ::WriteFile(*handle(), buffer, static_cast<DWORD>(size), &bytes, nullptr) ? bytes : -1;
}

#endif
