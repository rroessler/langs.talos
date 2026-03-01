/// Forge Modules
#include "forge/bytecode/compiler.hpp"
#include "forge/bytecode/routine.hpp"

//  CONSTRUCTORS  //

Forge::Bytecode::Request::Request(const Syntax::Lambda* function) : Request(function, nullptr) {}
Forge::Bytecode::Request::Request(const Syntax::Lambda* function, const $::Ptr::Shared<Variable::Context>& upvalues) :
    m_function(function),
    m_registers($::New().unique<Allocator>()),
    m_variables($::New().shared<Variable::Context>(upvalues)) {}

//  PUBLIC METHODS  //

$::Ptr::Unique<Forge::Bytecode::Request> Forge::Bytecode::Queue::dequeue() noexcept {
    auto top = std::move(m_requests.front());
    return m_requests.pop(), std::move(top);
}

Forge::Bytecode::Index Forge::Bytecode::Queue::enqueue(const Syntax::Lambda* function) {
    return enqueue(function, nullptr);
}

Forge::Bytecode::Index Forge::Bytecode::Queue::enqueue(
    const Syntax::Lambda* function, const $::Ptr::Shared<Variable::Context>& upvalues) {
    return m_requests.emplace($::New().unique<Request>(function, upvalues)), m_offset++;
}
