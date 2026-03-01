/// Forge Modules
#include "forge/toolchain/compile.hpp"
#include "forge/bytecode/compiler.hpp"
#include "forge/runtime/container.hpp"

//  PUBLIC METHODS  //

$::Ptr::Unique<Forge::Linker::Arena> Forge::Toolchain::compile(
    const Syntax::Tree* syntax, const Variable::Captures* captures) {
    return Bytecode::Compiler().process(syntax, captures);
}
