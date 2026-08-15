/// Relint Includes
#include "talos/relint/_inline/rules.ipp"

/// Type Includes
#include "talos/type/_inline/type.ipp"

//  MACROS  //

#define MM_RULE_NAME Talos::Relint::Label::NO_UNSAFE_ACCESSORS

//  PUBLIC METHODS  //

template <> void Talos::Relint::Register<MM_RULE_NAME>::subscribe(Hooks *hooks, const Rule *rule) noexcept {
  hooks->overload<Syntax::Accessor>([rule](const Syntax::Accessor *node, Context *context) {
    // prepare the mirrors to be used now
    auto *field = node->field();
    auto *parent = node->parent();
    auto *mirrors = context->mirrors();

    // get the incoming typing to be checked
    auto type = mirrors->resolve(parent)->type();

    // declare the error if possible to do so (only when type is "Any")
    if (type->is<Type::Any>()) context->report(node, rule, field->name());
  });
}

template <> Talos::Relint::Rule Talos::Relint::Register<MM_RULE_NAME>::define() noexcept {
  return {
      .recommended = true,
      .severity = Severity::WARN,
      .factory = subscribe,
      .documentation = {
          .message = "Unsafe property access into '{0}' of 'Any' value type",
          .description = "Disallows accessing a field from type 'Any'",
      },
  };
}
