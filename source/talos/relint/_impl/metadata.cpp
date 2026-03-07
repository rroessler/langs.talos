/// Talos Modules
#include "talos/relint/metadata.hpp"

//  PUBLIC METHODS  //

bool Talos::Relint::Metadata::bound(const Syntax::Node* origin) const { return m_mirrors.contains(origin); }

const Talos::Relint::Mirror* Talos::Relint::Metadata::resolve(const Syntax::Node* origin) const {
    auto mirror = m_mirrors.find(origin);  // safe resolution
    return mirror == m_mirrors.end() ? nullptr : mirror->second.get();
}

Talos::Relint::Mirror* Talos::Relint::Metadata::resolve(const Syntax::Node* origin, const Syntax::Node* parent) {
    auto iter = m_mirrors.find(origin);  // pre-scan here
    if (iter != m_mirrors.end()) return iter->second.get();

    // emplace the origin into the heap queue and then also the mirrors.
    m_sorted.emplace_back(origin), std::ranges::sort(m_sorted, Syntax::Comparator());
    return m_mirrors.emplace(origin, m_create(origin, parent)).first->second.get();
}

const Talos::Relint::Mirror* Talos::Relint::Metadata::search(const XLSP::Position& position) const noexcept {
    // prepare a predicate that uses the incoming position
    auto predicate = [position](const Syntax::Node* node) {
        // ensure we ignore some nodes (since we want internal values)
        switch (node->traits()->tag()) {
            case $::RTTI::Hash<Syntax::Block>(): return false;
            case $::RTTI::Hash<Syntax::Ternary>(): return false;
            default: return node->traits()->range().contains(position);
        }
    };

    // attempt searching for a suitable range now
    auto iter = std::ranges::find_if(m_sorted, predicate);

    // and return the resulting mirror as necessary
    return iter == m_sorted.end() ? nullptr : resolve(*iter);
}

//  PRIVATE METHODS  //

$::Ptr::Unique<Talos::Relint::Mirror> Talos::Relint::Metadata::m_create(
    const Syntax::Node* origin, const Syntax::Node* parent) const noexcept {
    if (parent == nullptr) return $::New().unique<Mirror>(origin);
    else return $::New().unique<Mirror>(origin, resolve(parent));
}
