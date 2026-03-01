/// Forge Modules
#include "forge/type/lattice.hpp"
#include "forge/type/tagged.hpp"

//  CONSTRUCTORS  //

Forge::Type::Lattice::Lattice(const Erased& type) : Lattice(type ? type->lattice() : Fact::ANY_TYPE) {}
