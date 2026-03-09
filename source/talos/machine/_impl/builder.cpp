/// Talos Modules
#include "talos/machine/builder.hpp"
#include "talos/machine/frame.hpp"
#include "talos/machine/signature.hpp"
#include "talos/runtime/isolate.hpp"
#include "talos/string/small.hpp"

/// Forward Declarations
$_FWD(Talos::Machine::Dispatch, void cancel(Runtime::Isolate*))

//  CONSTRUCTORS  //

Talos::Machine::Builder::Builder(Info* info, Compiler* compiler) :
    info(info), compiler(compiler), emitter(this), registers(compiler) {
    // construct the underlying function
    auto* node = Signature(compiler);

    // bind all the incoming base registers to be used
    isolate = compiler->new_gpz("@runtime.isolate/ptr");
    stack = compiler->new_gpz("@runtime.stack/ptr");
    frame = compiler->new_gpz("@runtime.frame/ptr");
    argv = compiler->new_gpz("@runtime.argv/ptr");
    envp = compiler->new_gpz("@runtime.envp/ptr");

    // register the incoming accumulator as well now
    result = registers.allocate(Engine::Accumulator());

    // bind all the incoming labels necessary
    panic = compiler->new_named_label("_panic");
    interrupt = compiler->new_named_label("_interrupt");

    // declare that we are setting up the function
    emitter.header("-- Function Prolog --\n");

    // then we want to bind our arguments now
    node->set_arg(0, isolate);
    node->set_arg(1, frame);

    // preload the stack pointer for references
    compiler->load_u64(frame, emitter.memory(frame));

    // ensure we pre-load the incoming context, arguments and stack
    compiler->load_u64(envp, emitter.memory(frame, Offset::STK_ENVP * sizeof(Value::Any)));
    compiler->load_u64(argv, emitter.memory(frame, Offset::STK_DATA * sizeof(Value::Any)));
    compiler->load_u64(stack, emitter.memory(frame, Offset::STK_PASS * sizeof(Value::Any)));

    // declare that we are now in the user-code
    emitter.header("-- Function Code --");
}

Talos::Machine::Builder::~Builder() {
    // show that we are emitting exceptions
    emitter.header("--  Function Exceptions --\n");

    // bind the fallback return condition
    emitter.returns(Value::Void());

    // bind the optimizable interrupt condition
    compiler->bind(interrupt), emitter.invoke(Dispatch::cancel, isolate);

    // bind the optimizable panic condition
    compiler->bind(panic), emitter.returns(Value::Failure());

    // and annotate the incoming function epilog
    emitter.header("-- Function Epilog --\n");
}

//  PUBLIC METHODS  //

void Talos::Machine::Dispatch::cancel(Runtime::Isolate* isolate) { isolate->panic(9000200); }
