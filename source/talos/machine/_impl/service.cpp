/// Talos Modules
#include "talos/machine/service.hpp"
#include "talos/machine/builder.hpp"
#include "talos/machine/visitor.hpp"
#include "talos/runtime/container.hpp"
#include "talos/runtime/isolate.hpp"

//  CONSTRUCTORS  //

Talos::Machine::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Talos::Machine::Service::Service(XI::Container* services) : m_services(services) {}

//  PUBLIC METHODS  //

bool Talos::Machine::Service::verify(Function::Closure closure) const noexcept { return verify(closure.info()); }
bool Talos::Machine::Service::verify(const Function::Info* info) const noexcept {
    auto jitless = m_services->get<Runtime::Options>()->flags.jitless;
    return !jitless && info->locals() <= XASM::Constants::REGISTERS;
}

Talos::Function::Dynamic Talos::Machine::Service::compile(Runtime::Isolate* isolate, Function::Closure closure) {
    return verify(closure) ? compile(isolate, closure.info(), closure.context()) : closure;
}

Talos::Function::Dynamic Talos::Machine::Service::compile(Runtime::Isolate* isolate, const Function::Info* info) {
    return compile(isolate, info, Value::Void());
}

Talos::Function::Dynamic Talos::Machine::Service::compile(
    Runtime::Isolate* isolate, const Function::Info* info, Value::Any context) {
    // for now we can only compile one item at a time
    $_UNUSED $_AUTO = $::Lock::guard(m_mutex);

    // prepare a compilation scope to be used
    auto* options = m_services->get<Runtime::Options>();
    auto compiler = m_context.scope<Callback>(options->dump.machine);

    // construct a new callee information to be used now
    auto* callee = m_callees.emplace($::New().unique<Info>(info)).first->get();

    $_PP_SCOPE() {
        // initialize the scoping to be used now
        auto builder = m_services->get<Builder>(callee, &compiler);

        // get the underlying bytecode to be converted
        auto bytecode = info->buffer();
        auto labels = bytecode.size();
        auto offset = bytecode.address();

        // prepare the width to be used now
        auto width = sizeof(Bytecode::Instruction::Encoded);

        // reserve the total labels now to be used
        for (size_t ii = 0; ii < (labels / width); ++ii) builder->labels.emplace_back(compiler->new_label());

        // iterate over the bytecode to be transformed
        for (size_t ii = 0; ii < labels; ii += width) {
            auto* instruction = std::bit_cast<Bytecode::Instruction*>(offset + ii);
            builder->emitter.header("{0}", *instruction);  // show the bytecode here
            compiler->bind(builder->emitter.label(ii));    // bind the current label
            Visitor::accept(builder.get(), instruction);   // and attempt compiling
        }
    }

    // finish off the resulting instance
    callee->callback() = compiler->finish();

    // show logging results if necessary
    if ($_UNLIKELY(options->dump.machine)) m_dump(info);

    // and construct the resulting native function
    return isolate->create<Function::Jitted>(callee, context);
}

//  PRIVATE METHODS  //

void Talos::Machine::Service::m_dump(const Function::Info* info) const noexcept {
    // show the baseline dump details now
    $::IO::eprintln("\n===== Assembly Dump '{0}' =====\n", $::Path::relative(info->resource().body()).string());

    // and attempt showing the necessary output now
    if (auto content = m_context.content(); content.size()) $::IO::eprintln(content);
}
