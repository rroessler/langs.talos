/// Forge Modules
#include "forge/machine/template.hpp"
#include "forge/engine/dispatch.hpp"
#include "forge/operator/traits.hpp"

/// Inline Modules
#include "forge/machine/_inline/macros.ipp"
#include "forge/value/_inline/value.ipp"

/// Forward Declarations
$_FWD(class Binary, Forge::Machine)
$_FWD(class Compare, Forge::Machine)

$_FWD(Reference lor(Reference, Reference), Forge::Machine::Dispatch)
$_FWD(Reference land(Reference, Reference), Forge::Machine::Dispatch)

$_FWD(Reference spawn(Runtime::Isolate *, Reference, Value::Any *), Forge::Machine::Dispatch)
$_FWD(Reference invoke(Runtime::Isolate *, Reference, Value::Any *), Forge::Machine::Dispatch)
$_FWD(Reference recall(Runtime::Isolate *, const Machine::Info *, Value::Any *), Forge::Machine::Dispatch)

//  TYPEDEFS  //

/// @brief Prepare the binary handler.
class Forge::Machine::Binary {
    //  TYPEDEFS  //

    /// @brief Underlying qualified details.
    template <Bytecode::Syllable S>
    using Qualified = Bytecode::Qualified<S>;

   protected:
    //  PROPERTIES  //

    Register m_dx = {};  // Result register.
    Register m_ax = {};  // Alpha register.
    Register m_bx = {};  // Beta register.

    Double m_axv = {};  // Vector register alpha.
    Double m_bxv = {};  // Vector register beta.

    Engine::Register m_dv = {};  // Result bytecode register.
    Engine::Register m_av = {};  // Alpha bytecode register.

    /// @brief The bail label available.
    Label m_bail = {};

    //  CONSTRUCTORS  //

    /// @brief The underlying state to encompase.
    constexpr Binary(Builder *builder = nullptr) {
        // get the incoming registers now
        m_dx = __cc__ new_gp64("@dx");
        m_ax = __cc__ new_gp64("@ax");
        m_bx = __cc__ new_gp64("@bx");

        // prepare some necessary registers now
        m_axv = __cc__ new_vec128("@axv");
        m_bxv = __cc__ new_vec128("@bxv");

        // prepare the labels now
        m_bail = __cc__ new_label();
    }

    /// @brief The underlying state to encompase.
    constexpr Binary(Builder *builder, Qualified<Bytecode::Syllable::BINOP_TPL> *instruction) : Binary(builder) {
        m_dv = instruction->get<0>();  // bind result
        m_av = instruction->get<1>();  // and alpha
    }

    /// @brief The underlying state to encompase.
    constexpr Binary(Builder *builder, Qualified<Bytecode::Syllable::BINOP_TPLI> *instruction) : Binary(builder) {
        m_dv = instruction->get<0>();  // bind result
        m_av = instruction->get<1>();  // and alpha
    }

   public:
    //  PUBLIC METHODS  //

    /// @brief Handles slow comparison operations.
    static inline void slow(Builder *builder, Operator::Kind kind, Bytecode::Instruction *instruction) noexcept {
        auto *qualified = static_cast<Qualified<Bytecode::Syllable::BINOP_TPL> *>(instruction);
        Binary(builder, qualified).m_generate(builder, kind, qualified->get<2>());
    }

    /// @brief Handles fast comparison operations.
    static inline void fast(Builder *builder, Operator::Kind kind, Bytecode::Instruction *instruction) noexcept {
        auto *qualified = static_cast<Qualified<Bytecode::Syllable::BINOP_TPLI> *>(instruction);
        Binary(builder, qualified).m_generate(builder, kind, qualified->get<2>());
    }

   protected:
    //  PRIVATE METHODS  //

    /// @brief Handles generating results.
    template <class T>
    inline constexpr void m_generate(Builder *builder, Operator::Kind kind, const T &operand) const noexcept {
        // preload the incoming binary instruction
        m_preload(builder, operand);

        // and attempt applying the result now
        m_apply(builder, kind);
    }

    /// @brief Handles preloading the comparison.
    template <class T>
    inline constexpr void m_preload(Builder *builder, const T &operand) const noexcept {
        // test whether or not the alpha register is valid
        __ee__ vtof(m_bail, m_axv, m_ax, m_av);

        // handle potential bytecode registers
        if constexpr (std::same_as<T, Engine::Register>) __ee__ vtof(m_bail, m_bxv, m_bx, operand);

        // handle potential immediate values
        if constexpr (std::same_as<T, Bytecode::Index>) {
            auto constant = builder->info->arena()->constants[operand];
            __ee__ load(m_bx, constant), __cc__ s_mov_u64(m_bxv, m_bx);
        }
    }

