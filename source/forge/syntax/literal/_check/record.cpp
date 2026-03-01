/// Forge Modules
#include "forge/type/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_CHECK_NODE(Record, record, analyzer) {
    // get the underlying record elements
    const auto& elements = record->elements();

    // stop early if they are empty
    if (elements.empty()) return { Type::Builder::interface() };

    // begin tracing for errors here now
    $_UNUSED $_AUTO = analyzer->trace(record);

    // prepare the fields to be bound now
    auto fields = $::Record<Type::Entity>();

    // convert all our values as necessary now
    for (const auto* variable : elements) {
        // prepare the name to be used
        auto name = variable->name();

        // construct the incoming expected entity now
        Type::Entity expected = analyzer->declare(variable);

        // update some values that are required
        expected.modifiers() = variable->modifiers();
        variable->traits()->type() = expected.value();

        // ensure incoming variables are not disposable
        if (variable->disposable()) analyzer->report(variable, 3000151, name);

        if (!fields.contains(name)) fields.emplace(name, expected);
        else analyzer->report(variable, 4000404, name);  // failure
    }

    // construct the resulting record to be used
    return { Type::Builder::interface(fields) };
}
