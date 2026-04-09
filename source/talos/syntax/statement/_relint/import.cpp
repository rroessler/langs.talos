/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/statement.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Import, node, analyzer) {
    auto* module = analyzer->import(node->path());
    if (module == nullptr) return;  // failed here

    // prepare the available references now
    auto* references = analyzer->references();

    // check if we have a wildcard entry at all
    auto wildcard = node->wildcard();

    // resolve the import patterns to be referenced
    for (const auto* pattern : node->patterns()) {
        // ensure we construct the base mirror to be used
        auto* mirror = analyzer->verify(pattern, node, false);

        // always declare the current pattern instance
        if (wildcard) {
            references->declare(pattern->name(), mirror);
            mirror->fields() = module->view();  // fields
        }

        // otherwise we want to resolve the original definition
        else {
            auto definition = module->resolve(pattern->name());
            references->relate(mirror, definition);  // relate
            references->overwrite(pattern->name(), definition);
        }
    }

    // check if we have any barrel exports that need to be handled
    if (!node->exported() || node->patterns().size()) return;

    /**
     * TODO: We should be appending barrel imports/exports (eg: export "..."), however due to VSC opening/closing
     * files anytime references/definitions are requested (for the mini preview), it causes syncing issues. This
     * is currently untenable with the linting setup we have now. If we are midway through resolving definitions
     * when a refresh occurs, then we need to cancel our request somehow ???
     */

    // this appears to work well enough for now, but again we should properly work out the de-sync problems
    for (const auto& [name, definition] : module->view()) references->overwrite(name, definition);
}