    /// @brief Handles incoming integral operations.
    inline constexpr void m_integral(Builder *builder, Operator::Kind kind) const noexcept {
        // prepare the start of the integral operation
        __cc__ s_cvt_round_f64_to_int(m_ax, m_axv);
        __cc__ s_cvt_round_f64_to_int(m_bx, m_bxv);

        // handle based on the incoming details now
        switch (kind) {
            case Operator::Kind::SHL: __cc__ shl(m_ax, m_ax, m_bx); break;
            case Operator::Kind::SHR: __cc__ shr(m_ax, m_ax, m_bx); break;
            case Operator::Kind::XOR: __cc__ xor_(m_ax, m_ax, m_bx); break;
            case Operator::Kind::BOR: __cc__ or_(m_ax, m_ax, m_bx); break;
            case Operator::Kind::BAND: __cc__ and_(m_ax, m_ax, m_bx); break;
            default: $_ABORT("Unexpected operator '{0}'", Operator::Traits::name(kind));
        }

        // prepare the post-condition of an integral operation
        __cc__ s_cvt_int_to_f64(m_axv, m_ax);
    }

    /// @brief Handles applying the incoming operation.
    virtual inline constexpr void m_apply(Builder *builder, Operator::Kind kind) const noexcept {
        // handle based on the incoming details now
        switch (kind) {
            case Operator::Kind::ADD: __cc__ s_add_f64(m_axv, m_axv, m_bxv); break;
            case Operator::Kind::SUB: __cc__ s_sub_f64(m_axv, m_axv, m_bxv); break;
            case Operator::Kind::MUL: __cc__ s_mul_f64(m_axv, m_axv, m_bxv); break;
            case Operator::Kind::DIV: __cc__ s_div_f64(m_axv, m_axv, m_bxv); break;
            case Operator::Kind::MOD: __cc__ s_mod_f64(m_axv, m_axv, m_bxv); break;

            case Operator::Kind::POW: {
                __ee__ invoke<double (*)(double, double)>(std::pow, m_axv, m_axv, m_bxv);
            } break;

            // handle all incoming integral operations as well
            default: m_integral(builder, kind); break;
        }

        // cast the outgoing float back to a numeric
        __ee__ ftov(m_axv, m_dx);

        // and finally prepare our bail conditions to be used
        __cc__ bind(m_bail), __ee__ move(m_dv, m_dx);
    }
};

/// @brief Prepare the comparison handler.
class Forge::Machine::Compare : public Binary {
    //  TYPEDEFS  //

    /// @brief Underlying qualified details.
    template <Bytecode::Syllable S>
    using Qualified = Bytecode::Qualified<S>;

    //  CONSTRUCTORS  //

    /// @brief Inherit the base constructor.
    using Binary::Binary;

   public:
    //  PUBLIC METHODS  //

    /// @brief Handles slow comparison operations.
    static inline void slow(Builder *builder, Operator::Kind kind, Bytecode::Instruction *instruction) noexcept {
        auto *qualified = static_cast<Qualified<Bytecode::Syllable::BINOP_TPL> *>(instruction);
        Compare(builder, qualified).m_generate(builder, kind, qualified->get<2>());
    }

    /// @brief Handles fast comparison operations.
    static inline void fast(Builder *builder, Operator::Kind kind, Bytecode::Instruction *instruction) noexcept {
        auto *qualified = static_cast<Qualified<Bytecode::Syllable::BINOP_TPLI> *>(instruction);
        Compare(builder, qualified).m_generate(builder, kind, qualified->get<2>());
    }

   protected:
    //  PRIVATE METHODS  //

    /// @brief Handles generating results.
    template <class T>
    inline constexpr void m_generate(Builder *builder, Operator::Kind kind, const T &operand) const noexcept {
        // load the truthy result now
        __ee__ load(m_dx, Value::Boolean(false));

        // preload the incoming binary instruction
        m_preload(builder, operand);

        // and attempt applying the result now
        m_apply(builder, kind);
    }

