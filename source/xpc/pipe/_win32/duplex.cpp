/// XPC Includes
#include "xpc/pipe/duplex.hpp"

#if $_PLATFORM_WINDOWS

//  PRIVATE METHODS  //

XPC::Pipe::Duplex XPC::Pipe::Duplex::m_create(Atomic inherit) noexcept {
  // prepare the security attributes to be used
  SECURITY_ATTRIBUTES security = {
      .nLength = sizeof(SECURITY_ATTRIBUTES),
      .lpSecurityDescriptor = 0,
      .bInheritHandle = static_cast<bool>(inherit),
  };

  // prepare the duplex pipe values
  Handle input, output;

  // attempt creating the incoming pipe now
  $_EXPECT(::CreatePipe(&input, &output, &security, 0));

  // construct the resulting pipe now
  return Duplex(input, output);
}

#endif
