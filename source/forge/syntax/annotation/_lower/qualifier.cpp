/// Forge Modules
#include "forge/bytecode/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/annotation.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LOWER_NODE(Qualifier, qualifier, compiler, destination) {
    // get the incoming segments to be handled
    const auto& segments = qualifier->segments();

    // if the destination is nowhere, then we ignore
    if (segments.empty() || destination.nowhere()) return;

    // attempt loading in the qualifier segment by segment
    auto* identifier = segments.front();
    auto treg = compiler->registers()->temporary();

    // load the initial identifier as a normal value
    compiler->lower(identifier, destination);

    // iterate through the available fields now
    for (size_t ii = 1; ii < segments.size(); ++ii) {
        auto index = compiler->symbol(segments.at(ii)->name());  // load next
        compiler->emit<Syllable::LOAD_FIELD>(destination, destination, index);
    }
}
