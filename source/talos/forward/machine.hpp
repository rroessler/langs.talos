#ifndef _TALOS_FORWARD_MACHINE_HPP
#define _TALOS_FORWARD_MACHINE_HPP

/// Vendor Modules
#include <xasm/xasm.hpp>
#include <xinv/xinv.hpp>

/// Talos Modules
#include "talos/value/pointer.hpp"

/// Forward Declarations
$_FWD(class Info, Talos::Machine)
$_FWD(class Frame, Talos::Machine)
$_FWD(class Service, Talos::Machine)
$_FWD(class Emitter, Talos::Machine)
$_FWD(struct Builder, Talos::Machine)

/// Forward Definitions
$_FWD(using Label = XASM::Host::Label, Talos::Machine)
$_FWD(using Double = XASM::Host::Double, Talos::Machine)
$_FWD(using Memory = XASM::Host::Memory, Talos::Machine)
$_FWD(using Immediate = XASM::Host::Immediate, Talos::Machine)
$_FWD(using Register = XASM::Host::Register, Talos::Machine)
$_FWD(using Reference = Pointer::Underlying, Talos::Machine)
$_FWD(using Compiler = XASM::Compiler::Universal, Talos::Machine)

#endif
