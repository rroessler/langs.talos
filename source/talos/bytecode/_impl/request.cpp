/// Talos Modules
#include "talos/bytecode/compiler.hpp"
#include "talos/bytecode/routine.hpp"

//  CONSTRUCTORS  //

Talos::Bytecode::Request::Request(const Syntax::Lambda *function, const $::Shared::Pointer<Variable::Scope> &upvalues) :
    Request(function->signature()->prototype(), function->body(), upvalues) {}

Talos::Bytecode::Request::Request(const Syntax::Class *prototype, const $::Shared::Pointer<Variable::Scope> &upvalues) :
    Request(prototype->constructor(), prototype->block(), upvalues) {
  m_super = prototype->super(); // bind the super-call as well
}

Talos::Bytecode::Request::Request(
    const Syntax::Constructor *signature, const Syntax::Node *body, const $::Shared::Pointer<Variable::Scope> &upvalues
) :
    m_body(body), m_signature(signature), m_registers($::Unique::New<Allocator>()),
    m_variables($::Shared::New<Variable::Scope>(upvalues)) {}

//  PUBLIC METHODS  //

$::Unique::Pointer<Talos::Bytecode::Request> Talos::Bytecode::Queue::dequeue() noexcept {
  auto top = std::move(m_requests.front());
  return m_requests.pop(), std::move(top);
}

Talos::Bytecode::Index Talos::Bytecode::Queue::enqueue(const Syntax::Lambda *function) {
  return enqueue(function, nullptr);
}

Talos::Bytecode::Index Talos::Bytecode::Queue::enqueue(const Syntax::Class *prototype) {
  return enqueue(prototype, nullptr);
}

Talos::Bytecode::Index
Talos::Bytecode::Queue::enqueue(const Syntax::Lambda *function, const $::Shared::Pointer<Variable::Scope> &upvalues) {
  return m_requests.emplace($::Unique::New<Request>(function, upvalues)), m_offset++;
}

Talos::Bytecode::Index
Talos::Bytecode::Queue::enqueue(const Syntax::Class *prototype, const $::Shared::Pointer<Variable::Scope> &upvalues) {
  return m_requests.emplace($::Unique::New<Request>(prototype, upvalues)), m_offset++;
}
