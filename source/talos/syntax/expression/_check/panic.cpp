/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Panic, panic, analyzer) {
    // push the necessary traces for analyzing
    $_UNUSED $_AUTO = analyzer->trace(panic);

    // forcibly check the incoming value to be used now
    analyzer->check(panic->value());

    // // check for validness against potential types
    // auto valid = result.type->is<Type::Any, Type::None>();

    // // ensure the result is valid for exceptions
    // if (!valid) analyzer->report(3000950, *result.type);

    // and declare as currently reachable now
    return analyzer->unreachable();
}
