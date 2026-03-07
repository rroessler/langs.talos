/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Record, record, compiler, destination) {
    // trace the incoming binary node now
    $_UNUSED $_AUTO = compiler->trace(record);

    // if empty, then construct an empty record
    if (record->empty()) return compiler->plug<Syllable::OBJECT_EMPTY>(destination);

    // prepare a suitable variables list
    auto arguments = compiler->registers()->list();

    // attempt building our values into a list
    for (const auto& element : record->elements()) {
        // ensure we trace each of the element declarations
        $_UNUSED $_AUTO = compiler->trace(element);

        // prepare the key-register and variable register
        auto kreg = arguments.grow(), vreg = arguments.grow();

        // bind the element to a symbol as well
        auto symbol = compiler->symbol(element->name());
        compiler->emit<Syllable::LOAD_CONST>(kreg, symbol);

        // prepare the initializer instance
        auto* initializer = element->initializer();
        if (initializer) compiler->lower(initializer, vreg);
        else compiler->emit<Syllable::LOAD_VOID>(vreg);
    }

    // once complete, construct an object literal
    compiler->plug<Syllable::OBJECT_MAKE>(destination, arguments);
}
