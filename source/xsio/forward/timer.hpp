#ifndef _XSIO_FORWARD_TIMER_HPP
#define _XSIO_FORWARD_TIMER_HPP

/// Vendor Modules
#include <xtdlib/xtdlib.hpp>

/// Forward Definitions
$_FWD(class Event, XSIO::Timer)
$_FWD(class Token, XSIO::Timer)
$_FWD(class Cache, XSIO::Timer)
$_FWD(struct Action, XSIO::Timer)

/// Forward Definitions
$_FWD(using Identifier = size_t, XSIO::Timer)
$_FWD(using Point = $::Chrono::Point, XSIO::Timer)
$_FWD(using Ticks = $::Chrono::Duration, XSIO::Timer)

#endif
