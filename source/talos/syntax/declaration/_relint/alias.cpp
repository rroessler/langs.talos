/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Alias, alias, analyzer) {
    analyzer->verify(alias->hint(), alias);
    analyzer->verify(alias->generics(), alias);
}
