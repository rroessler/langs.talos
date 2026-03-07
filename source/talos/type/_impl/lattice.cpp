/// Talos Modules
#include "talos/type/lattice.hpp"
#include "talos/type/tagged.hpp"

//  CONSTRUCTORS  //

Talos::Type::Lattice::Lattice(const Erased& type) : Lattice(type ? type->lattice() : Fact::ANY_TYPE) {}
