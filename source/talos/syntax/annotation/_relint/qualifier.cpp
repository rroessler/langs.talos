/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/annotation.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Qualifier, node, analyzer) {
    // prepare the metadata and references
    auto* mirrors = analyzer->mirrors();
    auto* references = analyzer->references();

    // prepare the segments to be handled
    auto* self = mirrors->resolve(node);
    const auto& segments = node->segments();

    // start by getting the front-most segment
    auto* identifier = segments.front();

    // and the front-most mirror/definition for us to process
    auto* current = mirrors->resolve(identifier, node);
    auto definition = references->resolve(identifier->name());

    // we should always bind both definitions to the base items
    references->relate(self, definition);

    // for the initial value, we always bind a variable relation
    references->relate(current, definition);

    // we want to iterate through the segments now to resolve chained items
    for (size_t ii = 1; ii < segments.size(); ++ii) {
        // get the next identifier value to be used
        identifier = segments.at(ii);

        // attempt finding a suitable definition
        definition = current->lookup(identifier->name());

        // post-resolve the mirror for the identifier
        current = mirrors->resolve(identifier, node);

        // and bind the current variable definition
        references->relate(current, definition);
    }
}
