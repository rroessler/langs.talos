/// Forge Modules
#include "forge/relint/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/annotation.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LINT_NODE(Qualifier, qualifier, analyzer) { analyzer->verify(qualifier->segments(), qualifier); }
