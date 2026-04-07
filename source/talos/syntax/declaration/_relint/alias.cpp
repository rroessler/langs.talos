/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Alias, node, analyzer) {
    // get some base analyzer details
    auto* mirrors = analyzer->mirrors();
    auto* references = analyzer->references();

    // bind the suitable annotation definition
    auto* self = mirrors->resolve(node);
    references->annotate(node->name(), self);

    // and finally update all the details for the alias
    analyzer->verify(node->hint(), node);
    analyzer->verify(node->generics(), node);
}
