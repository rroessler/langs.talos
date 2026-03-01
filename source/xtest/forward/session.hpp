#ifndef _XTEST_FORWARD_SESSION_HPP
#define _XTEST_FORWARD_SESSION_HPP

/// Vendor Modules
#include <xinv/xinv.hpp>

/// Forward Declarations
$_FWD(class Runner, XT::Session)
$_FWD(class Service, XT::Session)
$_FWD(class Registry, XT::Session)
$_FWD(struct Progress, XT::Session)
$_FWD(class Statistics, XT::Session)

/// Forward Definitions
$_FWD(using Bind = Session::Registry, XT)

#endif
