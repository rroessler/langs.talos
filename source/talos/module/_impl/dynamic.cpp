/// Talos Includes
#include "talos/module/dynamic.hpp"
#include "talos/crate/service.hpp"
#include "talos/runtime/isolate.hpp"

/// Metadata Includes
#include "talos/syntax/metadata.hpp"
#include "talos/type/metadata.hpp"

//  PRIVATE METHODS  //

Talos::Async::Thenable *
Talos::Module::Dynamic::m_interpret(Runtime::Isolate *isolate, Metadata::Wrapper<Phase::EXPORTED> *exports) {
  auto *thenable = exports->thenable(); // prepare
  auto *crates = isolate->service<Crate::Service>();

  // prepare the result to be returned
  auto result = crates->dylib(isolate, name());
  auto okay = result.pointer().okay();

  if (result.pointer().okay()) okay = thenable->resolve(isolate, result);
  else okay = thenable->reject(isolate, isolate->exception());

  // and resolve to the final details now
  return okay ? thenable : nullptr;
}
