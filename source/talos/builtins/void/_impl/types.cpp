/// Builtin Includes
#include "talos/builtins/_inline/builtins.ipp"

/// Type Includes
#include "talos/type/_inline/type.ipp"

/// Forward Definitions
$_FWD(Talos::Builtins, using TN = Type::New)

//  PRIVATE METHODS  //

void Talos::Builtins::Wrapper<Talos::Value::Void>::m_typedefs(Type::World *globals) {
  globals->types().declare(name(), TN::none());
  globals->values().declare(name(), TN::none());
}
