/// Talos Modules
#include "talos/bytecode/compiler.hpp"
#include "talos/bundle/service.hpp"
#include "talos/bytecode/visitor.hpp"
#include "talos/module/service.hpp"
#include "talos/runtime/container.hpp"
#include "talos/syntax/tree.hpp"

//  CONSTRUCTORS  //

Talos::Bytecode::Compiler::Compiler() : Compiler($::Global::get<Runtime::Container>()) {}

Talos::Bytecode::Compiler::Compiler(XI::Container* services) : m_services(services) {
    m_optimizer = services->get<Optimizer>(m_labels.get());
    m_assembler = services->get<Assembler>();  // prebuild
}

//  PUBLIC METHODS  //

Talos::Bytecode::Index Talos::Bytecode::Compiler::constant(Value::Any value) {
    auto& constants = m_arena->constants;
    auto begin = constants.cbegin(), end = constants.cend();
    auto iter = std::ranges::find(constants, value);
    if (iter != end) return std::ranges::distance(begin, iter);
    return constants.emplace_back(value), constants.size() - 1;
}

Talos::Bytecode::Index Talos::Bytecode::Compiler::string(const $::String::View& buffer) {
    auto& table = m_arena->strings;
    auto symbol = Value::Symbol(buffer);
    auto begin = table.cbegin(), end = table.cend();

    // attempt finding a valid result now
    for (auto iter = begin; iter != end; ++iter) {
        if (iter->symbol() == symbol) return std::distance(begin, iter);
    }

    // failed to find, so we want to emplace a value now
    return table.emplace_back(String::Intern(buffer, symbol)), table.size() - 1;
}

Talos::Bytecode::Index Talos::Bytecode::Compiler::symbol(const $::String::View& buffer) {
    return constant(m_arena->strings.at(string(buffer)).symbol());
}

void Talos::Bytecode::Compiler::import(Destination sink, const $::String::View& buffer) {
    // do a regular import if we are dynamically running out program
    if (!bundled()) return emit<Syllable::MODULE_IMPORT>(sink, string(buffer));

    // otherwise we want to resolve the resource now
    auto result = m_services->get<Import::Service>()->resolve(buffer, resource().body());

    // if this failed, then declare a bytecode error now
    if (!result.has_value()) return panic(8000000, result.error());

    // otherwise check if the resource is file-based or not
    if (result->scheme() != $::URI::Scheme::FILE) return emit<Syllable::MODULE_IMPORT>(sink, string(buffer));

    // since a valid file, then we should emit the import as an archive
    auto resource = $::URI::Buffer("arch", result->relative());
    emit<Syllable::MODULE_IMPORT>(sink, string(resource.view()));
}

void Talos::Bytecode::Compiler::lower(const Syntax::Node* node, Destination sink) { Visitor::visit(node, this, sink); }

void Talos::Bytecode::Compiler::preamble(const Syntax::Preamble* preamble, Register value) {
    // update our value with the available decorators/attributes
    for (const auto& attribute : preamble->attributes()) lower(attribute, value);
    for (const auto& decorator : preamble->decorators()) lower(decorator, value);

    // and ensure we expose the value as necessary now
    expose(preamble, value);
}

void Talos::Bytecode::Compiler::expose(const Syntax::Declaration* preamble, Register value) {
    if (!preamble->modifiers().test(Variable::Flag::EXPORT)) return;
    emit<Syllable::MODULE_EXPORT>(value, string(preamble->name()));
}

Talos::Bytecode::Index Talos::Bytecode::Compiler::enqueue(const Syntax::Lambda* function) const {
    return m_queue->enqueue(function, m_request ? m_request->m_variables : nullptr);
}

Talos::Bytecode::Index Talos::Bytecode::Compiler::enqueue(const Syntax::Class* prototype) const {
    return m_queue->enqueue(prototype, m_request ? m_request->m_variables : nullptr);
}

void Talos::Bytecode::Compiler::load(const $::String::View& name, Variable::Extent extent, Destination sink) {
    // ignore if there is no valid output destination
    if (sink.nowhere()) return;

    // handle based on the incoming extent value
    switch (extent) {
        case Variable::Extent::LOCAL: {
            auto leaked = variables()->leaked(name);
            auto vreg = variables()->resolve(name);

            if (leaked) emit<Syllable::LOAD_CONTEXT>(sink, vreg);
            else if (vreg != sink) emit<Syllable::REG_MOVE>(sink, vreg);
        } break;

        case Variable::Extent::UPVALUE: {
            auto upvalue = variables()->upvalue(name);
            $_ASSERT(!upvalue.slot.nowhere(), "Invalid upvalue lookup");
            if (!upvalue.depth) emit<Syllable::LOAD_CONTEXT>(sink, upvalue.slot);
            else emit<Syllable::LOAD_UPVALUE>(sink, upvalue.slot, upvalue.depth);
        } break;

        case Variable::Extent::GLOBAL: emit<Syllable::LOAD_GLOBAL>(sink, constant(Value::Symbol(name))); break;
        default: $_ABORT("Cannot load leaked variables");  // ensure that our extent is invalid here since unknown
    }
}

