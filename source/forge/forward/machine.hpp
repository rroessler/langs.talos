#ifndef _FORGE_FORWARD_MACHINE_HPP
#define _FORGE_FORWARD_MACHINE_HPP

/// Vendor Modules
#include <xasm/xasm.hpp>
#include <xinv/xinv.hpp>

/// Forge Modules
#include "forge/value/pointer.hpp"

/// Forward Declarations
$_FWD(class Info, Forge::Machine)
$_FWD(class Frame, Forge::Machine)
$_FWD(class Service, Forge::Machine)
$_FWD(class Emitter, Forge::Machine)
$_FWD(struct Builder, Forge::Machine)

/// Forward Definitions
$_FWD(using Label = XASM::Host::Label, Forge::Machine)
$_FWD(using Double = XASM::Host::Double, Forge::Machine)
$_FWD(using Memory = XASM::Host::Memory, Forge::Machine)
$_FWD(using Immediate = XASM::Host::Immediate, Forge::Machine)
$_FWD(using Register = XASM::Host::Register, Forge::Machine)
$_FWD(using Reference = Pointer::Underlying, Forge::Machine)
$_FWD(using Compiler = XASM::Compiler::Universal, Forge::Machine)

#endif
