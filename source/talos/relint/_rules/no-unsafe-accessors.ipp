/// Relint Modules
#include "talos/relint/_inline/define.ipp"

/// Type Modules
#include "talos/type/_inline/type.ipp"

/// Syntax Modules
#include "talos/syntax/expression/accessor.hpp"

/// Type Modules
#include "talos/type/_inline/type.ipp"

//  MACROS  //

// name of the rule being used
#define MM_RULE_NAME "talos/no-unsafe-accessors"

//  PROPERTIES  //

#ifdef TALOS_MM_RELINT_DEFINE

// clang-format off
TALOS_MM_RELINT_DEFINE(MM_RULE_NAME, {
    .recommended = true,
    .severity = Severity::WARN,
    .documentation = {
        .message = "Unsafe property access into '{0}' of 'Any' value type",
        .description = "Disallows accessing a field from type 'Any'",
    },

    // handle showing where there are empty-blocks
    .factory = Register<MM_RULE_NAME>,
})
// clang-format on

#endif

//  PUBLIC METHODS  //

#ifdef TALOS_MM_RELINT_REGISTER

template <>
void Talos::Relint::Register<MM_RULE_NAME>(Hooks* hooks, const Rule* rule) {
    hooks->overload<Syntax::Accessor>([rule](const Syntax::Accessor* node, Context* context) {
        // prepare the mirrors to be used now
        auto* field = node->field();
        auto* parent = node->parent();
        auto* mirrors = context->mirrors();

        // get the incoming typing to be checked
        auto typing = mirrors->resolve(parent)->typing();

        // ignore if the typing is a silent value
        if (typing->is<Type::Failure>()) return;

        // declare the error if possible to do so
        if (typing->is<Type::Any>()) context->report(node, rule, field->name());
    });
}

#endif

//  UNDEFINES  //

// ensure the name is undefined
#undef MM_RULE_NAME