void Talos::Bytecode::Compiler::store(const $::String::View& name, Variable::Extent extent, Register value) {
    // prepare the source register to be used now
    if (value.nowhere()) value = Accumulator();

    // handle based on the incoming extent
    switch (extent) {
        case Variable::Extent::LOCAL: {
            auto leaked = variables()->leaked(name);
            auto vreg = variables()->resolve(name);

            if (leaked) emit<Syllable::STORE_CONTEXT>(vreg, value);
            else if (vreg != value) emit<Syllable::REG_MOVE>(vreg, value);
        } break;

        case Variable::Extent::UPVALUE: {
            auto upvalue = variables()->upvalue(name);
            $_ASSERT(!upvalue.slot.nowhere(), "Invalid upvalue lookup");
            if (!upvalue.depth) emit<Syllable::STORE_CONTEXT>(upvalue.slot, value);
            else emit<Syllable::STORE_UPVALUE>(upvalue.slot, value, upvalue.depth);
        } break;

        case Variable::Extent::GLOBAL: panic("Cannot modify global variable '{0}'", name); break;
        default: $_ABORT("Cannot load leaked variables");  // ensure that our extent is valid here
    }
}

$::Ptr::Unique<Talos::Linker::Arena> Talos::Bytecode::Compiler::process(
    const Syntax::Tree* syntax, const Variable::Captures* captures) {
    // prepare the base-line details to be used for compilation
    m_captures = captures, m_arena = $::New().unique<Linker::Arena>(), lower(syntax);

    // update the arenas associated resource
    m_arena->resource = syntax->resource();

    // process the incoming routine queue now
    while (m_queue->size()) {
        auto request = m_queue->dequeue();
        m_function(m_request = request.get());
    }

    // and return the final result after cleanup
    return m_captures = nullptr, m_request = nullptr, std::move(m_arena);
}

//  PRIVATE METHODS  //

bool Talos::Bytecode::Compiler::m_bundled() const noexcept { return m_services->exists<Bundle::Service>(); }

void Talos::Bytecode::Compiler::m_emit(const Instruction& instruction) {
    // get the details to emit the instruction
    auto* block = m_labels->head();
    auto branches = instruction.branches();

    // always ensure a label for the first instruction
    if (block->empty()) m_labels->patch();

    // push the instruction onto the block now and onto the source-mapping
    auto pointer = $::New().unique<Instruction>(instruction);
    auto* reference = block->instructions().emplace_back(std::move(pointer)).get();
    if (m_traces.size()) m_assembler->m_positions.set(reference, m_traces.top());

    // construct a new block if the instruction branches
    if (branches) m_labels->scope();
}

void Talos::Bytecode::Compiler::m_function(Request* request) {
    // construct a new shared-function to be used now
    auto* info = m_arena->functions.emplace_back($::New().unique<Function::Info>(m_arena.get())).get();

    // pull out some of the request details to be used
    const auto* function = request->m_constructor;

    // pull out the spread value as well to be compared
    const auto* spread = function->spread();

    // update the underlying shared information
    info->shared()->arity = function->arity();
    info->shared()->adicity = function->adicity();

    // emplace the information onto the request now
    request->m_routine = $::New().unique<Routine>(info->shared());

    // prepare a new labels scoping to be used
    m_labels->clear(), m_labels->scope();

    // pull out the necessary parameters now
    auto parameters = function->parameters() ? function->parameters()->list() : std::vector<Syntax::Variable*>();

    // emit all the necessary parameters now for the function
    for (const auto& [ii, parameter] : $::Each(parameters)) {
        if (m_parameter(parameter, spread)) info->shared()->vargs = ii;
    }

    // check if the function-body is a block or not
    Destination destination = request->m_body->is<Syntax::Block>() ? Register() : Accumulator();

    // prepare the function body to be used now
    auto returns = m_labels->m_returns.emplace(m_labels->reserve());
    lower(request->m_body, destination), m_labels->m_returns.pop(), m_labels->patch(returns);

    // and emit an empty return handler just-in-case
    if (destination.nowhere()) emit<Syllable::LOAD_VOID>();
    emit<Syllable::EXEC_RETURN>();  // push a final return

    // attempt optimizing the function now as necessary
    m_optimizer->process(request->routine());

    // and update our final details for the routine now
    info->shared()->locals = registers()->maximum();

    // finally attempt assembling the resulting buffer to be used
    info->buffer() = m_assembler->process(request->routine(), m_arena.get());
}

bool Talos::Bytecode::Compiler::m_parameter(const Syntax::Variable* parameter, const Syntax::Variable* spread) {
    // prepare the parameter details to be handled
    auto [dest, leaked] = declare(parameter);
    auto* initializer = parameter->initializer();
    auto treg = leaked ? registers()->allocate() : dest;

    // update the initializer if necessary
    if (initializer) {
        // prepare the skip handler to be used
        auto skip = m_labels->reserve();

        // we test the initial register if assigned
        emit<Syllable::JUMP_FILLED>(skip, treg);
        lower(initializer, treg), m_labels->patch(skip);
    }

    // and move into a suitable position if necessary
    if (leaked) emit<Syllable::STORE_CONTEXT>(dest, treg);

    // declare if the spread is same as the parameter
    return parameter == spread;
}
