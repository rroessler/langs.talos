#ifndef _XLSP_FORWARD_MESSAGE_HPP
#define _XLSP_FORWARD_MESSAGE_HPP

/// Vendor Modules
#include <xtdlib/xtdlib.hpp>

/// Forward Declarations
$_FWD(XLSP::Message, struct Error)

/// Forward Definitions
$_FWD(XLSP::Message, using Method = $::String::View)
$_FWD(XLSP::Message, using Params = $::Serde::Value)

#endif
