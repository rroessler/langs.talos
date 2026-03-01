#ifndef _FORGE_FORWARD_TESTING_HPP
#define _FORGE_FORWARD_TESTING_HPP

/// Vendor Modules
#include <xtest/xtest.hpp>

/// Forward Declarations
$_FWD(class Service, Forge::Testing)
$_FWD(struct Options, Forge::Testing)
$_FWD(class Registry, Forge::Testing)

/// Forward Definitions
$_FWD(using Case = XT::Case, Forge::Testing)
$_FWD(using Bench = XT::Bench, Forge::Testing)
$_FWD(using Group = XT::Group, Forge::Testing)
$_FWD(using Runner = XT::Session::Runner, Forge::Testing)
$_FWD(using Callback = XT::Handle::Callback, Forge::Testing)
$_FWD(using Session = XT::Session::Service, Forge::Testing)
$_FWD(using Handle = $::Ptr::Unique<XT::Handle>, Forge::Testing)

#endif
