/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Decorator, decorator, analyzer) {
    // get the current preamble target to be validated
    auto target = analyzer->world()->preamble()->value();

    // set the current trace handler
    $_UNUSED $_AUTO = analyzer->trace(decorator);

    // we want to check the incoming "decorator" value
    auto candidate = analyzer->check(decorator->expression()).type;

    // prepare a baseline decorator callback that we expect
    auto args = Type::Builder::arguments(target);
    auto callback = Type::Builder::function(target, args);

    // ensure that the incoming decorator safely type-checks
    if (callback->unify(candidate)) return analyzer->passable();

    // otherwise we have an invalid decorator context to be applied
    else return analyzer->report(3000850, *candidate);
}
