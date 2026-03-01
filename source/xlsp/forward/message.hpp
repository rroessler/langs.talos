#ifndef _XLSP_FORWARD_MESSAGE_HPP
#define _XLSP_FORWARD_MESSAGE_HPP

/// Vendor Modules
#include <xtdlib/xtdlib.hpp>

/// Forward Declarations
$_FWD(struct Error, XLSP::Message)

/// Forward Definitions
$_FWD(using Method = $::String::View, XLSP::Message)
$_FWD(using Params = $::Serde::Value, XLSP::Message)

#endif
