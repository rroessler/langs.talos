#ifndef _TALOS_FORWARD_ASYNC_HPP
#define _TALOS_FORWARD_ASYNC_HPP

/// Vendor Modules
#include <xinv/xinv.hpp>
#include <xsio/xsio.hpp>

/// Forward Declarations
$_FWD(Talos::Async, struct Main)
$_FWD(Talos::Async, class Worker)
$_FWD(Talos::Async, class Service)
$_FWD(Talos::Async, struct Future)
$_FWD(Talos::Async, struct Thenable)

/// Forward Declartions
$_FWD(Talos::Async, using Options = XSIO::Async::Options)
$_FWD(Talos::Async, using Thread = XSIO::Virtual::Thread)
$_FWD(Talos::Async, using Scheduler = XSIO::Async::Scheduler)
$_FWD(Talos::Async, using Processor = XSIO::Virtual::Processor)
$_FWD(Talos::Async, using Timeout = $::Ptr::Unique<XSIO::Virtual::Timeout>)
$_FWD(Talos::Async, template <class T> using Task = XSIO::Task::Abstract<T>)

#endif
