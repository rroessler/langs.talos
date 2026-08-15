#ifndef _TALOS_FORWARD_TESTING_HPP
#define _TALOS_FORWARD_TESTING_HPP

/// Vendor Includes
#include <xtest/xtest.hpp>

/// Forward Declarations
$_FWD(Talos::Testing, class Entry)
$_FWD(Talos::Testing, class Service)
$_FWD(Talos::Testing, struct Options)
$_FWD(Talos::Testing, struct Storage)

/// Forward Definitions
$_FWD(Talos::Testing, using Case = XT::Handle::Case)
$_FWD(Talos::Testing, using Bench = XT::Bench::Mark)
$_FWD(Talos::Testing, using Group = XT::Handle::Group)
$_FWD(Talos::Testing, using Callback = XT::Handle::Callback)
$_FWD(Talos::Testing, using Runner = XT::Session::Runner)
$_FWD(Talos::Testing, using Handle = $::Unique::Pointer<XT::Handle::Base>)

#endif
