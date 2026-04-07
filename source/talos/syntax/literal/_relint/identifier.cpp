/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Self, node, analyzer) {
    auto* self = analyzer->mirrors()->resolve(node);
    analyzer->references()->capture(node->name(), self);
}

TALOS_MM_LINT_NODE(Identifier, node, analyzer) {
    auto* self = analyzer->mirrors()->resolve(node);
    analyzer->references()->capture(node->name(), self);
}