    /// @brief Handles applying the condition.
    inline constexpr void m_apply(Builder *builder, Operator::Kind kind) const noexcept final {
        // handle based on the incoming condition given
        switch (kind) {
            case Operator::Kind::LT: __cc__ s_cmp_lt_f64(m_axv, m_axv, m_bxv); break;
            case Operator::Kind::GT: __cc__ s_cmp_gt_f64(m_axv, m_axv, m_bxv); break;
            case Operator::Kind::LE: __cc__ s_cmp_le_f64(m_axv, m_axv, m_bxv); break;
            case Operator::Kind::GE: __cc__ s_cmp_ge_f64(m_axv, m_axv, m_bxv); break;
            default: $_ABORT("Unexpected operator '{0}'", Operator::Traits::name(kind));
        }

        __ee__ load(m_bx, Value::Boolean(true));  // preload the conditional value to move
        __cc__ s_mov(m_ax, m_axv), __cc__ cmov(m_dx, m_bx, asmjit::ujit::cmp_ne(m_ax, 0));

        // bind the resulting bail condition now
        __cc__ bind(m_bail), __ee__ move(m_dv, m_dx);
    }
};

//  PUBLIC METHODS  //

Forge::Machine::Reference Forge::Machine::Dispatch::lor(Reference left, Reference right) {
    return Value::Boolean(Value::Any(left).truthiness() || Value::Any(right).truthiness());
}

Forge::Machine::Reference Forge::Machine::Dispatch::land(Reference left, Reference right) {
    return Value::Boolean(Value::Any(left).truthiness() && Value::Any(right).truthiness());
}

Forge::Machine::Reference Forge::Machine::Dispatch::recall(
    Runtime::Isolate *isolate, const Machine::Info *info, Value::Any *span) {
    return Engine::Call::inlined(isolate, info, Template::arguments(span)).pointer();
}

Forge::Machine::Reference Forge::Machine::Dispatch::invoke(
    Runtime::Isolate *isolate, Reference target, Value::Any *span) {
    return Engine::Call::any(isolate, static_cast<Value::Any>(target), Template::arguments(span)).pointer();
}

Forge::Machine::Reference Forge::Machine::Dispatch::spawn(
    Runtime::Isolate *isolate, Reference value, Value::Any *span) {
    // ensure the incoming target is valid
    auto target = static_cast<Value::Any>(value);

    // should have a suitable spawn target given
    if (!target.is<Function::Dynamic>()) return isolate->panic(6000201, target.type_name()).pointer();

    // and construct the future to be used now
    return isolate->create<Async::Future>(target.as<Function::Dynamic>(), Template::arguments(span)).pointer();
}

void Forge::Machine::Template::negate(Builder *builder, Bytecode::Instruction *instruction) {
    // get the underlying qualified instruction to be used
    auto *qualified = static_cast<Bytecode::Qualified<Bytecode::Syllable::UNOP_TPL> *>(instruction);

    // get the underlying details to be used
    auto dv = qualified->get<0>();
    auto tv = qualified->get<1>();

    // get the associated registers as well
    auto dx = __cc__ new_gp64("@dx");

    // preload the incoming inverted value to be used
    __ee__ load(dx, Value::Boolean(true));

    // attempt checking if we have a falsey value
    auto bail = __ee__ falsey(tv);

    // should safely emit the falsey value
    __ee__ load(dx, Value::Boolean(false));

    // and bind the final label now
    __cc__ bind(bail), __ee__ move(dv, dx);
}

void Forge::Machine::Template::unary(Builder *builder, Operator::Kind kind, Bytecode::Instruction *instruction) {
    // check if we have logical negation to be handled instead
    if (kind == Operator::Kind::NOT) return negate(builder, instruction);

    // destructure the incoming instruction
    auto *qualified = static_cast<Bytecode::Qualified<Bytecode::Syllable::UNOP_TPL> *>(instruction);

    // prepare the baseline bytecode registers
    auto dv = qualified->get<0>();
    auto tv = qualified->get<1>();

    // prepare all the incoming items to be used now
    auto dx = __cc__ new_gp64("@dx");
    auto tx = __cc__ new_gp64("@tx");

    // value float register
    auto txv = __cc__ new_vec128("@txv");

    // prepare the bail details as well
    auto bail = __cc__ new_label();

    // test whether or not the alpha register is valid
    __ee__ vtof(bail, txv, tx, tv);

    // apply the incoming operator now
    switch (kind) {
        // can simply negate values as needed
        case Operator::Kind::NEG: __cc__ s_neg_f64(txv, txv); break;

        // inversion requires a little extra handling as an integer
        case Operator::Kind::INV: {
            __cc__ s_cvt_round_f64_to_int(tx, txv);
            __cc__ not_(tx, tx);  // negate result
            __cc__ s_cvt_int_to_f64(txv, tx);
        } break;

        // all unknown operators should follow through here
        default: $_ABORT("Unexpected operator '{0}'", Operator::Traits::name(kind));
    }

    // cast the outgoing float back to a numeric
    __ee__ ftov(txv, dx);

    // and finally prepare our bail conditions to be used
    __cc__ bind(bail), __ee__ move(dv, dx);
}

