/// Talos Modules
#include "talos/forward/string.hpp"
#include "talos/machine/builder.hpp"
#include "talos/machine/template.hpp"
#include "talos/runtime/isolate.hpp"
#include "talos/string/literal.hpp"
#include "talos/value/boolean.hpp"

/// Forward Declarations
$_FWD(void expose(Reference, bool), Talos::Machine::Dispatch)
$_FWD(uint64_t validate(Reference), Talos::Machine::Dispatch)
$_FWD(uint64_t truthiness(Reference), Talos::Machine::Dispatch)
$_FWD(Reference argv(const Function::Arguments*, size_t), Talos::Machine::Dispatch)
$_FWD(Reference string(Runtime::Isolate*, const String::Intern*), Talos::Machine::Dispatch)

//  MACROS  //

/// @brief These are some helper macros.
#define __ee__
#define __tm__ Template::
#define __cc__ m_builder->compiler->
#define __iv__(V) Talos::Machine::Immediate(std::bit_cast<Talos::Machine::Reference>(V))

//  PUBLIC METHODS  //

Talos::Machine::Memory Talos::Machine::Emitter::memory(const Register& vreg, size_t offset) const noexcept {
    return asmjit::ujit::mem_ptr(vreg, offset);
}

Talos::Machine::Immediate Talos::Machine::Emitter::immediate(Value::Any value) const noexcept { return __iv__(value); }

Talos::Machine::Register Talos::Machine::Emitter::intern(const Bytecode::Index& index) noexcept {
    auto ix = __cc__ new_gp64("@ix");
    __cc__ mov(ix, m_intern(index));
    return ix;  // and return intern
}

Talos::Machine::Register Talos::Machine::Emitter::string(const Bytecode::Index& index) noexcept {
    return __ee__ string(m_intern(index));
}

Talos::Machine::Register Talos::Machine::Emitter::string(const String::Intern* intern) noexcept {
    auto dx = __cc__ new_gp64("@dx");
    return __ee__ string(dx, intern), dx;
}

Talos::Machine::Reference Talos::Machine::Dispatch::string(Runtime::Isolate* isolate, const String::Intern* intern) {
    return String::Dynamic(isolate, *intern).pointer();
}

void Talos::Machine::Emitter::string(const Register& vreg, const Bytecode::Index& index) noexcept {
    __ee__ string(vreg, m_intern(index));
}

void Talos::Machine::Emitter::string(const Register& vreg, const String::Intern* intern) noexcept {
    // check if the intern is a small-string at all (removes "call" and reduces "mov" instructions)
    if (intern->bytes() <= String::Limits::SMALL) return __ee__ load(vreg, String::Small(intern->view()));

    // move the intern into a register
    auto ix = __cc__ new_gpz("@ix");
    __cc__ mov(ix, intern);

    // and dispatch the necessary callback
    __ee__ invoke(Dispatch::string, vreg, m_builder->isolate, ix);
}

void Talos::Machine::Emitter::string(const Bytecode::Register& vreg, const Bytecode::Index& index) noexcept {
    __ee__ string(__ee__ resolve(vreg), index);
}

void Talos::Machine::Emitter::string(const Bytecode::Register& vreg, const String::Intern* intern) noexcept {
    __ee__ string(__ee__ resolve(vreg), intern);
}

Talos::Machine::Register Talos::Machine::Emitter::resolve(const Engine::Register& vreg) {
    // stop early if we have the accumulator register to be returned
    if (vreg.accumulator()) return m_builder->result;

    // check if we have a local value instead of an argument
    auto local = vreg.encode() > m_builder->info->argmax();
    if (local) return m_builder->registers.allocate(vreg);

    // otherwise stop early if the register has already been bound
    if (m_builder->registers.bound(vreg)) return m_builder->registers.resolve(vreg);

    // since we have an unbounded argument, we must bind
    auto dst = m_builder->registers.allocate(vreg);
    return __ee__ m_argv(dst, vreg.encode() - 1), dst;
}

Talos::Machine::Label Talos::Machine::Emitter::label(size_t offset) {
    return m_builder->labels[(m_offset = offset) / sizeof(Bytecode::Instruction::Encoded)];
}

