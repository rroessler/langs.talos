/// Forge Modules
#include "forge/type/analyzer.hpp"

//  CONSTRUCTORS  //

Forge::Type::Scope::Scope(Analyzer* analyzer) : World(analyzer->m_world), m_analyzer(analyzer) {
    m_analyzer->m_world = this;  // cache the current world reference now
}

Forge::Type::Scope::~Scope() {
    // prepare all the deferred callbacks to be run
    for (const auto& callback : m_deferred) callback(m_analyzer);

    // ensure we report any errors relating to unused variables
    for (const auto& [name, entity] : m_entities) {
        if (!entity.unused() || name.starts_with('_')) continue;
        m_analyzer->report(m_locations.at(name), 4000901, name);
    }

    // resolve the current world instance to be used
    m_analyzer->m_world = m_parent;
}
