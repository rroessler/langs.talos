/// Forge Modules
#include "forge/bytecode/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/statement.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LOWER_NODE(Loop, node, compiler, ) {
    // get the underlying condition details
    auto *condition = node->condition();
    auto type = condition->traits()->lattice();

    // ignore if the loop never runs at all
    if (type.falsey()) return compiler->lower(condition);

    // prepare the loop instance to be used now
    auto loop = compiler->loop();

    // compile the incoming condition onto the accumulator
    compiler->lower(condition, Accumulator());

    // allow exiting if we have a non-forever loop
    if (!type.truthy()) compiler->emit<Syllable::JUMP_FALSEY>(loop.exit(), Accumulator());

    // and lower the entire body now
    compiler->lower(node->statement());
}

FORGE_MM_LOWER_NODE(For, node, compiler, ) {
    // get some common items to be used now
    auto parameters = node->parameters();

    // prepare a new variable scoping to be used
    $_UNUSED $_AUTO = compiler->scope();
    $_UNUSED $_AUTO = compiler->trace(node);

    // prepare our necessary registers to be used
    auto value = parameters.size() > 0 ? compiler->declare(parameters.at(0)).first : Register();
    auto index = parameters.size() > 1 ? compiler->declare(parameters.at(1)).first : Register();

    // prepare a suitable "temporary" for the iterator register
    auto iterator = compiler->registers()->allocate();

    // ensure we compiler our iterator into the necessary location
    $_PP_SCOPE() {
        $_UNUSED $_AUTO = compiler->trace(node->iterable());
        compiler->lower(node->iterable(), iterator);  // prepare
        compiler->emit<Syllable::ITER_LOAD>(iterator, iterator);
    }

    // start the loop sequence now to be used
    auto loop = compiler->loop();

    // get the next iterator value now
    compiler->emit<Syllable::ITER_NEXT>(iterator, value, index);
    compiler->emit<Syllable::JUMP_TRUTHY>(loop.exit(), Accumulator());

    // ensure we now compile our desired loop statement
    compiler->lower(node->statement());
}
