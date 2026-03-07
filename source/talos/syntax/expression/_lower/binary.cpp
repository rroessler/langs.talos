/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

/// Forward Declarations
$_FWD(Value::Any fold(Operator::Kind, Value::Any, Value::Any), Talos::Bytecode::Constants)

//  MACROS  //

#define MM_APPLY_IMPL(L, R, ...) L.is<Number::Tagged>() && R.is<Number::Tagged>() ? __VA_ARGS__ : Value::Failure()
#define MM_APPLY_BINOP(OP, L, R) MM_APPLY_IMPL(L, R, L.as<Number::Tagged>() OP R.as<Number::Tagged>())
#define MM_APPLY_METHOD(F, L, R) MM_APPLY_IMPL(L, R, L.as<Number::Tagged>().F(R.as<Number::Tagged>()))
#define MM_APPLY_COMOP(OP, L, R) MM_APPLY_IMPL(L, R, Value::Boolean(L.as<Number::Tagged>() OP R.as<Number::Tagged>()))

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Binary, node, compiler, destination) {
    // allow access to the traits for operators
    namespace Traits = ::Talos::Operator::Traits;

    // pull out the underlying opcode
    auto opcode = node->opcode();

    // get the left/right expressions
    auto *left = node->left(), *right = node->right();
    auto lv = left->fold(), rv = right->fold();  // and fold now
    auto immediate = Bytecode::Constants::fold(opcode, lv, rv);

    // allow returning an immediate value if necessary
    if (immediate.traits().okay()) {
        auto index = compiler->constant(immediate);  // prepare constant
        return compiler->plug<Syllable::LOAD_CONST>(destination, index);
    }

    // merge the types to determine what we have
    auto type = left->traits()->lattice().join(right->traits()->lattice());

    // handle any "fast" operations if necessary to do so
    if (rv.is<Number::Tagged>()) {
        switch (opcode) {
#define TALOS_XX_SYLLABLE_INDEXED(P, N, ...)  \
    case Operator::Kind::N:                   \
        compiler->lower(left, Accumulator()); \
        return compiler->emit<Syllable::P##_##N##I>(destination, Accumulator(), compiler->constant(rv));

#include "talos/bytecode/_defines/syllables.def"
            default: break;  // allow handling as normal now
        }
    }

    auto bx = Accumulator();  // prepare ax/bx
    auto ax = compiler->registers()->temporary();

    // compile both our expression values now
    compiler->lower(left, ax), compiler->lower(right, bx);

    // trace the incoming binary node now
    $_UNUSED $_AUTO = compiler->trace(node);

    // if we have a purely "string" output type, then force a concatenation to occur
    auto concat = type.strictly(Type::Fact::STR_ANY) && opcode == Operator::Kind::ADD;
    if (concat) return compiler->plug<Syllable::STRING_CONCAT>(destination, ax, bx);

    // attempt emitting our necessary opcodes for binary instructions
    switch (opcode) {
#define TALOS_XX_TOKEN_BINARY(N, ...) \
    case Operator::Kind::N: compiler->emit<Syllable::BINOP_##N>(destination, ax, bx); break;
#define TALOS_XX_TOKEN_COMPARE(N, ...) \
    case Operator::Kind::N: compiler->emit<Syllable::TEST_##N>(destination, ax, bx); break;
#include "talos/lexer/_defines/tokens.def"
        default: $_ABORT("Unknown binary operator '{0}'", Traits::name(opcode));
    }
}

Talos::Value::Any Talos::Bytecode::Constants::fold(Operator::Kind opcode, Value::Any left, Value::Any right) {
    // stop if either values are invalid now
    if (!left.traits().okay() || !right.traits().okay()) return Value::Failure();

    // handle based on the incoming opcodes now
    switch (opcode) {
        case Operator::Kind::ADD: return MM_APPLY_BINOP(+, left, right);
        case Operator::Kind::SUB: return MM_APPLY_BINOP(-, left, right);
        case Operator::Kind::MUL: return MM_APPLY_BINOP(*, left, right);
        case Operator::Kind::DIV: return MM_APPLY_BINOP(/, left, right);
        case Operator::Kind::MOD: return MM_APPLY_BINOP(%, left, right);
        case Operator::Kind::POW: return MM_APPLY_METHOD(power, left, right);

        case Operator::Kind::BOR: return MM_APPLY_BINOP(|, left, right);
        case Operator::Kind::BAND: return MM_APPLY_BINOP(&, left, right);
        case Operator::Kind::XOR: return MM_APPLY_BINOP(^, left, right);
        case Operator::Kind::SHL: return MM_APPLY_BINOP(<<, left, right);
        case Operator::Kind::SHR: return MM_APPLY_BINOP(>>, left, right);

        case Operator::Kind::EQ: return Value::Boolean(left == right);
        case Operator::Kind::NE: return Value::Boolean(left != right);
        case Operator::Kind::LE: return MM_APPLY_COMOP(<=, left, right);
        case Operator::Kind::GE: return MM_APPLY_COMOP(>=, left, right);
        case Operator::Kind::LT: return MM_APPLY_COMOP(<, left, right);
        case Operator::Kind::GT: return MM_APPLY_COMOP(>, left, right);

        // otherwise default to a normal output value now
        default: return Value::Failure();
    }
}

//  PRIVATE METHODS  //

Talos::Value::Any Talos::Syntax::Binary::m_fold() const noexcept {
    return Bytecode::Constants::fold(m_opcode, m_left->fold(), m_right->fold());
}
