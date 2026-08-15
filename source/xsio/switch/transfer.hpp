#ifndef _XSIO_SWITCH_TRANSFER_HPP
#define _XSIO_SWITCH_TRANSFER_HPP

/// XSIO Includes
#include "xsio/forward/switch.hpp"

namespace XSIO::Switch {

/// @brief Aliased `fcontext_t` value.
using Pointer = void *;

/// @brief Context Transfer Object.
struct Transfer {
  void *data;
  Pointer fctx;
};

} // namespace XSIO::Switch

#endif
