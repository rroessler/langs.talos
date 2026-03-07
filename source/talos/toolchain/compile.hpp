#ifndef _TALOS_TOOLCHAIN_COMPILE_HPP
#define _TALOS_TOOLCHAIN_COMPILE_HPP

/// Talos Modules
#include "talos/linker/arena.hpp"
#include "talos/syntax/tree.hpp"
#include "talos/variable/captures.hpp"

namespace Talos::Toolchain {

    /**
     * @brief Handles compiling a module.
     * @param syntax                Syntax tree.
     * @param captures              Captures to use.
     */
    $::Ptr::Unique<Linker::Arena> compile(const Syntax::Tree* syntax, const Variable::Captures* captures);

}  // namespace Talos::Toolchain

#endif
