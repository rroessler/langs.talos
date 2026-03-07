/// Talos Modules
#include "talos/forward/shape.hpp"
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

/// Forward Declarations
$_FWD(Erased check(Syntax::Expression*, Analyzer*, const Erased&, Diagnostic::Code), Talos::Type::Dispatch)

//  PUBLIC METHODS  //

Talos::Type::Erased Talos::Type::Dispatch::check(
    Syntax::Expression* expression, Analyzer* analyzer, const Erased& expected, Diagnostic::Code code) {
    // always default if the expression is missing
    if (expression == nullptr) return expected;

    // otherwise attempt getting the inferred typing
    auto inferred = analyzer->check(expression).type;

    // check that our inferred type is assignable to the expression
    if (expected->unify(inferred)) return expected;

    // otherwise report and return base details
    return analyzer->report(expression, code, *inferred, *expected), expected;
}

TALOS_MM_CHECK_NODE(Enum, node, analyzer) {
    // start tracing this now now
    $_UNUSED $_AUTO = analyzer->trace(node);

    // prepare some underlying details about the node
    auto name = node->name();

    // prepare the underlying variants that have been found
    auto variants = $::Record<Type::Entity>();

    // assign a new shape instance now
    auto shape = analyzer->shapes()->assign(node);

    // prepare the enumeration value
    auto enumeration = Type::Builder::enumeration(name, shape);

    // iterate over the available enumeration choices
    for (const auto& variant : node->variants()) {
        auto emplaced = variants.try_emplace(variant->key(), enumeration).second;  // emplace now
        emplaced ? analyzer->check(variant) : analyzer->report(variant, 4000405, variant->key());
    }

    auto accessor = Type::Builder::interface(name, variants);  // prepare custom accessor
    auto* entity = analyzer->world()->values().declare(node, accessor, analyzer->captures());

    if (entity == nullptr) return analyzer->report(4000403, name);    // already exists so fail
    if (entity->transient()) return analyzer->report(4000402, name);  // exists in type-land

    // update the underlying type to be used now
    return analyzer->passable(entity->type() = enumeration);
}

TALOS_MM_CHECK_NODE(Variant, node, analyzer) {
    // trace this node now
    $_UNUSED $_AUTO = analyzer->trace(node);

    // check the label if we have been given one at all
    Type::Dispatch::check(node->label(), analyzer, Type::Builder::string(), 3000303);

    // otherwise the core check is the incoming
    return Type::Dispatch::check(node->value(), analyzer, Type::Builder::number(), 3000302);
}
