/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/annotation.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Placeholder, node, analyzer) {
    // get some base analyzer details
    auto* mirrors = analyzer->mirrors();
    auto* references = analyzer->references();

    // bind the suitable annotation definition
    auto* self = mirrors->resolve(node);
    references->annotate(node->name(), self);

    // and finally update all the details for the placeholder
    analyzer->verify(node->extends(), node);
    analyzer->verify(node->fallback(), node);
}
