#ifndef _FORGE_TOOLCHAIN_COMPILE_HPP
#define _FORGE_TOOLCHAIN_COMPILE_HPP

/// Forge Modules
#include "forge/linker/arena.hpp"
#include "forge/syntax/tree.hpp"
#include "forge/variable/captures.hpp"

namespace Forge::Toolchain {

    /**
     * @brief Handles compiling a module.
     * @param syntax                Syntax tree.
     * @param captures              Captures to use.
     */
    $::Ptr::Unique<Linker::Arena> compile(const Syntax::Tree* syntax, const Variable::Captures* captures);

}  // namespace Forge::Toolchain

#endif
