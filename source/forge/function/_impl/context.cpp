/// Forge Modules
#include "forge/function/context.hpp"
#include "forge/runtime/isolate.hpp"

//  CONSTRUCTORS  //

Forge::Function::Context::Context(Runtime::Isolate* isolate, size_t size) : Context() {
    if (size) m_environment = isolate->create<Iterable::List>(Offset::VALUES + size);
}