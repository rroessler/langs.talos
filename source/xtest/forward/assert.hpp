#ifndef _XTEST_FORWARD_ASSERT_HPP
#define _XTEST_FORWARD_ASSERT_HPP

/// Vendor Includes
#include <xtdlib/xtdlib.hpp>

/// Forward Declarations
$_FWD(XT::Assert, class That)
$_FWD(XT::Assert, struct Info)
$_FWD(XT::Assert, struct Failure)

/// Forward Definitions
$_FWD(XT::Assert, using Pending = std::vector<Failure>)
$_FWD(XT::Assert, using Trace = std::vector<$::String::Buffer>)

#endif
