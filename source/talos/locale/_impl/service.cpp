/// Vendor Includes
#include <boost/locale.hpp>

/// Talos Includes
#include "talos/locale/service.hpp"
#include "talos/runtime/container.hpp"
#include "talos/runtime/options.hpp"

//  CONSTRUCTORS  //

Talos::Locale::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Talos::Locale::Service::Service(XI::Container *services) : Service(&services->get<Runtime::Options>()->locale) {}
Talos::Locale::Service::Service(const Options *options) : m_options(options) {
  if (m_options->initial.empty()) reset();
  else change(m_options->initial);
}

//  PRIVATE METHODS  //

$::String::Buffer
Talos::Locale::Service::m_lower(const $::String::View &input, const std::locale &locale) const noexcept {
  return boost::locale::to_lower(input.data(), input.data() + input.size(), locale);
}

$::String::Buffer
Talos::Locale::Service::m_upper(const $::String::View &input, const std::locale &locale) const noexcept {
  return boost::locale::to_upper(input.data(), input.data() + input.size(), locale);
}
