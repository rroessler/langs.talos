/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Operator, attribute, analyzer) {
    // get the current preamble target to be validated
    auto* _ = analyzer->world()->preamble();

    // set the current trace handler
    $_UNUSED $_AUTO = analyzer->trace(attribute);

    // we want to validate the incoming "self" value
    auto _ = analyzer->check(attribute->target()).type;

    // declare as passable now
    return analyzer->passable();
}
