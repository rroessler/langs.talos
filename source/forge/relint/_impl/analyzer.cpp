/// Forge Modules
#include "forge/relint/analyzer.hpp"
#include "forge/relint/visitor.hpp"
#include "forge/runtime/container.hpp"

//  CONSTRUCTORS  //

Forge::Relint::Analyzer::Analyzer() : Analyzer($::Global::get<Runtime::Container>()) {}
Forge::Relint::Analyzer::Analyzer(XI::Container* services) : Define(services) {}

//  PUBLIC METHODS  //

$::Ptr::Unique<Forge::Relint::Metadata> Forge::Relint::Analyzer::audit(
    const Syntax::Tree* tree, Diagnostic::Reporter* reporter) {
    // ensure that we are given a valid reporter to use
    if (reporter == nullptr) return $::New().unique<Metadata>();

    // we construct a new context instance
    $_UNUSED $_AUTO = m_context(tree, reporter);
    m_mirrors = $::New().unique<Metadata>();

    // then we verify and move the metadata result
    return verify(tree), std::move(m_mirrors);
}

Forge::Relint::Mirror* Forge::Relint::Analyzer::verify(const Syntax::Node* node, const Syntax::Node* parent) {
    // ignore if this node is invalid
    if ($_UNLIKELY(node == nullptr)) return nullptr;

    // pre-construct the incoming mirror to be used now
    auto* mirror = m_mirrors->resolve(node, parent);

    // attempt visiting the node in question
    Visitor::visit(node, this), traverse(node);

    // and resolve the resulting mirror now
    return m_finalize(mirror), mirror;
}

void Forge::Relint::Analyzer::traverse(const Syntax::Node* node) {
    // ignore if this node is invalid
    if ($_UNLIKELY(node == nullptr)) return;

    // get the incoming rules to be handled
    auto rules = m_hooks->m_resolve(node);

    // apply all available rules to the current node in question
    for (const auto& rule : rules) rule(node, this);
}

//  PRIVATE METHODS  //

void Forge::Relint::Analyzer::m_finalize(Mirror* mirror) {
    // get the underlying details of the mirror
    auto* origin = mirror->origin();
    auto* traits = origin->traits();

    // ignore if we do not have a declaration node
    if (!origin->is<Syntax::Declaration>()) return;

    // use the traits to get all documentation comments
    $_PP_IGNORE(traits);
}
