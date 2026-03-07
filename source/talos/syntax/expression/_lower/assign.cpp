/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Assign, assign, compiler, destination) {
    // handle based on the target details to be used
    switch (auto* target = assign->target(); target->traits()->tag()) {
        case $::RTTI::Hash<Syntax::Accessor>(): {
            auto* accessor = target->as<Syntax::Accessor>();
            auto treg = compiler->registers()->temporary();
            auto index = compiler->symbol(accessor->field()->name());

            compiler->lower(accessor->parent(), treg);
            compiler->lower(assign->value(), Accumulator());

            $_UNUSED $_AUTO = compiler->trace(accessor->parent());  // and store
            compiler->emit<Syllable::STORE_FIELD>(treg, Accumulator(), index);
            compiler->plug<Syllable::REG_MOVE>(destination, Accumulator());
        } break;

        case $::RTTI::Hash<Syntax::Identifier>(): {
            auto* identifier = target->as<Syntax::Identifier>();
            auto extent = compiler->captures()->resolve(identifier);
            compiler->lower(assign->value(), Accumulator());
            $_UNUSED $_AUTO = compiler->trace(identifier);  // trace
            compiler->store(identifier->name(), extent, Accumulator());
            compiler->plug<Syllable::REG_MOVE>(destination, Accumulator());
        } break;

        // otherwise declare an invalid assignment now
        default: compiler->panic(2000500); break;
    }
}
