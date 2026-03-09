#ifndef _XSIO_FORWARD_CONTEXT_HPP
#define _XSIO_FORWARD_CONTEXT_HPP

/// XSIO Modules
#include "xsio/forward/virtual.hpp"

/// Forward Declarations
$_FWD(XSIO, struct Switch)
$_FWD(XSIO::Context, struct Transfer)

/// Forward Definitions
$_FWD(XSIO::Context, using Pointer = void*)
$_FWD(XSIO::Context, using Callback = $::Functor::Unique<void(Virtual::Thread*, Virtual::Processor*)>)

#endif
