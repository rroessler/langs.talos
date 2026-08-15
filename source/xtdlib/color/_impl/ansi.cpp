/// Library Includes
#include "xtdlib/color/ansi.hpp"
#include "xtdlib/color/enabled.hpp"

$_FWD($::Escape, String::Buffer stringify(uint8_t))
$_FWD($::Escape, String::Buffer stringify(uint8_t, uint8_t))
$_FWD($::Escape, String::Buffer merge(const String::Buffer &, const String::View &))
$_FWD($::Escape, template <class... A> String::Buffer merge(const String::Buffer &, const String::View &, A &&...))

//  PUBLIC METHODS  //

$::String::Buffer $::Escape::stringify(uint8_t value) { return value == UINT8_MAX ? "" : fmt::to_string(value); }
$::String::Buffer $::Escape::stringify(uint8_t offset, uint8_t value) {
  return value == UINT8_MAX ? "" : fmt::to_string(offset + value);
}

$::String::Buffer $::Escape::merge(const String::Buffer &prefix, const String::View &suffix) {
  return prefix + (prefix.empty() || suffix.empty() ? "" : ";") + String::Buffer(suffix);
}

template <class... As>
$::String::Buffer $::Escape::merge(const String::Buffer &prefix, const String::View &suffix, As &&...rest) {
  return merge(merge(prefix, suffix), std::forward<As>(rest)...);
}

//  PRIVATE METHODS  //

void $::Color::ANSI::m_print(std::ostream &os, const ANSI &self) {
  // get the current pretty enablement to be used
  if (!Enabled(os)) return void(os << self.m_value);

  // prepare the necessary buffers to be used
  auto style = Escape::stringify(self.m_style);
  auto foreground = Escape::stringify(30, self.m_foreground);
  auto background = Escape::stringify(40, self.m_background);

  // construct the resulting buffer now
  auto buffer = $::Escape::merge(style, foreground, background);

  // if the buffer is empty, then stop early
  if (buffer.empty()) return void(os << self.m_value);

  // otherwise format altogether now
  os << "\033[" << buffer << 'm' << self.m_value << "\033[0m";
}
