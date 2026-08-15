/// Talos Includes
#include "talos/toolchain/audit.hpp"
#include "talos/relint/analyzer.hpp"
#include "talos/type/analyzer.hpp"

//  PUBLIC METHODS  //

$::Unique::Pointer<Talos::Type::Exports>
Talos::Toolchain::audit(const Syntax::Tree *syntax, XI::Container *services, Diagnostic::Reporter *reporter) {
  return services->get<Type::Analyzer>()->audit(syntax, reporter);
}

$::Unique::Pointer<Talos::Relint::Exports>
Talos::Toolchain::lint(const Syntax::Tree *syntax, XI::Container *services, Diagnostic::Reporter *reporter) {
  return services->get<Relint::Analyzer>()->audit(syntax, reporter);
}
