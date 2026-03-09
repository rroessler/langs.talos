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
$_FWD(XSIO::Virtual, class Worker)
$_FWD(XSIO::Virtual, class Thread)
$_FWD(XSIO::Virtual, class Timeout)
$_FWD(XSIO::Virtual, class Spinner)
$_FWD(XSIO::Virtual, class Processor)
$_FWD(XSIO::Virtual, enum class State : uint8_t)

/// Forward Definitions
$_FWD(XSIO::Virtual, using Native = $::Functor::Unique<void()>)

#endif
