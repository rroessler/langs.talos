/// Talos Includes
#include "talos/locale/service.hpp"
#include "talos/runtime/container.hpp"
#include "talos/runtime/options.hpp"

//  CONSTRUCTORS  //

Talos::Locale::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Talos::Locale::Service::Service(XI::Container *services) : Service(&services->get<Runtime::Options>()->locale) {}
Talos::Locale::Service::Service(const Options *options) : m_options(options) {
  if (!m_options->initial) reset();
  else update(m_options->initial);
}
