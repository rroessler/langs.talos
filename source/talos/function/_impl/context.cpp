/// Talos Modules
#include "talos/function/context.hpp"
#include "talos/runtime/isolate.hpp"

//  CONSTRUCTORS  //

Talos::Function::Context::Context(Runtime::Isolate* isolate, size_t size) : Context() {
    if (size) m_environment = isolate->create<Iterable::List>(Offset::VALUES + size);
}
