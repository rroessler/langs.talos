/// Forge Modules
#include "forge/relint/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LINT_NODE(Variable, variable, analyzer) {
    analyzer->verify(variable->hint(), variable);
    analyzer->verify(variable->initializer(), variable);
}
