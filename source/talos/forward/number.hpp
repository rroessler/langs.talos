#ifndef _TALOS_FORWARD_NUMBER_HPP
#define _TALOS_FORWARD_NUMBER_HPP

/// Vendor Includes
#include <xtdlib/xtdlib.hpp>

/// Forward Declarations
$_FWD(Talos::Number, struct Bignum)
$_FWD(Talos::Number, struct Tagged)

/// Forward Definitions
$_FWD(Talos::Number, using Floating = $_ARCH_TYPED(double, float))
$_FWD(Talos::Number, using Integral = $_ARCH_TYPED(int64_t, int32_t))

#endif
