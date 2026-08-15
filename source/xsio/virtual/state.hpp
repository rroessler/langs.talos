#ifndef _XSIO_VIRTUAL_STATE_HPP
#define _XSIO_VIRTUAL_STATE_HPP

/// XSIO Includes
#include "xsio/forward/virtual.hpp"

namespace XSIO::Virtual {

/// @brief Available Virtual States.
enum class State : uint8_t {
  CLEANED, // Thread/Worker is clean and can be assigned.

  SLEEPING,  // Worker is currently sleeping.
  ACQUIRING, // Worker is acquiring a processor.

  NATIVE,  // Thread/Worker is inside a native section.
  STOPPED, // Worker is currently stopped from working.

  READY,   // Thread is ready for execution.
  WAITING, // Thread is currently waiting.
  RUNNING, // Thread/Worker is currently running.
  EXITED,  // Thread has exited their current task.

  SHUTDOWN, // Thread has requested a shutdown phase (must be last).
};

} // namespace XSIO::Virtual

#endif
