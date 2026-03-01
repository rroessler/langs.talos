#ifndef _FORGE_ENGINE_MACROS_IPP
#define _FORGE_ENGINE_MACROS_IPP

/// Forge Modules
#include "forge/engine/dispatch.hpp"

//  MACROS  //

#define FORGE_MM_ENGINE_EXECUTE(N, T, F, I, ...)                                                         \
    template <>                                                                                          \
    $_INLINE_FORCE Forge::Engine::Mode Forge::Engine::Dispatch::m_execute<Forge::Bytecode::Syllable::N>( \
        Isolate * T, Function::Frame * F, Bytecode::Qualified<Bytecode::Syllable::N> * I)

#define FORGE_MM_ENGINE_UNIMPLEMENTED(N, ...)                             \
    FORGE_MM_ENGINE_EXECUTE(N, isolate, , instruction) {                  \
        return isolate->panic(9000002, instruction->name()), Mode::PANIC; \
    }

#endif
