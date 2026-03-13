/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Enum, enumeration, compiler, ) {
    // trace the incoming enumeration node now
    $_UNUSED $_AUTO = compiler->trace(enumeration);

    // prepare the destination of the enumeration
    auto [dest, leaked] = compiler->declare(enumeration);
    $_ASSERT(!dest.nowhere(), "Declaration does not exist?");
    auto treg = leaked ? compiler->registers()->temporary() : dest;

    // prepare a suitable variables list
    auto arguments = compiler->registers()->list();

    // attempt building our values into a list
    for (const auto& variant : enumeration->variants()) {
        // ensure we trace on each of the variants
        $_UNUSED $_AUTO = compiler->trace(variant);

        // prepare the name, label and value registers
        auto kreg = arguments.grow(), lreg = arguments.grow(), vreg = arguments.grow();

        // prepare each of our items now
        compiler->emit<Syllable::STRING_MAKE>(kreg, compiler->string(variant->key()));

        if (auto* label = variant->label()) compiler->lower(label, lreg);
        else compiler->emit<Syllable::REG_MOVE>(lreg, kreg);  // copy here

        if (auto* value = variant->value()) compiler->lower(value, vreg);
        else compiler->emit<Syllable::LOAD_VOID>(vreg);  // auto-build
    }

    // once complete, construct an enumeration literal
    if (arguments.empty()) compiler->emit<Syllable::ENUM_EMPTY>(treg);
    else compiler->emit<Syllable::ENUM_MAKE>(treg, arguments);

    // post-emit the expose handler
    compiler->expose(enumeration, treg);

    // finally emit the outgoing details now
    if (leaked) compiler->emit<Syllable::STORE_CONTEXT>(dest, treg);
}

TALOS_MM_LOWER_UNIMPLEMENTED(Variant, , compiler, )
