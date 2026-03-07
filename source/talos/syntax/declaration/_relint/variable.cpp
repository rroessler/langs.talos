/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Variable, variable, analyzer) {
    analyzer->verify(variable->hint(), variable);
    analyzer->verify(variable->initializer(), variable);
}
