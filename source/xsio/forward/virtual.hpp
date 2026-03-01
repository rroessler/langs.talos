#ifndef _XSIO_FORWARD_VIRTUAL_HPP
#define _XSIO_FORWARD_VIRTUAL_HPP

/// Vendor Modules
#include <xtdlib/xtdlib.hpp>

/// Memory Declarations
$_ALLOCATOR_CATEGORY(XSIO_STACK)
$_ALLOCATOR_CATEGORY(XSIO_THREAD)
$_ALLOCATOR_CATEGORY(XSIO_WORKER)
$_ALLOCATOR_CATEGORY(XSIO_PROCESSOR)

/// Forward Declarations
$_FWD(class Worker, XSIO::Virtual)
$_FWD(class Thread, XSIO::Virtual)
$_FWD(class Timeout, XSIO::Virtual)
$_FWD(class Spinner, XSIO::Virtual)
$_FWD(class Processor, XSIO::Virtual)
$_FWD(enum class State : uint8_t, XSIO::Virtual)

/// Forward Definitions
$_FWD(using Native = $::Functor::Unique<void()>, XSIO::Virtual)

#endif
