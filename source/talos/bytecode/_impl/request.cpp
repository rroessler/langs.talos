/// Talos Modules
#include "talos/bytecode/compiler.hpp"
#include "talos/bytecode/routine.hpp"

//  CONSTRUCTORS  //

Talos::Bytecode::Request::Request(const Syntax::Lambda* function) : Request(function, nullptr) {}
Talos::Bytecode::Request::Request(const Syntax::Lambda* function, const $::Ptr::Shared<Variable::Context>& upvalues) :
    Request(function->signature()->prototype(), function->body(), upvalues) {}

Talos::Bytecode::Request::Request(const Syntax::Class* prototype) : Request(prototype, nullptr) {}
Talos::Bytecode::Request::Request(const Syntax::Class* prototype, const $::Ptr::Shared<Variable::Context>& upvalues) :
    Request(prototype->constructor(), prototype->block(), upvalues) {}

Talos::Bytecode::Request::Request(const Syntax::Constructor* constructor, const Syntax::Node* body) :
    Request(constructor, body, nullptr) {}

Talos::Bytecode::Request::Request(const Syntax::Constructor* constructor, const Syntax::Node* body,
    const $::Ptr::Shared<Variable::Context>& upvalues) :
    m_body(body),
    m_constructor(constructor),
    m_registers($::New().unique<Allocator>()),
    m_variables($::New().shared<Variable::Context>(upvalues)) {}

//  PUBLIC METHODS  //

$::Ptr::Unique<Talos::Bytecode::Request> Talos::Bytecode::Queue::dequeue() noexcept {
    auto top = std::move(m_requests.front());
    return m_requests.pop(), std::move(top);
}

Talos::Bytecode::Index Talos::Bytecode::Queue::enqueue(const Syntax::Lambda* function) {
    return enqueue(function, nullptr);
}

Talos::Bytecode::Index Talos::Bytecode::Queue::enqueue(const Syntax::Class* prototype) {
    return enqueue(prototype, nullptr);
}

Talos::Bytecode::Index Talos::Bytecode::Queue::enqueue(
    const Syntax::Lambda* function, const $::Ptr::Shared<Variable::Context>& upvalues) {
    return m_requests.emplace($::New().unique<Request>(function, upvalues)), m_offset++;
}

Talos::Bytecode::Index Talos::Bytecode::Queue::enqueue(
    const Syntax::Class* prototype, const $::Ptr::Shared<Variable::Context>& upvalues) {
    return m_requests.emplace($::New().unique<Request>(prototype, upvalues)), m_offset++;
}
