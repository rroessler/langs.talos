#ifndef _XTDLIB_SPINNER_MODE_HPP
#define _XTDLIB_SPINNER_MODE_HPP

namespace $::Spinner {

/// @brief Available Spinner Modes.
enum class Mode : uint8_t {
  ENABLED,  // fully enabled
  DISABLED, // fully disabled
  PARTIAL,  // partial outputs
  RESOLVE,  // auto-decide here
};

} // namespace $::Spinner

#endif