void Forge::Machine::Template::coalesce(Builder *builder, Bytecode::Instruction *instruction) {
    // get the underlying qualified instruction to be used
    auto *qualified = static_cast<Bytecode::Qualified<Bytecode::Syllable::BINOP_TPL> *>(instruction);

    // get the associated registers as well
    auto dx = __cc__ new_gp64("@dx");
    auto bail = __cc__ new_label();

    // load the incoming values to be used
    __ee__ move(dx, qualified->get<1>());

    // check if the current value is void or not
    __cc__ j(bail, asmjit::ujit::cmp_ne(dx, __iv__(Value::Void())));

    // if we reached here, then we override the output value now
    __ee__ move(dx, qualified->get<2>());

    // bind the label and resolve the destination value
    __cc__ bind(bail), __ee__ move(qualified->get<0>(), dx);
}

void Forge::Machine::Template::logical(Builder *builder, Operator::Kind kind, Bytecode::Instruction *instruction) {
    // get the underlying qualified instruction to be used
    auto *qualified = static_cast<Bytecode::Qualified<Bytecode::Syllable::BINOP_TPL> *>(instruction);

    // get the underlying details to be used
    auto dx = __ee__ resolve(qualified->get<0>());
    auto ax = __ee__ resolve(qualified->get<1>());
    auto bx = __ee__ resolve(qualified->get<2>());

    // and attempt running the logical invocation
    switch (kind) {
        case Operator::Kind::LOR: __ee__ invoke(Dispatch::lor, dx, ax, bx); break;
        case Operator::Kind::LAND: __ee__ invoke(Dispatch::land, dx, ax, bx); break;
        default: $_ABORT("Unexpected operator '{0}'", Operator::Traits::name(kind));
    }
}

void Forge::Machine::Template::equality(Builder *builder, Operator::Kind kind, Bytecode::Instruction *instruction) {
    // get the underlying qualified instruction to be used
    auto *qualified = static_cast<Bytecode::Qualified<Bytecode::Syllable::BINOP_TPL> *>(instruction);

    // get the underlying details to be used
    auto dv = qualified->get<0>();
    auto av = qualified->get<1>();
    auto bv = qualified->get<2>();

    // get the associated registers as well
    auto dx = __cc__ new_gp64("@dx");
    auto ax = __cc__ new_gp64("@ax");
    auto bx = __cc__ new_gp64("@bx");

    // prepare a bail out condition to be used
    auto bail = __cc__ new_label();

    // prepare the baseline result to be used
    __ee__ load(dx, Value::Boolean(true));

    // load the incoming "ax" and "bx" values
    __ee__ move(ax, av), __ee__ move(bx, bv);

    // attempt checking if we have equal values
    switch (kind) {
        case Operator::Kind::EQ: __cc__ j(bail, asmjit::ujit::cmp_eq(ax, bx)); break;
        case Operator::Kind::NE: __cc__ j(bail, asmjit::ujit::cmp_ne(ax, bx)); break;
        default: $_ABORT("Unexpected operator '{0}'", Operator::Traits::name(kind));
    }

    // slow path the false value if the result failed
    __ee__ load(dx, Value::Boolean(false));

    // and bind the final label now
    __cc__ bind(bail), __ee__ move(dv, dx);
}

void Forge::Machine::Template::binary(Builder *builder, Operator::Kind kind, Bytecode::Instruction *instruction) {
    Binary::slow(builder, kind, instruction);
}

void Forge::Machine::Template::binary_i(Builder *builder, Operator::Kind kind, Bytecode::Instruction *instruction) {
    Binary::fast(builder, kind, instruction);
}

void Forge::Machine::Template::compare(Builder *builder, Operator::Kind kind, Bytecode::Instruction *instruction) {
    Compare::slow(builder, kind, instruction);
}

void Forge::Machine::Template::compare_i(Builder *builder, Operator::Kind kind, Bytecode::Instruction *instruction) {
    Compare::fast(builder, kind, instruction);
}

Forge::Machine::Register Forge::Machine::Template::getter(
    Builder *builder, const Engine::Register &tv, const Bytecode::Index &index) {
    return getter(builder, __ee__ resolve(tv), index);
}

