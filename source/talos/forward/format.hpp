#ifndef _TALOS_FORWARD_FORMAT_HPP
#define _TALOS_FORWARD_FORMAT_HPP

/// Vendor Includes
#include <xtdlib/xtdlib.hpp>

/// Forward Declarations
$_FWD(Talos::Format, class Reader)
$_FWD(Talos::Format, class Writer)
$_FWD(Talos::Format, struct Piece)
$_FWD(Talos::Format, class Storage)
$_FWD(Talos::Format, struct Options)
$_FWD(Talos::Format, class Pipeline)

/// Forward Definitions
$_FWD(Talos::Format, using Sigil = size_t)
$_FWD(Talos::Format, using Buffer = std::vector<Piece *>)
$_FWD(Talos::Format, using Result = std::optional<$::String::Buffer>)

#endif
