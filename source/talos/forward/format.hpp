#ifndef _TALOS_FORWARD_FORMAT_HPP
#define _TALOS_FORWARD_FORMAT_HPP

/// Vendor Includes
#include <xtdlib/xtdlib.hpp>

/// Forward Declarations
$_FWD(struct Node, Talos::Format)
$_FWD(class Reader, Talos::Format)
$_FWD(class Writer, Talos::Format)
$_FWD(class Storage, Talos::Format)
$_FWD(class Pipeline, Talos::Format)
$_FWD(struct Options, Talos::Format)
$_FWD(class Dispatch, Talos::Format)

/// Forward Definitions
$_FWD(using Sigil = size_t, Talos::Format)
$_FWD(using Buffer = std::vector<Node*>, Talos::Format)
$_FWD(using Result = std::optional<$::String::Buffer>, Talos::Format)

#endif
