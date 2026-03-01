/// Forge Modules
#include "forge/type/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/annotation.ipp"

//  PUBLIC METHODS  //

FORGE_MM_CHECK_NODE(Interface, node, analyzer) {
    // get the underlying record elements
    const auto& properties = node->properties();

    // stop early if they are empty
    if (properties.empty()) return { Type::Builder::object() };

    // prepare the fields to be bound now
    auto fields = $::Record<Type::Entity>();

    // convert all our values as necessary now
    for (const auto* variable : properties) {
        auto name = variable->name();
        auto expected = analyzer->declare(variable);

        // ensure incoming variables are not disposable
        if (variable->disposable()) analyzer->report(variable, 3000151, name);

        if (!fields.contains(name)) fields.emplace(name, expected);
        else analyzer->report(variable, 4000404, name);  // invalid
    }

    // construct the resulting record to be used
    return { Type::Builder::interface(fields) };
}
