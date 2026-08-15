/// Builtin Includes
#include "talos/builtins/_inline/builtins.ipp"

/// Type Includes
#include "talos/type/_inline/type.ipp"

/// Forward Definitions
$_FWD(Talos::Builtins, using TN = Type::New)

//  PRIVATE METHODS  //

void Talos::Builtins::Wrapper<Talos::Builtins::Custom::Utility>::m_typedefs(Type::World *globals) {
  // prepare the baseline intrinsic types to be used
  globals->types().declare("Any", TN::any());
  globals->types().declare("Never", TN::never());

  // define the generic "Maybe" typing using a required generic
  auto M = Talos::Builtins::TN::constraint("T", TN::any());
  globals->types().declare("Maybe", TN::generic(TN::maybe(M), M));

  // define the generic "Record" typing using a suitable generic
  auto R = Talos::Builtins::TN::constraint("T", TN::any());
  globals->types().declare("Record", TN::generic(TN::record(R), R));
}
