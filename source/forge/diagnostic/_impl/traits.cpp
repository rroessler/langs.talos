/// Forge Modules
#include "forge/diagnostic/traits.hpp"

/// Forward Declarations
$_FWD(template <Code C $_PP_COMMA Severity S> bool overridable(), Forge::Diagnostic::Traits)

//  PUBLIC METHODS  //

template <Forge::Diagnostic::Code C, Forge::Diagnostic::Severity S>
bool Forge::Diagnostic::Traits::overridable() {
    return C < 9000000 && S != Severity::ERROR;
}

bool Forge::Diagnostic::Traits::overridable(Code code) {
    // attempt checking if the value fits an overridable one
    switch (code) {
#define FORGE_XX_DIAGNOSTIC_CODE(_, N, S, ...) \
    case (N): return overridable<N, Severity::S>();
#include "forge/diagnostic/_defines/codes.def"
        default: return false;
    }
}

Forge::Diagnostic::Tags Forge::Diagnostic::Traits::tags(Code code) {
    switch (code) {
#define FORGE_XX_DIAGNOSTIC_CODE(_, N, __, ___, ...) \
    case N: return Tags(__VA_ARGS__);
#include "forge/diagnostic/_defines/codes.def"
        default: return Tags();
    }
}

Forge::Diagnostic::Severity Forge::Diagnostic::Traits::severity(Code code) {
    switch (code) {
#define FORGE_XX_DIAGNOSTIC_CODE(_, N, S, ...) \
    case N: return Severity::S;
#include "forge/diagnostic/_defines/codes.def"
        default: return Severity::NONE;
    }
}

$::String::View Forge::Diagnostic::Traits::category(Code code) {
    switch (code) {
#define FORGE_XX_DIAGNOSTIC_CODE(C, N, S, ...) \
    case N: return C;
#include "forge/diagnostic/_defines/codes.def"
        default: return "Unknown";
    }
}

$::String::View Forge::Diagnostic::Traits::message(Code code) {
    switch (code) {
#define FORGE_XX_DIAGNOSTIC_CODE(_, N, __, M, ...) \
    case N: return M;
#include "forge/diagnostic/_defines/codes.def"
        default: $_ABORT("Unknown diagnostic code: {0}", code);
    }
}
