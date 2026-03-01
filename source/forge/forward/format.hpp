#ifndef _FORGE_FORWARD_FORMAT_HPP
#define _FORGE_FORWARD_FORMAT_HPP

/// Vendor Includes
#include <xtdlib/xtdlib.hpp>

/// Forward Declarations
$_FWD(struct Node, Forge::Format)
$_FWD(class Reader, Forge::Format)
$_FWD(class Writer, Forge::Format)
$_FWD(class Storage, Forge::Format)
$_FWD(class Pipeline, Forge::Format)
$_FWD(struct Options, Forge::Format)
$_FWD(class Dispatch, Forge::Format)

/// Forward Definitions
$_FWD(using Sigil = size_t, Forge::Format)
$_FWD(using Buffer = std::vector<Node*>, Forge::Format)
$_FWD(using Result = std::optional<$::String::Buffer>, Forge::Format)

#endif
