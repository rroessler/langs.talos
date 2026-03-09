#ifndef _TALOS_FORWARD_MACHINE_HPP
#define _TALOS_FORWARD_MACHINE_HPP

/// Vendor Modules
#include <xasm/xasm.hpp>
#include <xinv/xinv.hpp>

/// Talos Modules
#include "talos/value/pointer.hpp"

/// Forward Declarations
$_FWD(Talos::Machine, class Info)
$_FWD(Talos::Machine, class Frame)
$_FWD(Talos::Machine, class Service)
$_FWD(Talos::Machine, class Emitter)
$_FWD(Talos::Machine, struct Builder)

/// Forward Definitions
$_FWD(Talos::Machine, using Label = XASM::Host::Label)
$_FWD(Talos::Machine, using Double = XASM::Host::Double)
$_FWD(Talos::Machine, using Memory = XASM::Host::Memory)
$_FWD(Talos::Machine, using Immediate = XASM::Host::Immediate)
$_FWD(Talos::Machine, using Register = XASM::Host::Register)
$_FWD(Talos::Machine, using Reference = Pointer::Underlying)
$_FWD(Talos::Machine, using Compiler = XASM::Compiler::Universal)

#endif
