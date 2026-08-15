/// Relint Includes
#include "talos/relint/_inline/rules.ipp"

/// Type Includes
#include "talos/type/_inline/type.ipp"

//  MACROS  //

#define MM_RULE_NAME Talos::Relint::Label::NO_UNSAFE_CALLS

//  PUBLIC METHODS  //

template <> void Talos::Relint::Register<MM_RULE_NAME>::subscribe(Hooks *hooks, const Rule *rule) noexcept {
  hooks->overload<Syntax::Call>([rule](const Syntax::Call *node, Context *context) {
    // prepare the mirrors and callee
    auto *callee = node->callee();
    auto *mirrors = context->mirrors();

    // get the incoming typing to be checked
    auto type = mirrors->resolve(callee)->type();

    // declare the error if possible to do so
    if (type->is<Type::Any>()) context->report(callee, rule);
  });
}

template <> Talos::Relint::Rule Talos::Relint::Register<MM_RULE_NAME>::define() noexcept {
  return {
      .recommended = true,
      .severity = Severity::WARN,
      .factory = subscribe,
      .documentation = {
          .message = "Unsafe call of 'Any' value type",
          .description = "Disallows calling a value with type 'Any'",
      },
  };
}
