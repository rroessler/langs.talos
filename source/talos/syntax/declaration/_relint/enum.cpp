/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Enum, node, analyzer) {
    // get some base analyzer details
    auto* mirrors = analyzer->mirrors();
    auto* references = analyzer->references();

    // bind this mirror as a suitable definition
    auto* self = mirrors->resolve(node);

    // get the fields that we will update
    auto& fields = self->fields();

    // bind both the value and type definitions
    references->declare(node->name(), self);
    references->annotate(node->name(), self);

    // bind the incoming details for the enumeration
    for (const auto* field : node->variants()) {
        auto* variant = analyzer->verify(field, node);
        references->declare(field->key(), variant);
        auto definition = references->resolve(field->key());
        fields.emplace(field->key(), definition);
    }
}

TALOS_MM_LINT_NODE(Variant, node, analyzer) {
    analyzer->verify(node->label(), node);
    analyzer->verify(node->value(), node);
}
