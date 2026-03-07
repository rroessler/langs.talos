/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Class, node, analyzer) {
    analyzer->verify(node->extends(), node);
    analyzer->verify(node->implements(), node);
    analyzer->verify(node->constructor(), node);

    $_UNUSED $_AUTO = analyzer->scope();
    analyzer->verify(node->fields(), node);
}
