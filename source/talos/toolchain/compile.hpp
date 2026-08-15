#ifndef _TALOS_TOOLCHAIN_COMPILE_HPP
#define _TALOS_TOOLCHAIN_COMPILE_HPP

/// Talos Modules
#include "talos/image/arena.hpp"
#include "talos/syntax/tree.hpp"
#include "talos/variable/captures.hpp"

namespace Talos::Toolchain {

/**
 * @brief Handles compiling a module.
 * @param syntax                Syntax tree.
 * @param services              Runtime services.
 */
$::Unique::Pointer<Image::Arena> compile(const Syntax::Tree *syntax, XI::Container *services);

} // namespace Talos::Toolchain

#endif
