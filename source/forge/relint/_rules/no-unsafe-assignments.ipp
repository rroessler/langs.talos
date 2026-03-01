/// Relint Modules
#include "forge/relint/_inline/define.ipp"

/// Type Modules
#include "forge/type/_inline/type.ipp"

/// Syntax Modules
#include "forge/syntax/declaration/variable.hpp"

/// Type Modules
#include "forge/type/_inline/type.ipp"

//  MACROS  //

// name of the rule being used
#define MM_RULE_NAME "talos/no-unsafe-assignments"

//  PROPERTIES  //

#ifdef FORGE_MM_RELINT_DEFINE

// clang-format off
FORGE_MM_RELINT_DEFINE(MM_RULE_NAME, {
    .recommended = true,
    .severity = Severity::WARN,
    .documentation = {
        .message = "Unsafe assignment of an 'Any' value to variable of type '{0}'",
        .description = "Disallows assigning a value with type 'Any' to variables",
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
    hooks->overload<Syntax::Variable>([rule](const Syntax::Variable* variable, Context* context) {
        // prepare the mirrors and initializer
        auto* mirrors = context->mirrors();

        // get the incoming initializer to be used
        const auto* initializer = variable->initializer();

        // stop if there is no initializer
        if (initializer == nullptr) return;

        // prepare the incoming types to be used now
        auto expected = mirrors->resolve(variable)->typing();
        auto incoming = mirrors->resolve(initializer)->typing();

        // stop early if the expected typing is a failure at all
        if (expected->is<Type::Failure>()) return;

        // declare the error if possible to do so
        auto unsafe = !expected->is<Type::Any>() && incoming->is<Type::Any>();
        if (unsafe) context->report(initializer, rule, *expected);  // show
    });
}

#endif

//  UNDEFINES  //

// ensure the name is undefined
#undef MM_RULE_NAME
