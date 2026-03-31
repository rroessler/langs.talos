/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Decorator, decorator, compiler, destination) {
    // ensure the incoming destination is valid
    if (destination.nowhere()) return;

    // prepare a suitable list for compilation
    auto list = compiler->registers()->list();

    // prepare the decorator to be called and the target to bind
    compiler->lower(decorator->expression(), list.grow());
    compiler->emit<Syllable::REG_MOVE>(list.grow(), destination);

    // attempt applying the decorator now to the built arguments
    compiler->emit<Syllable::CALL_N_VOID>(destination, list);
}
