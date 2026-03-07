#ifndef _TALOS_ENGINE_MACROS_IPP
#define _TALOS_ENGINE_MACROS_IPP

/// Talos Modules
#include "talos/engine/dispatch.hpp"

//  MACROS  //

#define TALOS_MM_ENGINE_EXECUTE(N, T, F, I, ...)                                                         \
    template <>                                                                                          \
    $_INLINE_FORCE Talos::Engine::Mode Talos::Engine::Dispatch::m_execute<Talos::Bytecode::Syllable::N>( \
        Isolate * T, Function::Frame * F, Bytecode::Qualified<Bytecode::Syllable::N> * I)

#define TALOS_MM_ENGINE_UNIMPLEMENTED(N, ...)                             \
    TALOS_MM_ENGINE_EXECUTE(N, isolate, , instruction) {                  \
        return isolate->panic(9000002, instruction->name()), Mode::PANIC; \
    }

#endif
