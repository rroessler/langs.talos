/// Vendor Includes
#include <boost/locale.hpp>

/// Talos Includes
#include "talos/locale/generator.hpp"

//  CONSTRUCTORS  //

Talos::Locale::Generator::Generator() : m_context(new boost::locale::generator()) {}
Talos::Locale::Generator::~Generator() { delete static_cast<boost::locale::generator *>(m_context); }

//  PRIVATE METHODS  //

std::locale Talos::Locale::Generator::m_bind(const std::locale &locale, const $::String::Buffer &id) const noexcept {
  return static_cast<boost::locale::generator *>(m_context)->generate(locale, id);
}
