/// Forge Modules
#include "forge/type/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

FORGE_MM_CHECK_NODE(Variable, variable, analyzer) {
    // prepare the base variable report to be used
    $_UNUSED $_AUTO = analyzer->trace(variable);

    // get the incoming expected typing
    auto expected = analyzer->declare(variable);

    // show an error for disposable variables that are exported
    auto exported = variable->modifiers().test(Variable::Flag::EXPORT);
    if (exported && variable->disposable()) analyzer->report(3000150);

    // attempt declaring on the world now
    auto* entity = analyzer->world()->values().declare(variable, expected, analyzer->captures());
    return entity ? analyzer->passable(expected) : analyzer->report(4000403, variable->name());
}
