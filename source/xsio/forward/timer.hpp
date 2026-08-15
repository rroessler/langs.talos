#ifndef _XSIO_FORWARD_TIMER_HPP
#define _XSIO_FORWARD_TIMER_HPP

/// Vendor Includes
#include <xtdlib/xtdlib.hpp>

/// Forward Definitions
$_FWD(XSIO::Timer, class Event)
$_FWD(XSIO::Timer, class Token)
$_FWD(XSIO::Timer, class Cache)
$_FWD(XSIO::Timer, struct Action)

/// Forward Definitions
$_FWD(XSIO::Timer, using Identifier = size_t)
$_FWD(XSIO::Timer, using Point = $::Chrono::Point)
$_FWD(XSIO::Timer, using Ticks = $::Chrono::Duration)

#endif