Talos::Machine::Label Talos::Machine::Emitter::label(const Bytecode::Index& index) {
    // get the current offset to jump now
    auto* arena = m_builder->info->arena();
    auto constant = arena->constants[index];
    size_t jump = constant.as<Number::Tagged>();

    // get the necessary offset now and convert that to a suitable label
    auto offset = m_offset + jump + sizeof(Bytecode::Instruction::Encoded);
    return m_builder->labels[offset / sizeof(Bytecode::Instruction::Encoded)];
}

uint64_t Talos::Machine::Dispatch::truthiness(Reference target) { return Value::Any(target).truthiness(); }

Talos::Machine::Label Talos::Machine::Emitter::truthy(const Engine::Register& vreg) {
    return __ee__ truthy(__ee__ resolve(vreg));
}

Talos::Machine::Label Talos::Machine::Emitter::truthy(const Register& vreg) {
    auto label = __cc__ new_label();  // prep
    return __ee__ truthy(label, vreg), label;
}

void Talos::Machine::Emitter::truthy(const Label& label, const Engine::Register& vreg) {
    __ee__ truthy(label, __ee__ resolve(vreg));
}

void Talos::Machine::Emitter::truthy(const Label& label, const Register& vreg) {
    // prepare the truthiness register
    auto tx = __cc__ new_gp64("@tx");

    // attempt the invocation now to be conducted
    __ee__ invoke(Dispatch::truthiness, tx, vreg);

    // and jump if the value is truthy at all
    __cc__ j(label, asmjit::ujit::test_nz(tx));
}

Talos::Machine::Label Talos::Machine::Emitter::falsey(const Engine::Register& vreg) {
    return __ee__ falsey(__ee__ resolve(vreg));
}

Talos::Machine::Label Talos::Machine::Emitter::falsey(const Register& vreg) {
    auto label = __cc__ new_label();  // prep
    return __ee__ falsey(label, vreg), label;
}

void Talos::Machine::Emitter::falsey(const Label& label, const Engine::Register& vreg) {
    __ee__ falsey(label, __ee__ resolve(vreg));
}

void Talos::Machine::Emitter::falsey(const Label& label, const Register& vreg) {
    // prepare the truthiness register
    auto tx = __cc__ new_gp64("@tx");

    // attempt the invocation now to be conducted
    __ee__ invoke(Dispatch::truthiness, tx, vreg);

    // and jump if the value is truthy at all
    __cc__ j(label, asmjit::ujit::test_z(tx));
}

void Talos::Machine::Emitter::load(Value::Any value) { __ee__ load(m_builder->result, value); }
void Talos::Machine::Emitter::load(const Engine::Register& vreg, Value::Any value) {
    __ee__ load(__ee__ resolve(vreg), value);
}

void Talos::Machine::Emitter::load(const Register& vreg, Value::Any value) {
    __cc__ mov(vreg, __ee__ immediate(value));  // move the value now
}

void Talos::Machine::Emitter::move(const Register& dst, const Register& src) { __cc__ mov(dst, src); }
void Talos::Machine::Emitter::move(const Register& dst, const Engine::Register& src) {
    __ee__ move(dst, __ee__ resolve(src));
}

void Talos::Machine::Emitter::move(const Engine::Register& dst, const Register& src) {
    __ee__ move(__ee__ resolve(dst), src);
}

void Talos::Machine::Emitter::move(const Engine::Register& dst, const Engine::Register& src) {
    __ee__ move(__ee__ resolve(dst), __ee__ resolve(src));
}

void Talos::Machine::Emitter::vtof(const Label& label, const Double& xmm, const Register& dx) {
    __cc__ j(label, asmjit::ujit::bt_nz(dx, 0)), __cc__ s_mov_u64(xmm, dx);
}

void Talos::Machine::Emitter::vtof(
    const Label& label, const Double& xmm, const Register& dx, const Engine::Register& dv) {
    __ee__ move(dx, dv), __ee__ vtof(label, xmm, dx);
}

void Talos::Machine::Emitter::ftov(const Double& xmm, const Register& dx) {
    __cc__ s_mov_u64(dx, xmm), __cc__ and_(dx, dx, ~Pointer::Mask::NUM);
}

void Talos::Machine::Emitter::expose(const Register& vreg, bool pretty) {
    __ee__ invoke(Dispatch::expose, vreg, pretty);
}

