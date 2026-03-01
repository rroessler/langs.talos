/// Forge Modules
#include "forge/relint/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/annotation.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LINT_NODE(Placeholder, placeholder, analyzer) {
    analyzer->verify(placeholder->extends(), placeholder);
    analyzer->verify(placeholder->fallback(), placeholder);
}
