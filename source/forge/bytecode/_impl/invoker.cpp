/// Forge Modules
#include "forge/bytecode/invoker.hpp"
#include "forge/bytecode/compiler.hpp"

//  PUBLIC METHODS  //

void Forge::Bytecode::Invoker::invoke(
    Compiler* compiler, Destination destination, const std::vector<Syntax::Expression*>& arguments) const noexcept {
    // prepare the dispatch handler now
    auto list = m_prepare(compiler, destination, arguments, false);

    // and dispatch a multiple invocation now
    arguments.empty() ? m_invoke(compiler, destination) : m_invoke(compiler, destination, list);
}

void Forge::Bytecode::Invoker::spawn(
    Compiler* compiler, Destination destination, const std::vector<Syntax::Expression*>& arguments) const noexcept {
    // prepare the dispatch handler now
    auto list = m_prepare(compiler, destination, arguments, true);

    // and dispatch a multiple invocation now
    arguments.empty() ? m_spawn(compiler, destination) : m_spawn(compiler, destination, list);
}

//  PRIVATE METHODS  //

Forge::Bytecode::Register::List Forge::Bytecode::Invoker::m_prepare(Compiler* compiler, Destination& destination,
    const std::vector<Syntax::Expression*>& arguments, bool async) const noexcept {
    // prepare the arguments list to be used
    auto list = compiler->registers()->list();

    // fix the destination to be used now
    if (destination.nowhere()) destination = Accumulator();

    // construct a suitable callee register to be used
    auto creg = arguments.empty() || inlined(async) ? Accumulator() : list.grow();

    // handle the callee value that should be lowered
    switch (m_convention) {
        case Convention::VOID: compiler->lower(m_callee, creg); break;
        case Convention::FIELD: compiler->lower(m_callee->as<Syntax::Accessor>()->parent(), creg); break;
        case Convention::INLINE: {
            // we only allow inline if not asynchronous
            if (async) compiler->lower(m_callee, creg);
        } break;
    }

    // otherwise attempt building with multiple values
    for (const auto& argument : arguments) compiler->lower(argument, list.grow());

    // return the resulting list now
    return list;
}

void Forge::Bytecode::Invoker::m_invoke(Compiler* compiler, Destination destination) const noexcept {
    switch (m_convention) {
        case Convention::VOID: compiler->emit<Syllable::CALL_0_VOID>(destination); break;
        case Convention::INLINE: compiler->emit<Syllable::CALL_0_INLINE>(destination); break;
        case Convention::FIELD: {
            $_UNUSED $_AUTO = compiler->trace(m_callee);
            auto field = m_callee->as<Syntax::Accessor>()->field();  // cast to suitable field
            compiler->emit<Syllable::CALL_0_FIELD>(destination, compiler->symbol(field->name()));
        } break;
    }
}

void Forge::Bytecode::Invoker::m_invoke(
    Compiler* compiler, Destination destination, const Register::Span& span) const noexcept {
    switch (m_convention) {
        case Convention::VOID: compiler->emit<Syllable::CALL_N_VOID>(destination, span); break;
        case Convention::INLINE: compiler->emit<Syllable::CALL_N_INLINE>(destination, span); break;
        case Convention::FIELD: {
            $_UNUSED $_AUTO = compiler->trace(m_callee);
            auto field = m_callee->as<Syntax::Accessor>()->field();  // cast to a suitable field now
            compiler->emit<Syllable::CALL_N_FIELD>(destination, compiler->symbol(field->name()), span);
        } break;
    }
}

void Forge::Bytecode::Invoker::m_spawn(Compiler* compiler, Destination destination) const noexcept {
    switch (m_convention) {
        case Convention::VOID: $_FALLTHROUGH;  // we do not have inline items when spawning
        case Convention::INLINE: compiler->emit<Syllable::SPAWN_0_VOID>(destination); break;
        case Convention::FIELD: {
            $_UNUSED $_AUTO = compiler->trace(m_callee);
            auto field = m_callee->as<Syntax::Accessor>()->field();  // cast to suitable field
            compiler->emit<Syllable::SPAWN_0_FIELD>(destination, compiler->symbol(field->name()));
        } break;
    }
}

void Forge::Bytecode::Invoker::m_spawn(
    Compiler* compiler, Destination destination, const Register::Span& span) const noexcept {
    switch (m_convention) {
        case Convention::VOID: $_FALLTHROUGH;  // we do not have inline items when spawning
        case Convention::INLINE: compiler->emit<Syllable::SPAWN_N_VOID>(destination, span); break;
        case Convention::FIELD: {
            $_UNUSED $_AUTO = compiler->trace(m_callee);
            auto field = m_callee->as<Syntax::Accessor>()->field();  // cast to a suitable field now
            compiler->emit<Syllable::SPAWN_N_FIELD>(destination, compiler->symbol(field->name()), span);
        } break;
    }
}
