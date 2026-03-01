#ifndef _FORGE_FORWARD_ASYNC_HPP
#define _FORGE_FORWARD_ASYNC_HPP

/// Vendor Modules
#include <xinv/xinv.hpp>
#include <xsio/xsio.hpp>

/// Forward Declarations
$_FWD(struct Main, Forge::Async)
$_FWD(class Worker, Forge::Async)
$_FWD(class Service, Forge::Async)
$_FWD(struct Future, Forge::Async)
$_FWD(struct Thenable, Forge::Async)

/// Forward Declartions
$_FWD(using Options = XSIO::Async::Options, Forge::Async)
$_FWD(using Thread = XSIO::Virtual::Thread, Forge::Async)
$_FWD(using Scheduler = XSIO::Async::Scheduler, Forge::Async)
$_FWD(using Processor = XSIO::Virtual::Processor, Forge::Async)
$_FWD(using Timeout = $::Ptr::Unique<XSIO::Virtual::Timeout>, Forge::Async)
$_FWD(template <class T> using Task = XSIO::Task::Abstract<T>, Forge::Async)

#endif
