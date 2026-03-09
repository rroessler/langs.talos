#ifndef _TALOS_FORWARD_TESTING_HPP
#define _TALOS_FORWARD_TESTING_HPP

/// Vendor Modules
#include <xtest/xtest.hpp>

/// Forward Declarations
$_FWD(Talos::Testing, class Service)
$_FWD(Talos::Testing, struct Options)
$_FWD(Talos::Testing, class Registry)

/// Forward Definitions
$_FWD(Talos::Testing, using Case = XT::Case)
$_FWD(Talos::Testing, using Bench = XT::Bench)
$_FWD(Talos::Testing, using Group = XT::Group)
$_FWD(Talos::Testing, using Runner = XT::Session::Runner)
$_FWD(Talos::Testing, using Callback = XT::Handle::Callback)
$_FWD(Talos::Testing, using Session = XT::Session::Service)
$_FWD(Talos::Testing, using Handle = $::Ptr::Unique<XT::Handle>)

#endif
