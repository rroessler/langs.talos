/// Talos Includes
#include "talos/relint/options.hpp"
#include "talos/diagnostic/inspect.hpp"

/// Forward Declarations
$_FWD(Talos::Relint::Decode, void overrides(Options &))
$_FWD(Talos::Relint::Decode, std::optional<Severity> severity(const $::Serde::Value &))
$_FWD(Talos::Relint::Decode, std::optional<Diagnostic::Code> diagnostic(const $::String::Buffer &))
$_FWD(Talos::Relint::Decode, template <class K> $::Map::Base<K, Severity> object(const $::Serde::Object &))

//  PROPERTIES  //

#define TALOS_XX_RELINT_ALIAS(N, C, ...) {N, C},
static $::Map::Dict<Talos::Diagnostic::Code> g_aliases = {
#include "talos/relint/_defines/aliases.def"
};

//  PUBLIC METHODS  //

void Talos::Relint::Decode::overrides(Options &options) {
  for (const auto &[identifier, code] : g_aliases) {
    if (!options.rules.contains(identifier)) continue; // not found
    options.overrides.try_emplace(code, options.rules.at(identifier));
  }
}

std::optional<Talos::Diagnostic::Code> Talos::Relint::Decode::diagnostic(const $::String::Buffer &buffer) {
  size_t index = 0; // we use a localized index for conversion
  std::optional<Diagnostic::Code> result = std::stoi(buffer, &index);
  if (index != buffer.size()) return std::nullopt; // failed to parse
  return Diagnostic::Inspect::overridable(*result) ? result : std::nullopt;
}

std::optional<Talos::Relint::Severity> Talos::Relint::Decode::severity(const $::Serde::Value &value) {
  // get the underlying text-value to be used
  auto text = value.as<$::Serde::Text>();

  // ignore if the incoming value is not text at all
  if (text == nullptr) return std::nullopt;

  // and manually cast the text to a suitable severity
  switch (XH::FNV::U32($::Convert::uppercase(*text))) {
  case XH::FNV::U32("NONE"): return Severity::NONE;
  case XH::FNV::U32("HINT"): return Severity::HINT;
  case XH::FNV::U32("INFO"): return Severity::INFO;
  case XH::FNV::U32("WARN"): return Severity::WARN;
  case XH::FNV::U32("ERROR"): return Severity::ERROR;
  default: return std::nullopt; // ignore invalid items
  }
}

template <class K>
$::Map::Base<K, Talos::Relint::Severity> Talos::Relint::Decode::object(const $::Serde::Object &elements) {
  // prepare the output mapping to be used
  auto output = $::Map::Base<K, Severity>();

  // iterate over the current mapping now
  for (const auto &[key, value] : elements) {
    // attempt getting the current severity
    auto override = severity(value);
    if (!override.has_value()) continue;

    if (!value.is<$::Serde::Text>()) continue; // ignore non-string values
    if constexpr (std::same_as<K, $::Serde::Text>) output[key] = *override;
    else if (auto code = diagnostic(key)) output[*code] = *override; // coded
  }

  // return the resulting mapping now
  return output;
}

//  PRIVATE METHODS  //

Talos::Relint::Options Talos::Relint::Options::m_decode(const $::Serde::Value &value) {
  // prepare the default options now
  auto options = Options();

  // stop-fast if there is no valid object
  if (!value.is<$::Serde::Object>()) return options;

  // pull out the details we could be using
  auto *rules = value.at<$::Serde::Object>("rules");
  auto *plugins = value.at<$::Serde::Array>("plugins");
  auto *overrides = value.at<$::Serde::Object>("overrides");
  auto *recommended = value.at<$::Serde::Boolean>("recommended");

  // and assign the values if possible to do so
  if (recommended) options.recommended = *recommended;
  if (rules) options.rules = Decode::object<$::Serde::Text>(*rules);
  if (overrides) options.overrides = Decode::object<Diagnostic::Code>(*overrides);
  if (plugins) options.plugins = $::Serde::Decode<$::Serde::Text>(*plugins);

  // and return the resulting options now
  return Decode::overrides(options), options;
}
