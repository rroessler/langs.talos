#ifndef _TALOS_FORWARD_TESTING_HPP
#define _TALOS_FORWARD_TESTING_HPP

/// Vendor Modules
#include <xtest/xtest.hpp>

/// Forward Declarations
$_FWD(class Service, Talos::Testing)
$_FWD(struct Options, Talos::Testing)
$_FWD(class Registry, Talos::Testing)

/// Forward Definitions
$_FWD(using Case = XT::Case, Talos::Testing)
$_FWD(using Bench = XT::Bench, Talos::Testing)
$_FWD(using Group = XT::Group, Talos::Testing)
$_FWD(using Runner = XT::Session::Runner, Talos::Testing)
$_FWD(using Callback = XT::Handle::Callback, Talos::Testing)
$_FWD(using Session = XT::Session::Service, Talos::Testing)
$_FWD(using Handle = $::Ptr::Unique<XT::Handle>, Talos::Testing)

#endif
