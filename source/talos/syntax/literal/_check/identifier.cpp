/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

/// Forward Declarations
$_FWD(Talos::Type::Dispatch, template <std::derived_from<Syntax::Node> T> Deduction identifier(Analyzer *, const T *))

//  PUBLIC METHODS  //

template <std::derived_from<Talos::Syntax::Node> T>
Talos::Type::Deduction Talos::Type::Dispatch::identifier(Analyzer *analyzer, const T *node) {
    // get the underlying node name
    auto name = node->name();

    // prepare tracing for the identifier now
    $_UNUSED $_AUTO = analyzer->trace(node);

    // attempt getting a type for the current identifier
    auto [entity, depth] = analyzer->world()->lookup(name);

    // declare an error if the variable does not exist or not a value
    if (entity == nullptr) return analyzer->report(4000301, name);
    if (!entity->opaque()) return analyzer->report(3000200, name);

    // mark the node if necessary to do so
    if constexpr (std::same_as<T, Syntax::Identifier>) analyzer->mark(node, entity, depth);

    // update the current entity as used and return the value
    return entity->value();
}

TALOS_MM_CHECK_NODE(Self, node, analyzer) { return Type::Dispatch::identifier(analyzer, node); }
TALOS_MM_CHECK_NODE(Identifier, node, analyzer) { return Type::Dispatch::identifier(analyzer, node); }
