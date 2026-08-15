/// Talos Includes
#include "talos/module/abstract.hpp"
#include "talos/async/future.hpp"
#include "talos/document/service.hpp"
#include "talos/function/common.hpp"
#include "talos/runtime/container.hpp"
#include "talos/runtime/isolate.hpp"
#include "talos/toolchain/audit.hpp"
#include "talos/toolchain/parse.hpp"

/// Metadata Includes
#include "talos/bytecode/metadata.hpp"
#include "talos/syntax/metadata.hpp"
#include "talos/type/metadata.hpp"

//  CONSTRUCTORS  //

Talos::Module::Abstract::Abstract(const $::URI::Buffer &resource) :
    Abstract($::Global::get<Runtime::Container>(), resource) {}

Talos::Module::Abstract::Abstract(XI::Container *services, const $::URI::Buffer &resource) :
    m_reporter(services->get<Diagnostic::Reporter>(resource)) {}

//  PRIVATE METHODS  //

Talos::Syntax::Dependencies Talos::Module::Abstract::m_dependencies() const noexcept {
  return metadata<Phase::PARSED>()->tree()->dependencies();
}

$::Shared::Pointer<Talos::Document::Buffer>
Talos::Module::Abstract::m_document(XI::Container *services) const noexcept {
  return m_document(services, resource());
}

$::Shared::Pointer<Talos::Document::Buffer>
Talos::Module::Abstract::m_document(XI::Container *services, const $::URI::View &resource) const noexcept {
  if (resource.scheme() != $::URI::Scheme::FILE) return $::Shared::New<Document::Buffer>();
  return services->get<Document::Service>()->resolve(resource); // attempt resolving now
}

void Talos::Module::Abstract::m_parse(XI::Container *) { metadata<Phase::PARSED>(); }
void Talos::Module::Abstract::m_analyze(XI::Container *) { metadata<Phase::TYPED>(); }
void Talos::Module::Abstract::m_compile(XI::Container *) { metadata<Phase::COMPILED>(); }

Talos::Async::Thenable *
Talos::Module::Abstract::m_interpret(Runtime::Isolate *isolate, Metadata::Wrapper<Phase::EXPORTED> *exports) {
  // get the underlying thenable instance
  auto *thenable = exports->thenable();

  // prepare a local-scoping to be used
  auto local_scope = isolate->scope(exports);

  // bind in the internal arena details for the "main" function
  const auto *codegen = metadata<Phase::COMPILED>();
  auto *info = codegen->arena()->functions[0].get();

  // construct the main module future to be resolved
  auto local_main = local_scope(isolate->create<Function::Closure>(info));
  auto local_future = local_scope(isolate->create<Async::Future>(*local_main));

  auto local_thenable = local_future->thenable(); // and await the result
  auto okay = local_scope(local_thenable->await(isolate))->pointer().okay();

  // check the result is valid and handle accordingly now
  if (okay) okay = thenable->resolve(isolate, exports->close());
  else okay = thenable->reject(isolate, isolate->exception());

  // and return the thenable based on the final details
  return okay ? thenable : nullptr;
}
