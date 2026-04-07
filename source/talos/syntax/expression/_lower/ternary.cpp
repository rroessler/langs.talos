/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Ternary, node, compiler, destination) {
    // get the base condition to be handled
    auto* condition = node->condition();
    auto type = condition->traits()->lattice();

    // bypass everything if the condition is truthy/falsey
    if (type.truthy()) return compiler->lower(condition), compiler->lower(node->consequence(), destination);
    if (type.falsey()) return compiler->lower(condition), compiler->lower(node->alternative(), destination);

    auto* labels = compiler->labels();  // prepare labels
    auto skip = labels->reserve(), exit = labels->reserve();

    compiler->lower(condition, Accumulator());  // conditional
    compiler->emit<Syllable::JUMP_FALSEY>(skip, Accumulator());

    // prepare the consequence handler now
    compiler->lower(node->consequence(), destination);
    compiler->emit<Syllable::JUMP_TO>(exit);  // bailout

    // prepare the alternative pathway handler
    labels->patch(skip), compiler->lower(node->alternative(), destination);

    // and finally patch the exit handler
    labels->patch(exit);
}
