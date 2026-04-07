/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Variable, node, analyzer) {
    // get some base analyzer details
    auto* mirrors = analyzer->mirrors();
    auto* references = analyzer->references();

    // bind this mirror as a suitable definition
    auto* self = mirrors->resolve(node);
    references->declare(node->name(), self);

    // bind the incoming details for the variable
    analyzer->verify(node->hint(), node);
    analyzer->verify(node->initializer(), node);
}
