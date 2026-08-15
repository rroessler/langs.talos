#ifndef _TALOS_FORWARD_MACHINE_HPP
#define _TALOS_FORWARD_MACHINE_HPP

/// Vendor Includes
#include <xasm/xasm.hpp>

/// Talos Includes
#include "talos/forward/runtime.hpp"
#include "talos/function/info.hpp"
#include "talos/value/pointer.hpp"

/// Forward Declarations
$_FWD(Talos::Machine, class Info)
$_FWD(Talos::Machine, class Facts)
$_FWD(Talos::Machine, class Frame)
$_FWD(Talos::Machine, class Logger)
$_FWD(Talos::Machine, class Service)
$_FWD(Talos::Machine, class Emitter)
$_FWD(Talos::Machine, struct Builder)
$_FWD(Talos::Machine, class Allocator)

/// Forward Definitions
$_FWD(Talos::Machine, using Stack = Value::Any *)
$_FWD(Talos::Machine, using Label = XASM::Host::Label)
$_FWD(Talos::Machine, using Double = XASM::Host::Double)
$_FWD(Talos::Machine, using Memory = XASM::Host::Memory)
$_FWD(Talos::Machine, using Immediate = XASM::Host::Immediate)
$_FWD(Talos::Machine, using Reference = Pointer::Underlying)
$_FWD(Talos::Machine, using Compiler = XASM::Compiler::Universal)

#endif
