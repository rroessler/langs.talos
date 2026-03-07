#ifndef _TALOS_TOOLCHAIN_AUDIT_HPP
#define _TALOS_TOOLCHAIN_AUDIT_HPP

/// Talos Modules
#include "talos/diagnostic/reporter.hpp"
#include "talos/syntax/tree.hpp"
#include "talos/type/options.hpp"

namespace Talos::Toolchain {

    /**
     * @brief Handles analyzing a syntax-tree.
     * @param syntax                Syntax tree.
     * @param options               Type options.
     */
    $::Ptr::Unique<Type::Context> audit(const Syntax::Tree* syntax, const Type::Options& options = {});

}  // namespace Talos::Toolchain

#endif
