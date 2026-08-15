/// Talos Modules
#include "talos/toolchain/compile.hpp"
#include "talos/bytecode/compiler.hpp"

//  PUBLIC METHODS  //

$::Unique::Pointer<Talos::Image::Arena> Talos::Toolchain::compile(const Syntax::Tree *syntax, XI::Container *services) {
  return services->get<Bytecode::Compiler>()->process(syntax);
}
