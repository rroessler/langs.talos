/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Operator, attribute, analyzer) {
    // prepare the baseline function
    static auto s_expected = Type::Builder::variadic();

    // get the current preamble target to be validated
    auto* entity = analyzer->world()->preamble();

    // set the current trace handler
    $_UNUSED $_AUTO = analyzer->trace(attribute);

    // we want to validate the incoming "self" value
    auto _ = analyzer->check(attribute->target()).type;

    // ensure the incoming entity is valid
    auto valid = s_expected->unify(entity->value());
    if (valid) return analyzer->passable(entity->value());
    return analyzer->report(3000802, *entity->value());
}
