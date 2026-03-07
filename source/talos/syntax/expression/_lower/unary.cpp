/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Unary, node, compiler, destination) {
    // allow access to the traits for operators
    namespace Traits = ::Talos::Operator::Traits;

    // emit the operand to begin with onto the sink
    compiler->lower(node->operand(), Accumulator());

    // trace the incoming binary node now
    $_UNUSED $_AUTO = compiler->trace(node);

    // attempt emitting based on the incoming opcodes
    switch (node->opcode()) {
#define TALOS_XX_TOKEN_UNARY(N, ...) \
    case Operator::Kind::N: compiler->plug<Syllable::UNOP_##N>(destination, Accumulator()); break;
        TALOS_XX_TOKEN_UNARY(NEG)
#include "talos/lexer/_defines/tokens.def"
        default: $_ABORT("Unknown unary operator '{0}'", Traits::name(node->opcode()));
    }
}

//  PRIVATE METHODS  //

Talos::Value::Any Talos::Syntax::Unary::m_fold() const noexcept {
    // get the underlying value to be handled
    auto value = m_operand->fold();

    // stop if the value is a failure here
    if (!value.traits().okay()) return value;

    // handle based on the incoming opcodes now
    switch (m_opcode) {
        case Operator::Kind::NOT: return Value::Boolean(value.truthiness());  // should be valid to ascertain now
        case Operator::Kind::NEG: return value.is<Number::Tagged>() ? -value.as<Number::Tagged>() : Value::Failure();
        case Operator::Kind::INV: return value.is<Number::Tagged>() ? ~value.as<Number::Tagged>() : Value::Failure();

        // stop for invalid opcodes now
        default: return Value::Failure();
    }
}
