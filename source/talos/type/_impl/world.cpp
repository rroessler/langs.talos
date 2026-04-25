/// Talos Modules
#include "talos/type/analyzer.hpp"

//  CONSTRUCTORS  //

Talos::Type::Scope::Scope(Analyzer* analyzer) : World(analyzer->m_world), m_analyzer(analyzer) {
    m_analyzer->m_world = this;  // cache the current world reference now
}

Talos::Type::Scope::~Scope() {
    // prepare all the deferred callbacks to be run
    for (const auto& callback : m_deferred) callback(m_analyzer);

    // ensure we report any errors relating to unused variables
    for (const auto& [name, entity] : m_entities) {
        // resolve the underlying location of the entity
        auto location = m_locations.at(name);

        // check whether we should actually report the instance
        if (!entity.unused() || name.starts_with('_') || location.anonymous()) continue;

        // if unused, then we declare as such to the reporter
        m_analyzer->report(location, entity.transient() ? 4000901 : 4000902, name);
    }

    // resolve the current world instance to be used
    m_analyzer->m_world = m_parent;
}

//  PRIVATE METHODS  //

Talos::Variable::Captures* Talos::Type::Scope::m_captures() const noexcept { return &m_analyzer->captures(); }