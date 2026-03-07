#ifndef _TALOS_FORWARD_ASYNC_HPP
#define _TALOS_FORWARD_ASYNC_HPP

/// Vendor Modules
#include <xinv/xinv.hpp>
#include <xsio/xsio.hpp>

/// Forward Declarations
$_FWD(struct Main, Talos::Async)
$_FWD(class Worker, Talos::Async)
$_FWD(class Service, Talos::Async)
$_FWD(struct Future, Talos::Async)
$_FWD(struct Thenable, Talos::Async)

/// Forward Declartions
$_FWD(using Options = XSIO::Async::Options, Talos::Async)
$_FWD(using Thread = XSIO::Virtual::Thread, Talos::Async)
$_FWD(using Scheduler = XSIO::Async::Scheduler, Talos::Async)
$_FWD(using Processor = XSIO::Virtual::Processor, Talos::Async)
$_FWD(using Timeout = $::Ptr::Unique<XSIO::Virtual::Timeout>, Talos::Async)
$_FWD(template <class T> using Task = XSIO::Task::Abstract<T>, Talos::Async)

#endif
