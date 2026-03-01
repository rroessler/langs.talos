#ifndef _FORGE_TOOLCHAIN_AUDIT_HPP
#define _FORGE_TOOLCHAIN_AUDIT_HPP

/// Forge Modules
#include "forge/diagnostic/reporter.hpp"
#include "forge/syntax/tree.hpp"
#include "forge/type/options.hpp"

namespace Forge::Toolchain {

    /**
     * @brief Handles analyzing a syntax-tree.
     * @param syntax                Syntax tree.
     * @param options               Type options.
     */
    $::Ptr::Unique<Type::Context> audit(const Syntax::Tree* syntax, const Type::Options& options = {});

}  // namespace Forge::Toolchain

#endif
