/// Builtin Includes
#include "talos/builtins/_inline/builtins.ipp"

/// Type Includes
#include "talos/type/_inline/type.ipp"

/// Forward Declarations
$_FWD(Talos::Builtins, using TN = Type::New)

//  PRIVATE METHODS  //

void Talos::Builtins::Wrapper<Talos::Builtins::Custom::Debug>::m_typedefs(Type::World *globals) {
  // prepare the fields to be used
  auto fields = $::Map::Record<Type::Entity>();

  // bind all the underlying fields to be used now
#define TALOS_XX_FIELDS_DEFINE(N, ...) fields.emplace(#N, TN::variadic(TN::none()));
#include "talos/builtins/debug/_defines/fields.def"
#undef TALOS_XX_FIELDS_DEFINE

  // expose the "Debug" protocol only as a value
  globals->values().declare(name(), TN::interface(name(), fields));
}
