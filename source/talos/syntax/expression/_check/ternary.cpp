/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Ternary, ternary, analyzer) {
    // trace from the ternary node
    $_UNUSED $_AUTO = analyzer->trace(ternary);

    auto deduction = analyzer->check(ternary->condition());
    auto truthiness = deduction.type->truthiness();

    // validate the consequence and alternative values now
    auto consequence = analyzer->check(ternary->consequence());
    auto alternative = analyzer->check(ternary->alternative());

    // stop early if the condition was not passable
    if (deduction.flow->unreachable()) return deduction;

    // handle branching our details based on the truthiness
    if (truthiness == true) return consequence;
    if (truthiness == false) return alternative;

    // otherwise we want to merge the results somehow
    return Type::Builder::merge(consequence.type, alternative.type);
}
