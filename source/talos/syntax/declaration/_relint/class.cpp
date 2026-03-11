/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Header, node, analyzer) {
    analyzer->verify(node->constructor());
    analyzer->verify(node->super());
    analyzer->verify(node->implements());
}

TALOS_MM_LINT_NODE(Class, node, analyzer) {
    $_UNUSED $_AUTO = analyzer->scope();
    analyzer->verify(node->header(), node);
    analyzer->verify(node->fields(), node);
}
