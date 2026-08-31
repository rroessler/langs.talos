/// Vendor Includes
#include <boost/locale.hpp>

/// Talos Includes
#include "talos/locale/service.hpp"
#include "talos/runtime/container.hpp"
#include "talos/runtime/options.hpp"

//  MACROS  //

#define MM_ASSERT(L, ...) $_ASSERT(std::has_facet<boost::locale::info>(L), __VA_ARGS__)

//  CONSTRUCTORS  //

Talos::Locale::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Talos::Locale::Service::Service(XI::Container *services) : Service(&services->get<Runtime::Options>()->locale) {}
Talos::Locale::Service::Service(const Options *options) : m_options(options) {
  if (m_options->initial.empty()) reset();
  else change(m_options->initial);
}

//  PRIVATE METHODS  //

$::String::Buffer Talos::Locale::Service::m_lower(const $::String::View &input, const std::locale &locale) const {
  MM_ASSERT(locale, "Expected a valid locale constructed by boost::locale::generator");
  return boost::locale::to_lower(input.data(), input.data() + input.size(), locale);
}

$::String::Buffer Talos::Locale::Service::m_upper(const $::String::View &input, const std::locale &locale) const {
  MM_ASSERT(locale, "Expected a valid locale constructed by boost::locale::generator");
  return boost::locale::to_upper(input.data(), input.data() + input.size(), locale);
}

int64_t Talos::Locale::Service::m_compare(
    const $::String::View &left, const $::String::View &right, const std::locale &locale
) const {
  const auto &collate = std::use_facet<std::collate<char>>(locale); // prepare the collator to be used
  return collate.compare(left.data(), left.data() + left.size(), right.data(), right.data() + right.size());
}
