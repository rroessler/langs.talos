#ifndef _TALOS_FORWARD_SERVER_HPP
#define _TALOS_FORWARD_SERVER_HPP

/// Vendor Includes
#include <xinv/xinv.hpp>
#include <xlsp/xlsp.hpp>
#include <xsio/xsio.hpp>

/// Forward Declarations
$_FWD(Talos::Server, class Events)
$_FWD(Talos::Server, class Worker)
$_FWD(Talos::Server, struct Options)
$_FWD(Talos::Server, class Utilities)
$_FWD(Talos::Server, class Transport)
$_FWD(Talos::Server, class Connection)

/// Forward Definitions
$_FWD(Talos::Server, template <size_t N> using Channel = XLSP::Message::Channel<N>)

#endif
