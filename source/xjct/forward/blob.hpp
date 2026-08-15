#ifndef _XJCT_FORWARD_BLOB_HPP
#define _XJCT_FORWARD_BLOB_HPP

/// Vendor Includes
#include <xtdlib/xtdlib.hpp>

/// Forward Definitions
$_FWD(XJCT::Blob, using View = $::String::View)
$_FWD(XJCT::Blob, using Bytes = std::vector<uint8_t>)
$_FWD(XJCT::Blob, template <class T> concept Value = std::is_arithmetic_v<T>)

#endif
