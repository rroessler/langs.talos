/// Talos Modules
#include "talos/toolchain/compile.hpp"
#include "talos/bytecode/compiler.hpp"
#include "talos/runtime/container.hpp"

//  PUBLIC METHODS  //

$::Ptr::Unique<Talos::Linker::Arena> Talos::Toolchain::compile(
    const Syntax::Tree* syntax, const Variable::Captures* captures) {
    return Bytecode::Compiler().process(syntax, captures);
}
