#ifndef _XSIO_HPP
#define _XSIO_HPP

/// Async Includes
#include "xsio/async/manager.hpp"
#include "xsio/async/options.hpp"
#include "xsio/async/scheduler.hpp"
#include "xsio/async/shutdown.hpp"
#include "xsio/async/storage.hpp"
#include "xsio/async/watchdog.hpp"

/// Memory Includes
#include "xsio/memory/buffer.hpp"
#include "xsio/memory/stack.hpp"

/// Switch Includes
#include "xsio/switch/context.hpp"
#include "xsio/switch/transfer.hpp"

/// Task Includes
#include "xsio/task/deferred.hpp"
#include "xsio/task/executor.hpp"
#include "xsio/task/queue.hpp"
#include "xsio/task/scheduler.hpp"
#include "xsio/task/spinner.hpp"
#include "xsio/task/timeout.hpp"

/// Timer Includes
#include "xsio/timer/action.hpp"
#include "xsio/timer/cache.hpp"
#include "xsio/timer/event.hpp"
#include "xsio/timer/token.hpp"
#include "xsio/timer/yield.hpp"

/// Virtual Includes
#include "xsio/virtual/processor.hpp"
#include "xsio/virtual/state.hpp"
#include "xsio/virtual/thread.hpp"
#include "xsio/virtual/worker.hpp"

#endif
