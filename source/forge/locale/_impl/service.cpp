/// Forge Modules
#include "forge/locale/service.hpp"
#include "forge/runtime/options.hpp"

//  CONSTRUCTORS  //

Forge::Locale::Service::Service() : Service(&$::Global::get<Runtime::Options>()->locale) {}
Forge::Locale::Service::Service(XI::Container* services) : Service(&services->get<Runtime::Options>()->locale) {}
Forge::Locale::Service::Service(const Options* options) : m_options(options) {
    if (!m_options->initial) reset();
    else update(m_options->initial);
}
