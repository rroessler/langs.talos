/// Relint Modules
#include "talos/relint/_inline/define.ipp"

/// Syntax Modules
#include "talos/syntax/statement/block.hpp"

//  MACROS  //

// name of the rule being used
#define MM_RULE_NAME "talos/no-empty-blocks"

//  PROPERTIES  //

#ifdef TALOS_MM_RELINT_DEFINE

// clang-format off
TALOS_MM_RELINT_DEFINE(MM_RULE_NAME, {
    .recommended = true,
    .severity = Severity::WARN,
    .documentation = {
        .message = "Empty {0} statement",
        .description = "Disallow empty block statements",
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
    hooks->overload<Syntax::Block>([rule](const Syntax::Block* block, Context* context) {
        if (block->empty()) context->report(block, rule, "block");
    });
}

#endif

//  UNDEFINES  //

// ensure the name is undefined
#undef MM_RULE_NAME
