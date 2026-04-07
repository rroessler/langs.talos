/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/annotation.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Placeholder, node, analyzer) {
    analyzer->verify(node->extends(), node);
    analyzer->verify(node->fallback(), node);
}
