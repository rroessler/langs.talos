/// Forge Modules
#include "forge/relint/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LINT_NODE(Alias, alias, analyzer) {
    analyzer->verify(alias->hint(), alias);
    analyzer->verify(alias->generics(), alias);
}
