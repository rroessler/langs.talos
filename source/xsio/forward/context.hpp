#ifndef _XSIO_FORWARD_CONTEXT_HPP
#define _XSIO_FORWARD_CONTEXT_HPP

/// XSIO Modules
#include "xsio/forward/virtual.hpp"

/// Forward Declarations
$_FWD(struct Switch, XSIO)
$_FWD(struct Transfer, XSIO::Context)

/// Forward Definitions
$_FWD(using Pointer = void*, XSIO::Context)
$_FWD(using Callback = $::Functor::Unique<void(Virtual::Thread*, Virtual::Processor*)>, XSIO::Context)

#endif
