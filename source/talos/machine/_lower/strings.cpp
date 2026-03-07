/// Talos Modules
#include "talos/engine/dispatch.hpp"
#include "talos/string/dynamic.hpp"

/// Inline Modules
#include "talos/machine/_inline/macros.ipp"

//  PRIVATE METHODS  //

TALOS_MM_MACHINE_EMIT(STRING_MAKE, builder, instruction) {
    __ee__ string(instruction->get<0>(), instruction->get<1>());
}

TALOS_MM_MACHINE_EMIT(STRING_CONCAT, builder, instruction) {
    // prepare the incoming registers now
    auto dx = __ee__ resolve(instruction->get<0>());
    auto ax = __ee__ resolve(instruction->get<1>());
    auto bx = __ee__ resolve(instruction->get<2>());

    // emit the invocation for concatenation strings
    __ee__ invoke(Engine::Dispatch::concat, dx, builder->isolate, ax, bx);
}
