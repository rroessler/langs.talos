/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

/// Forward Declarations
$_FWD(Talos::Type::Dispatch, Algorithm* fields(const Erased&))
$_FWD(Talos::Type::Dispatch, Deduction attribute(Analyzer*, const Erased&, const Syntax::Operator*))

//  PUBLIC METHODS  //

Talos::Type::Algorithm* Talos::Type::Dispatch::fields(const Erased& type) {
    if (type->is<Instance>()) return &type->as<Instance>()->prototype()->fields();
    return type->is<Protocol>() ? &type->as<Protocol>()->fields() : nullptr;
}

Talos::Type::Deduction Talos::Type::Dispatch::attribute(
    Analyzer* analyzer, const Erased& type, const Syntax::Operator* attribute) {
    switch (attribute->kind()) {
        // disposables expect any empty function (eg: fn -> Void).
        case Operator::Kind::DISP: {
            static Erased s_expected = Builder::function();  // prepare
            if (s_expected->unify(type)) return analyzer->passable(type);
            return analyzer->report(attribute->target(), 3000802, attribute->label(), *s_expected, *type);
        }

        // declare all other attempts as invalid currently
        default: return analyzer->report(3000804, *type);
    }
}

TALOS_MM_CHECK_NODE(Operator, node, analyzer) {
    // get the current preamble target to be validated
    auto* entity = analyzer->world()->preamble();

    // set the current trace handler
    $_UNUSED $_AUTO = analyzer->trace(node);

    // we want to check the incoming "self" value
    auto self = analyzer->check(node->target());
    auto* fields = Type::Dispatch::fields(self.type);

    // check if we have a valid instance (eg: must have fields)
    if (fields == nullptr) return analyzer->report(3000803, *self.type, node->label());

    // to which we can then update the necessary lookup now
    auto valid = fields->emplace(node->symbol(), entity->value());
    if (!valid) return analyzer->report(6000303, node->label(), *self.type);

    // attempt validing the incoming operator now
    return Type::Dispatch::attribute(analyzer, entity->value(), node);
}