Forge::Machine::Register Forge::Machine::Template::getter(
    Builder *builder, const Register &tx, const Bytecode::Index &index) {
    auto dx = __cc__ new_gp64("@dx");  // bind
    return getter(builder, dx, tx, index), dx;
}

void Forge::Machine::Template::getter(
    Builder *builder, const Engine::Register &dv, const Register &tx, const Bytecode::Index &index) {
    getter(builder, __ee__ resolve(dv), tx, index);
}

void Forge::Machine::Template::getter(
    Builder *builder, const Register &dx, const Engine::Register &tv, const Bytecode::Index &index) {
    getter(builder, dx, __ee__ resolve(tv), index);
}

void Forge::Machine::Template::getter(
    Builder *builder, const Engine::Register &dv, const Engine::Register &tv, const Bytecode::Index &index) {
    getter(builder, __ee__ resolve(dv), __ee__ resolve(tv), index);
}

void Forge::Machine::Template::getter(
    Builder *builder, const Register &dx, const Register &tx, const Bytecode::Index &index) {
    // prepare the incoming constant register
    auto cx = __cc__ new_gp64("@cx");

    // attempt loading the constant and then the field
    __ee__ load(cx, builder->info->arena()->constants[index]);
    __ee__ invoke(Engine::Dispatch::getter, dx, builder->isolate, tx, cx);

    // finally post-validate the result was not a failure
    __ee__ validate(dx, Validate::SLOW);
}

//  PRIVATE METHODS  //

void Forge::Machine::Template::recall(
    Builder *builder, const Engine::Register &dv, const Engine::Register::Span &span) {
    recall(builder, __ee__ resolve(dv), span);
}

void Forge::Machine::Template::recall(Builder *builder, const Register &dx, const Engine::Register::Span &span) {
    // ensure we preload the necessary parameters
    __ee__ parameters(span);

    // and attempt an invocation that is required now
    __ee__ invoke(Dispatch::recall, dx, builder->isolate, builder->info, builder->stack);

    // validate the outgoing result is alright
    __ee__ validate(dx, Validate::FAST);
}

void Forge::Machine::Template::invoke(
    Builder *builder, const Engine::Register &dv, const Engine::Register &tv, const Engine::Register::Span &span) {
    invoke(builder, dv, tv, {}, span);
}

void Forge::Machine::Template::invoke(Builder *builder, const Engine::Register &dv, const Engine::Register &tv,
    const Engine::Register &self, const Engine::Register::Span &span) {
    invoke(builder, dv, __ee__ resolve(tv), self, span);
}

void Forge::Machine::Template::invoke(
    Builder *builder, const Engine::Register &dv, const Register &tx, const Engine::Register::Span &span) {
    invoke(builder, dv, tx, {}, span);
}

void Forge::Machine::Template::invoke(Builder *builder, const Engine::Register &dv, const Register &tx,
    const Engine::Register &self, const Engine::Register::Span &span) {
    // prepare a necessary registers to be used
    auto dx = __ee__ resolve(dv);

    // ensure we preload the necessary parameters
    __ee__ parameters(self, span);

    // and attempt an invocation that is required now
    __ee__ invoke(Dispatch::invoke, dx, builder->isolate, tx, builder->stack);

    // validate the outgoing result is alright
    __ee__ validate(dx, Validate::FAST);
}

void Forge::Machine::Template::spawn(
    Builder *builder, const Engine::Register &dv, const Engine::Register &tv, const Engine::Register::Span &span) {
    spawn(builder, dv, tv, {}, span);
}

void Forge::Machine::Template::spawn(Builder *builder, const Engine::Register &dv, const Engine::Register &tv,
    const Engine::Register &self, const Engine::Register::Span &span) {
    spawn(builder, dv, __ee__ resolve(tv), self, span);
}

void Forge::Machine::Template::spawn(
    Builder *builder, const Engine::Register &dv, const Register &tx, const Engine::Register::Span &span) {
    spawn(builder, dv, tx, {}, span);
}

void Forge::Machine::Template::spawn(Builder *builder, const Engine::Register &dv, const Register &tx,
    const Engine::Register &self, const Engine::Register::Span &span) {
    // prepare a necessary registers to be used
    auto dx = __ee__ resolve(dv);

    // ensure we preload the necessary parameters
    __ee__ parameters(self, span);

    // and attempt an invocation that is required now
    __ee__ invoke(Dispatch::spawn, dx, builder->isolate, tx, builder->stack);

    // validate the outgoing result is alright
    __ee__ validate(dx);
}
