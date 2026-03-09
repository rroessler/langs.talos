/// Talos Modules
#include "talos/diagnostic/traits.hpp"

/// Forward Declarations
$_FWD(Talos::Diagnostic::Traits, template <Code C, Severity S> bool overridable())

//  PUBLIC METHODS  //

template <Talos::Diagnostic::Code C, Talos::Diagnostic::Severity S>
bool Talos::Diagnostic::Traits::overridable() {
    return C < 9000000 && S != Severity::ERROR;
}

bool Talos::Diagnostic::Traits::overridable(Code code) {
    // attempt checking if the value fits an overridable one
    switch (code) {
#define TALOS_XX_DIAGNOSTIC_CODE(_, N, S, ...) \
    case (N): return overridable<N, Severity::S>();
#include "talos/diagnostic/_defines/codes.def"
        default: return false;
    }
}

Talos::Diagnostic::Tags Talos::Diagnostic::Traits::tags(Code code) {
    switch (code) {
#define TALOS_XX_DIAGNOSTIC_CODE(_, N, __, ___, ...) \
    case N: return Tags(__VA_ARGS__);
#include "talos/diagnostic/_defines/codes.def"
        default: return Tags();
    }
}

Talos::Diagnostic::Severity Talos::Diagnostic::Traits::severity(Code code) {
    switch (code) {
#define TALOS_XX_DIAGNOSTIC_CODE(_, N, S, ...) \
    case N: return Severity::S;
#include "talos/diagnostic/_defines/codes.def"
        default: return Severity::NONE;
    }
}

$::String::View Talos::Diagnostic::Traits::category(Code code) {
    switch (code) {
#define TALOS_XX_DIAGNOSTIC_CODE(C, N, S, ...) \
    case N: return C;
#include "talos/diagnostic/_defines/codes.def"
        default: return "Unknown";
    }
}

$::String::View Talos::Diagnostic::Traits::message(Code code) {
    switch (code) {
#define TALOS_XX_DIAGNOSTIC_CODE(_, N, __, M, ...) \
    case N: return M;
#include "talos/diagnostic/_defines/codes.def"
        default: $_ABORT("Unknown diagnostic code: {0}", code);
    }
}
