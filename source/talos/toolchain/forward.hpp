#ifndef _TALOS_TOOLCHAIN_FORWARD_HPP
#define _TALOS_TOOLCHAIN_FORWARD_HPP

/// Forge Includes
#include <forge/toolchain/audit.hpp>
#include <forge/toolchain/bundle.hpp>
#include <forge/toolchain/compile.hpp>
#include <forge/toolchain/format.hpp>
#include <forge/toolchain/launch.hpp>
#include <forge/toolchain/parse.hpp>
#include <forge/toolchain/serve.hpp>
#include <forge/toolchain/test.hpp>

/// Forward Definitions
$_FWD(using Forge::Toolchain::lex, Talos::Toolchain)
$_FWD(using Forge::Toolchain::parse, Talos::Toolchain)
$_FWD(using Forge::Toolchain::audit, Talos::Toolchain)
$_FWD(using Forge::Toolchain::lint, Talos::Toolchain)
$_FWD(using Forge::Toolchain::compile, Talos::Toolchain)
$_FWD(using Forge::Toolchain::launch, Talos::Toolchain)
$_FWD(using Forge::Toolchain::bundle, Talos::Toolchain)
$_FWD(using Forge::Toolchain::format, Talos::Toolchain)
$_FWD(using Forge::Toolchain::serve, Talos::Toolchain)
$_FWD(using Forge::Toolchain::test, Talos::Toolchain)

#endif
