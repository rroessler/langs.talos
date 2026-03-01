#ifndef _XSIO_HPP
#define _XSIO_HPP

/// Async Modules
#include "xsio/async/loop.hpp"
#include "xsio/async/manager.hpp"
#include "xsio/async/options.hpp"
#include "xsio/async/scheduler.hpp"
#include "xsio/async/shutdown.hpp"
#include "xsio/async/storage.hpp"
#include "xsio/async/watchdog.hpp"

/// Context Modules
#include "xsio/context/switch.hpp"
#include "xsio/context/transfer.hpp"

/// Memory Modules
#include "xsio/memory/buffer.hpp"
#include "xsio/memory/stack.hpp"

/// Signal Modules
#include "xsio/signal/code.hpp"
#include "xsio/signal/handler.hpp"

/// Task Modules
#include "xsio/task/deferred.hpp"
#include "xsio/task/executor.hpp"
#include "xsio/task/queue.hpp"

/// Timer Modules
#include "xsio/timer/action.hpp"
#include "xsio/timer/cache.hpp"
#include "xsio/timer/event.hpp"
#include "xsio/timer/token.hpp"
#include "xsio/timer/yield.hpp"

/// Virtual Modules
#include "xsio/virtual/processor.hpp"
#include "xsio/virtual/spinner.hpp"
#include "xsio/virtual/state.hpp"
#include "xsio/virtual/thread.hpp"
#include "xsio/virtual/timeout.hpp"
#include "xsio/virtual/worker.hpp"

#endif
