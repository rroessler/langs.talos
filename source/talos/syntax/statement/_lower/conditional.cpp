/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/statement.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Conditional, node, compiler, ) {
    // get the base condition to be handled
    auto* condition = node->condition();
    auto type = condition->traits()->lattice();

    // bypass everything if the condition is expected to be truthy/falsey
    if (type.truthy()) return compiler->lower(condition), compiler->lower(node->consequence());
    if (type.falsey()) return compiler->lower(condition), compiler->lower(node->alternative());

    auto* labels = compiler->labels();  // prepare labels
    auto skip = labels->reserve(), exit = labels->reserve();

    compiler->lower(condition, Accumulator());  // conditional
    compiler->emit<Syllable::JUMP_FALSEY>(skip, Accumulator());

    // prepare the consequence handler now
    compiler->lower(node->consequence()), compiler->emit<Syllable::JUMP_TO>(exit);

    // prepare the alternative handler now
    labels->patch(skip), compiler->lower(node->alternative());

    // and finally patch the exit label
    labels->patch(exit);
}
