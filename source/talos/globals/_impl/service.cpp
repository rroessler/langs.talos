/// Talos Includes
#include "talos/globals/service.hpp"
#include "talos/dylib/registry.hpp"
#include "talos/runtime/isolate.hpp"
#include "talos/type/world.hpp"
#include "talos/value/boolean.hpp"

/// Builtin Includes
#include "talos/builtins/_inline/builtins.ipp"

//  CONSTRUCTORS  //

Talos::Globals::Service::Service() : m_types($::Unique::New<Type::World>()) {
// define all the available type definitions for our builtins
#define XX_TYPEDEFS(T, ...)                                                                                         \
  if (!m_types->entities().contains(Builtins::Inspect<T>::name())) Builtins::Inspect<T>::m_typedefs(m_types.get());
  TALOS_XX_BUILTINS_LIST(XX_TYPEDEFS)
#undef XX_TYPEDEFS

// define all the factory based globals for our builtins
#define XX_GLOBALS(T, ...)                                                 \
  if (auto &&factory = Builtins::Inspect<T>::m_globals())                  \
    m_factories.emplace(Builtins::Inspect<T>::name(), std::move(factory));
  TALOS_XX_BUILTINS_LIST(XX_GLOBALS)
#undef XX_TYPEDEFS

  // emplace some uncommon globals as well
  m_values.emplace("True", Value::True);
  m_values.emplace("False", Value::False);

  // finally show how many globals we registered
  $_TRACE("Globals::Service: Registered {0} Factories", m_factories.size());
  $_TRACE("Dylib::Registry: Installed {0} Crates", Dylib::Registry::total());

  // declare globals as accessible to roots now
  m_roots->bind([this](Each &yield) {
    for (auto &value : m_values | std::views::values) yield(value);
    for (auto &value : m_internal | std::views::values) yield(value);
  });
}

//  PUBLIC METHODS  //

Talos::Function::Native
Talos::Globals::Service::internal(Runtime::Isolate *isolate, const $::String::View &name, Function::Callback callback) {
  return internal<Function::Native>(isolate, name, [name, callback](Runtime::Isolate *isolate) {
    return isolate->create<Function::Native>(callback, name);
  });
}
