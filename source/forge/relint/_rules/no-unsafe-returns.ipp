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
#define MM_RULE_NAME "talos/no-unsafe-returns"

//  PROPERTIES  //

#ifdef FORGE_MM_RELINT_DEFINE

// clang-format off
FORGE_MM_RELINT_DEFINE(MM_RULE_NAME, {
    .recommended = true,
    .severity = Severity::WARN,
    .documentation = {
        .message = "Unsafe return of 'Any' value type",
        .description = "Disallows returning a value of type 'Any'",
    },

    // handle showing where there are empty-blocks
    .factory = Register<MM_RULE_NAME>,
})
// clang-format on

#endif

//  PUBLIC METHODS  //

#ifdef FORGE_MM_RELINT_REGISTER

$_FWD(void unsafe_returns(const Mirror*, const Mirror*, const Rule*, Context*), Forge::Relint::Dispatch)
void Forge::Relint::Dispatch::unsafe_returns(
    const Mirror* value, const Mirror* parent, const Rule* rule, Context* context) {
    // ensure both the value and parent are valid
    if (value == nullptr || parent == nullptr) return;

    // prepare the incoming return typing now
    auto typing = value->typing();

    // stop early if the incoming typing is a failure
    if (typing->is<Type::Failure>()) return;

    // pull out the signature and callable typing here
    auto callable = Type::Builder::resolve<Type::Callable>(parent->typing());
    auto returns = callable ? callable->returns() : Type::Builder::unset();

    // check if the incoming value is potentially unsafe
    auto unsafe = typing->is<Type::Any>() && !returns->is<Type::Any>();

    // declare the error if possible to do so
    if (unsafe) context->report(value->origin(), rule);
}

template <>
void Forge::Relint::Register<MM_RULE_NAME>(Hooks* hooks, const Rule* rule) {
    // check all base return values here
    hooks->overload<Syntax::Return>([rule](const Syntax::Return* node, Context* context) {
        // prepare the mirrors to be used here
        auto* mirrors = context->mirrors();
        auto* value = mirrors->resolve(node->value());

        // attempt scanning until the parent callable
        auto parent = mirrors->resolve(value->parent<Syntax::Lambda>());

        // attempt dispatching the unsafe handler
        Dispatch::unsafe_returns(value, parent, rule, context);
    });

    // check all incoming lambdas (for non-block returns)
    hooks->overload<Syntax::Lambda>([rule](const Syntax::Lambda* lambda, Context* context) {
        // ignore if we have a block given
        if (lambda->body()->is<Syntax::Block>()) return;

        // prepare the mirrors to be used
        auto* mirrors = context->mirrors();

        // prepare the base mirrors now
        auto parent = mirrors->resolve(lambda);
        auto value = mirrors->resolve(lambda->body());

        // attempt dispatching the unsafe handler
        Dispatch::unsafe_returns(value, parent, rule, context);
    });
}

#endif

//  UNDEFINES  //

// ensure the name is undefined
#undef MM_RULE_NAME
