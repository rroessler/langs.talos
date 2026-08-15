#ifndef _XSIO_TIMER_YIELD_HPP
#define _XSIO_TIMER_YIELD_HPP

/// XSIO Includes
#include "xsio/forward/timer.hpp"

namespace XSIO::Timer::Yield {

static Point NEVER = Point(0ms);
static Point SHOULD = Point(1ms);
static Point VALID = Point(2ms);

} // namespace XSIO::Timer::Yield

#endif
