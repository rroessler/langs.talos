/// Talos Includes
#include "talos/diagnostic/inspect.hpp"

/// Forward Declarations
$_FWD(Talos::Diagnostic::Inspect, template <Code C, Severity S> bool overridable())

//  PUBLIC METHODS  //

template <Talos::Diagnostic::Code C, Talos::Diagnostic::Severity S> bool Talos::Diagnostic::Inspect::overridable() {
  return C < 9000000 && S != Severity::ERROR; // we only allow overriding codes that are non-errors
}

bool Talos::Diagnostic::Inspect::overridable(Code code) {
  // attempt checking if the value fits an overridable one
  switch (code) {
#define TALOS_XX_DIAGNOSTIC_CODE(_, N, S, ...)    \
  case (N): return overridable<N, Severity::S>();
#include "talos/diagnostic/_defines/codes.def"
  default: return false;
  }
}

Talos::Diagnostic::Tags Talos::Diagnostic::Inspect::tags(Code code) {
  switch (code) {
#define TALOS_XX_DIAGNOSTIC_CODE(_, N, __, ___, ...) \
  case N: return Tags(__VA_ARGS__);
#include "talos/diagnostic/_defines/codes.def"
  default: return Tags();
  }
}

Talos::Diagnostic::Severity Talos::Diagnostic::Inspect::severity(Code code) {
  switch (code) {
#define TALOS_XX_DIAGNOSTIC_CODE(_, N, S, ...) \
  case N: return Severity::S;
#include "talos/diagnostic/_defines/codes.def"
  default: return Severity::NONE;
  }
}

$::String::View Talos::Diagnostic::Inspect::message(Code code) {
  switch (code) {
#define TALOS_XX_DIAGNOSTIC_CODE(_, N, __, M, ...) \
  case N: return M;
#include "talos/diagnostic/_defines/codes.def"
  default: $_ABORT("Unknown diagnostic code: {0}", code);
  }
}

$::String::View Talos::Diagnostic::Inspect::category(Code code) {
  switch (code) {
#define TALOS_XX_DIAGNOSTIC_CODE(C, N, S, ...) \
  case N: return C;
#include "talos/diagnostic/_defines/codes.def"
  default: return "Unknown";
  }
}
