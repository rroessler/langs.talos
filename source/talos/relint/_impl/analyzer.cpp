/// Talos Modules
#include "talos/relint/analyzer.hpp"
#include "talos/module/service.hpp"
#include "talos/relint/visitor.hpp"
#include "talos/runtime/container.hpp"
#include "talos/type/metadata.hpp"

//  CONSTRUCTORS  //

Talos::Relint::Analyzer::Analyzer() : Analyzer($::Global::get<Runtime::Container>()) {}
Talos::Relint::Analyzer::Analyzer(XI::Container* services) : Define(services) {}

//  PUBLIC METHODS  //

$::Ptr::Unique<Talos::Relint::Metadata> Talos::Relint::Analyzer::audit(
    const Syntax::Tree* tree, Diagnostic::Reporter* reporter) {
    // ensure that we are given a valid reporter to use
    if (reporter == nullptr) return $::New().unique<Metadata>();

    // we construct a new context instance
    $_UNUSED $_AUTO = m_context(tree, reporter);
    m_mirrors = $::New().unique<Metadata>();
    m_scope = m_mirrors->m_references.get();

    // then we verify and move the metadata result
    return verify(tree), m_scope = nullptr, std::move(m_mirrors);
}

Talos::Relint::Mirror* Talos::Relint::Analyzer::verify(
    const Syntax::Node* node, const Syntax::Node* parent, bool visit) {
    // ignore if this node is invalid
    if ($_UNLIKELY(node == nullptr)) return nullptr;

    // pre-construct the incoming mirror to be used now
    auto* mirror = m_mirrors->resolve(node, parent);

    // attempt visiting the node in question
    if (visit) Visitor::visit(node, this);

    // and resolve the resulting mirror now
    return traverse(node), m_finalize(mirror), mirror;
}

void Talos::Relint::Analyzer::traverse(const Syntax::Node* node) {
    // ignore if this node is invalid
    if ($_UNLIKELY(node == nullptr)) return;

    // get the incoming rules to be handled
    auto rules = m_hooks->m_resolve(node);

    // apply all available rules to the current node in question
    for (const auto& rule : rules) rule(node, this);
}

const Talos::Relint::Scope* Talos::Relint::Analyzer::import(const $::String::View& path) {
    Import::Service* modules = *m_services;  // resolve now
    auto result = modules->resolve(path, resource().body());
    return result.has_value() ? import(*result) : nullptr;
}

const Talos::Relint::Scope* Talos::Relint::Analyzer::import(const $::URI::View& resource) {
    Import::Service* modules = *m_services;
    auto* found = modules->fetch(resource);
    if (found == nullptr) return nullptr;

    // always forcibly analyze the module
    found->analyze(m_services);

    // then we can safely resolve the metadata now
    auto* metadata = found->metadata<Module::Phase::TYPED>();
    return metadata->context()->mirrors()->references();
}

//  PRIVATE METHODS  //

void Talos::Relint::Analyzer::m_finalize(Mirror* mirror) {
    // get the underlying details of the mirror
    auto* origin = mirror->origin();
    auto* traits = origin->traits();

    // if the symbol is suitably valid, then we append to the lsit
    if (auto symbol = m_classify(mirror)) m_mirrors->m_symbols.emplace_back(symbol);

    // ignore if we do not have a declaration node
    if (!origin->is<Syntax::Declaration>()) return;

    /// TODO: use the traits to get all documentation comments
    $_PP_IGNORE(traits);
}

XLSP::Symbol Talos::Relint::Analyzer::m_classify(const Mirror* mirror) const {
    switch (auto* origin = mirror->origin(); origin->traits()->tag()) {
        // aliases can simply be resolved as needed
        case $::RTTI::Hash<Syntax::Alias>(): {
            auto name = origin->as<Syntax::Alias>()->name();
            return { name, XLSP::Symbol::Kind::INTERFACE };
        }

        // enums can simply be resolved as needed
        case $::RTTI::Hash<Syntax::Enum>(): {
            auto name = origin->as<Syntax::Enum>()->name();
            return { name, XLSP::Symbol::Kind::ENUM };
        }

        // classes can simply be resolved as needed
        case $::RTTI::Hash<Syntax::Class>(): {
            auto name = origin->as<Syntax::Class>()->name();
            return { name, XLSP::Symbol::Kind::CLASS };
        }

        // variables can simply be resolved as needed
        case $::RTTI::Hash<Syntax::Variable>(): {
            auto name = origin->as<Syntax::Variable>()->name();
            return { name, XLSP::Symbol::Kind::VARIABLE };
        }

        // namespaces can simply be resolved as needed
        case $::RTTI::Hash<Syntax::Namespace>(): {
            auto name = origin->as<Syntax::Declaration>()->name();
            return { name, XLSP::Symbol::Kind::NAMESPACE };
        }

        // in the default case, return an unknown symbol
        default: return XLSP::Symbol();
    }
}
