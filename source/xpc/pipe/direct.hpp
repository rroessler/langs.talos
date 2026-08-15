#ifndef _XPC_PIPE_DIRECT_HPP
#define _XPC_PIPE_DIRECT_HPP

/// XPC Includes
#include "xpc/forward/pipe.hpp"

namespace XPC::Pipe {

/// @brief The available pipe redirect.
enum class Direct : uint8_t {
  IGNORE, // ignore all pipe communications

  INHERIT, // inherit current process handles
  PIPED,   // redirects via an ad-hoc pipe

  STDOUT, // redirect to parent "stdout"
  STDERR, // redirect to parent "stderr"
};

} // namespace XPC::Pipe

#endif