void Talos::Machine::Emitter::expose(const Engine::Register& vreg, bool pretty) {
    __ee__ expose(__ee__ resolve(vreg), pretty);
}

void Talos::Machine::Dispatch::expose(Reference value, bool pretty) {
    if (pretty) $::IO::eprintln(Value::Any(value));
    else $::IO::eprintln(Pointer::Traits(value));
}

void Talos::Machine::Emitter::parameters() { parameters({}, {}); }
void Talos::Machine::Emitter::parameters(const Engine::Register& self) { parameters(self, {}); }
void Talos::Machine::Emitter::parameters(const Engine::Register::Span& span) { parameters({}, span); }
void Talos::Machine::Emitter::parameters(const Engine::Register& self, const Engine::Register::Span& span) {
    // prepare a temporary register to be used
    auto tx = __cc__ new_gp64("@tx");

    // prepare the size of the incoming arguments to be used
    __ee__ load(tx, Number::Tagged(span.count()));
    __cc__ store_u64(__ee__ memory(m_builder->stack), tx);

    // upload the incoming self value as well
    if (!self.nowhere()) __ee__ move(tx, self);
    else __ee__ load(tx, Value::Void());

    // set the incoming self value now
    __cc__ store_u64(__ee__ memory(m_builder->stack, Function::Offset::ARGS_SELF * sizeof(Value::Any)), tx);

    // finally push all the incoming arguments as well
    for (size_t ii = 0; ii < span.count(); ++ii) {
        auto offset = sizeof(Value::Any) * (ii + Function::Offset::ARGS_DATA);  // prepare offset
        __cc__ store_u64(__ee__ memory(m_builder->stack, offset), __ee__ resolve(span.first() + ii));
    }

    // update the current locals count to be used
    auto& locals = m_builder->info->locals();
    locals = std::max<size_t>(locals, span.count());
}

void Talos::Machine::Emitter::returns() { __ee__ returns(m_builder->result); }
void Talos::Machine::Emitter::returns(Value::Any value) { __ee__ returns(m_builder->result, value); }
void Talos::Machine::Emitter::returns(const Register& vreg) { __cc__ ret(vreg); }
void Talos::Machine::Emitter::returns(const Register& vreg, Value::Any value) {
    __ee__ load(vreg, value), __ee__ returns(vreg);
}

void Talos::Machine::Emitter::interrupt() { __cc__ j(m_builder->interrupt); }

void Talos::Machine::Emitter::interrupt(const Register& condition) {
    __cc__ j(m_builder->interrupt, asmjit::ujit::cmp_ne(condition, 0));
}

uint64_t Talos::Machine::Dispatch::validate(Reference target) { return Pointer::Traits(target).okay(); }

void Talos::Machine::Emitter::validate(const Engine::Register& vreg, bool fast) {
    __ee__ validate(__ee__ resolve(vreg), fast);
}

void Talos::Machine::Emitter::validate(const Register& vreg, bool fast) {
    // fast checks query "Value::Failure" instead
    if (fast) return __cc__ j(m_builder->panic, asmjit::ujit::cmp_eq(vreg, __iv__(Value::Failure())));

    // prepare a temporary working register
    auto tx = __cc__ new_gp64("@tx");

    // cache the resulting condition now
    __ee__ invoke(Dispatch::validate, tx, vreg);

    // test whether or not we have the valid bits
    __cc__ j(m_builder->panic, asmjit::ujit::test_z(tx));
}

Talos::Machine::Reference Talos::Machine::Dispatch::argv(const Function::Arguments* args, size_t offset) {
    return args->at(offset, Value::Void()).pointer();
}

//  PRIVATE METHODS  //

Talos::Machine::Compiler* Talos::Machine::Emitter::m_compiler() noexcept { return m_builder->compiler; }

const Talos::String::Intern* Talos::Machine::Emitter::m_intern(const Bytecode::Index& index) const noexcept {
    return &m_builder->info->arena()->strings[index];
}

void Talos::Machine::Emitter::m_argv(const Register& vreg, size_t offset) {
    __ee__ invoke(Dispatch::argv, vreg, m_builder->argv, offset);
}

void Talos::Machine::Emitter::m_header(const $::String::View& message) { __cc__ comment(message.data()); }
void Talos::Machine::Emitter::m_comment(const $::String::View& message) {
    __cc__ cc->set_inline_comment(message.data());
}
