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
    return search(position, [](const Syntax::Node* node) -> bool {
        // ensure we ignore some nodes (since we want internal values)
        switch (node->traits()->tag()) {
            case $::RTTI::Hash<Syntax::Block>(): return false;
            case $::RTTI::Hash<Syntax::Ternary>(): return false;
            default: return true;  // valid target for searching
        }
    });
}

const Talos::Relint::Mirror* Talos::Relint::Metadata::search(
    const XLSP::Position& position, Filter&& filter) const noexcept {
    // if the filter is invalid, then request the baseline details
    if (filter == nullptr) return search(position);

    // attempt finding a suitable candidate to be used
    for (const auto* node : m_sorted) {
        if (filter(node) && node->traits()->range().contains(position)) return resolve(node);
    }

    // otherwise we failed to find a candidate
    return nullptr;
}

//  PRIVATE METHODS  //

$::Ptr::Unique<Talos::Relint::Mirror> Talos::Relint::Metadata::m_create(
    const Syntax::Node* origin, const Syntax::Node* parent) const noexcept {
    if (parent == nullptr) return $::New().unique<Mirror>(origin);
    else return $::New().unique<Mirror>(origin, resolve(parent));
}
