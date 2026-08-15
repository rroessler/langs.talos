#ifndef _TALOS_FORWARD_REGISTER_HPP
#define _TALOS_FORWARD_REGISTER_HPP

/// Vendor Includes
#include <xasm/xasm.hpp>

/// Forward Declarations
$_FWD(Talos::Register, class List)
$_FWD(Talos::Register, struct Span)
$_FWD(Talos::Register, struct Slot)
$_FWD(Talos::Register, class Scoped)

/// Forward Definitions
$_FWD(Talos::Register, using Encoded = uint16_t)
$_FWD(Talos::Register, using Host = XASM::Host::Register)

#endif
