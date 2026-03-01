/// Relint Modules
#include "forge/relint/_inline/define.ipp"

/// Type Modules
#include "forge/type/_inline/type.ipp"

/// Syntax Modules
#include "forge/syntax/expression/call.hpp"

/// Type Modules
#include "forge/type/_inline/type.ipp"

//  MACROS  //

// name of the rule being used
#define MM_RULE_NAME "talos/no-unsafe-calls"

//  PROPERTIES  //

#ifdef FORGE_MM_RELINT_DEFINE

// clang-format off
FORGE_MM_RELINT_DEFINE(MM_RULE_NAME, {
    .recommended = true,
    .severity = Severity::WARN,
    .documentation = {
        .message = "Unsafe call of 'Any' value type",
        .description = "Disallows calling a value with type 'Any'",
    },

    // handle showing where there are empty-blocks
    .factory = Register<MM_RULE_NAME>,
})
// clang-format on

#endif

//  PUBLIC METHODS  //

#ifdef FORGE_MM_RELINT_REGISTER

template <>
void Forge::Relint::Register<MM_RULE_NAME>(Hooks* hooks, const Rule* rule) {
    hooks->overload<Syntax::Call>([rule](const Syntax::Call* node, Context* context) {
        // prepare the mirrors and callee
        auto* callee = node->callee();
        auto* mirrors = context->mirrors();

        // get the incoming typing to be checked
        auto typing = mirrors->resolve(callee)->typing();

        // ignore if the typing is a silent value
        if (typing->is<Type::Failure>()) return;

        // declare the error if possible to do so
        if (typing->is<Type::Any>()) context->report(callee, rule);
    });
}

#endif

//  UNDEFINES  //

// ensure the name is undefined
#undef MM_RULE_NAME
