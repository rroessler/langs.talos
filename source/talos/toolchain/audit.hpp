#ifndef _TALOS_TOOLCHAIN_AUDIT_HPP
#define _TALOS_TOOLCHAIN_AUDIT_HPP

/// Talos Includes
#include "talos/diagnostic/reporter.hpp"
#include "talos/relint/exports.hpp"
#include "talos/syntax/tree.hpp"
#include "talos/type/exports.hpp"

namespace Talos::Toolchain {

/**
 * @brief Handles analyzing a syntax-tree.
 * @param syntax                Syntax tree.
 * @param services              Services container.
 * @param reporter              Diagnostic reporter.
 */
$::Unique::Pointer<Type::Exports>
audit(const Syntax::Tree *syntax, XI::Container *services, Diagnostic::Reporter *reporter);

/**
 * @brief Handles linting a syntax-tree.
 * @param syntax                Syntax tree.
 * @param services              Services container.
 * @param reporter              Diagnostic reporter.
 */
$::Unique::Pointer<Relint::Exports>
lint(const Syntax::Tree *syntax, XI::Container *services, Diagnostic::Reporter *reporter);

} // namespace Talos::Toolchain

#endif
