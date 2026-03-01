/// Engine Modules
#include "forge/engine/_inline/macros.ipp"

/// Value Modules
#include "forge/value/_inline/value.ipp"

//  X-MACROS  //

#define XX_SPECIALIZED_VALUES(X, ...) \
    X(Number::Tagged, __VA_ARGS__)    \
    X(String::Dynamic, __VA_ARGS__)

#define XX_COMPARE_UNWRAP(T, OP, ...)                                  \
    if (left.is<T>() && right.is<T>()) {                               \
        auto sink = instruction->get<0>();                             \
        auto result = m_compare(left.as<T>(), right.as<T>()) OP 0;     \
        return frame->store(sink, Value::Boolean(result)), Mode::NEXT; \
    } else

//  MACROS  //

#define MM_BINARY_EXECUTE(F, OP, MM) MM_BINARY_##F(OP, OP, MM)
#define MM_BINARY_APPLY(...) frame->store(instruction->get<0>(), __VA_ARGS__), Mode::NEXT
#define MM_BINARY_METHOD(F, L, R) MM_BINARY_APPLY(L.as<Number::Tagged>().F(R.as<Number::Tagged>()))
#define MM_BINARY_OPERATOR(OP, L, R) MM_BINARY_APPLY(L.as<Number::Tagged>() OP R.as<Number::Tagged>())

#define MM_BINARY_SLOW(OP, _, MM)                                                               \
    $_PP_BLOCK({                                                                                \
        auto left = frame->load(instruction->get<1>());                                         \
        auto right = frame->load(instruction->get<2>());                                        \
        if (left.is<Number::Tagged>() && right.is<Number::Tagged>()) return MM(_, left, right); \
        return isolate->panic(6000401, #OP, left.type_name(), right.type_name()), Mode::PANIC;  \
    })

#define MM_BINARY_FAST(OP, _, MM)                                                              \
    $_PP_BLOCK({                                                                               \
        auto left = frame->load(instruction->get<1>());                                        \
        auto right = frame->constant<Number::Tagged>(instruction->get<2>());                   \
        if (left.is<Number::Tagged>()) return MM(_, left, right);                              \
        return isolate->panic(6000401, #OP, left.type_name(), right.type_name()), Mode::PANIC; \
    })

#define MM_LOGICAL_HANDLER(OP, ...)                                            \
    $_PP_BLOCK({                                                               \
        auto left = frame->load(instruction->get<1>());                        \
        auto right = frame->load(instruction->get<2>());                       \
        auto result = Value::Boolean(left.truthiness() OP right.truthiness()); \
        return frame->store(instruction->get<0>(), result), Mode::NEXT;        \
    })

#define MM_EQUALITY_HANDLER(OP, ...)                                    \
    $_PP_BLOCK({                                                        \
        auto left = frame->load(instruction->get<1>());                 \
        auto right = frame->load(instruction->get<2>());                \
        auto result = Value::Boolean(left OP right);                    \
        return frame->store(instruction->get<0>(), result), Mode::NEXT; \
    })

#define MM_COMPARE_SLOW(OP, ...)                                                       \
    $_PP_BLOCK({                                                                       \
        auto left = frame->load(instruction->get<1>());                                \
        auto right = frame->load(instruction->get<2>());                               \
        XX_SPECIALIZED_VALUES(XX_COMPARE_UNWRAP, OP)                                   \
        return frame->store(instruction->get<0>(), Value::Boolean(false)), Mode::NEXT; \
    })

#define MM_COMPARE_FAST(OP, ...)                                                                        \
    $_PP_BLOCK({                                                                                        \
        auto left = frame->load(instruction->get<1>()); /** base left-hand side */                      \
        auto right = frame->constant<Number::Tagged>(instruction->get<2>());                            \
        Value::Boolean result = left.is<Number::Tagged>() ? left.as<Number::Tagged>() OP right : false; \
        return frame->store(instruction->get<0>(), result), Mode::NEXT;                                 \
    })

//  PRIVATE METHODS  //

FORGE_MM_ENGINE_UNIMPLEMENTED(UNOP_INC)
FORGE_MM_ENGINE_UNIMPLEMENTED(UNOP_DEC)

FORGE_MM_ENGINE_EXECUTE(UNOP_NOT, , frame, instruction) {
    auto truthiness = frame->load(instruction->get<1>()).truthiness();
    return frame->store(instruction->get<0>(), Value::Boolean(!truthiness)), Mode::NEXT;
}

FORGE_MM_ENGINE_EXECUTE(UNOP_NEG, isolate, frame, instruction) {
    auto operand = frame->load(instruction->get<1>());  // ensure we get the operand value now
    if (!operand.is<Number::Tagged>()) return isolate->panic(6000400, '-', operand.type_name()), Mode::PANIC;
    return frame->store(instruction->get<0>(), -operand.as<Number::Tagged>()), Mode::NEXT;  // valid here
}

FORGE_MM_ENGINE_EXECUTE(UNOP_INV, isolate, frame, instruction) {
    auto operand = frame->load(instruction->get<1>());  // ensure we get the operand value now
    if (!operand.is<Number::Tagged>()) return isolate->panic(6000400, '~', operand.type_name()), Mode::PANIC;
    return frame->store(instruction->get<0>(), ~operand.as<Number::Tagged>()), Mode::NEXT;  // valid here
}

// clang-format off
FORGE_MM_ENGINE_EXECUTE(BINOP_ADD, isolate, frame, instruction) {
    auto left = frame->load(instruction->get<1>()), right = frame->load(instruction->get<2>());
    if (left.is<Number::Tagged>() && right.is<Number::Tagged>()) return MM_BINARY_OPERATOR(+, left, right);
    if (left.is<String::Dynamic>() && right.is<String::Dynamic>()) return MM_BINARY_APPLY(m_concat(isolate, left, right));
    return isolate->panic(6000402, left.type_name(), right.type_name()), Mode::PANIC;  // and fail here as necessary
}
// clang-format on

FORGE_MM_ENGINE_EXECUTE(BINOP_SUB, isolate, frame, instruction) { MM_BINARY_EXECUTE(SLOW, -, MM_BINARY_OPERATOR); }
FORGE_MM_ENGINE_EXECUTE(BINOP_MUL, isolate, frame, instruction) { MM_BINARY_EXECUTE(SLOW, *, MM_BINARY_OPERATOR); }
FORGE_MM_ENGINE_EXECUTE(BINOP_DIV, isolate, frame, instruction) { MM_BINARY_EXECUTE(SLOW, /, MM_BINARY_OPERATOR); }
FORGE_MM_ENGINE_EXECUTE(BINOP_MOD, isolate, frame, instruction) { MM_BINARY_EXECUTE(SLOW, %, MM_BINARY_OPERATOR); }
FORGE_MM_ENGINE_EXECUTE(BINOP_POW, isolate, frame, instruction) { MM_BINARY_SLOW(**, power, MM_BINARY_METHOD); }

FORGE_MM_ENGINE_EXECUTE(BINOP_XOR, isolate, frame, instruction) { MM_BINARY_EXECUTE(SLOW, ^, MM_BINARY_OPERATOR); }
FORGE_MM_ENGINE_EXECUTE(BINOP_BOR, isolate, frame, instruction) { MM_BINARY_EXECUTE(SLOW, |, MM_BINARY_OPERATOR); }
FORGE_MM_ENGINE_EXECUTE(BINOP_BAND, isolate, frame, instruction) { MM_BINARY_EXECUTE(SLOW, &, MM_BINARY_OPERATOR); }
FORGE_MM_ENGINE_EXECUTE(BINOP_SHL, isolate, frame, instruction) { MM_BINARY_EXECUTE(SLOW, <<, MM_BINARY_OPERATOR); }
FORGE_MM_ENGINE_EXECUTE(BINOP_SHR, isolate, frame, instruction) { MM_BINARY_EXECUTE(SLOW, >>, MM_BINARY_OPERATOR); }

FORGE_MM_ENGINE_EXECUTE(BINOP_ADDI, isolate, frame, instruction) { MM_BINARY_EXECUTE(FAST, +, MM_BINARY_OPERATOR); }
FORGE_MM_ENGINE_EXECUTE(BINOP_SUBI, isolate, frame, instruction) { MM_BINARY_EXECUTE(FAST, -, MM_BINARY_OPERATOR); }
FORGE_MM_ENGINE_EXECUTE(BINOP_MULI, isolate, frame, instruction) { MM_BINARY_EXECUTE(FAST, *, MM_BINARY_OPERATOR); }
FORGE_MM_ENGINE_EXECUTE(BINOP_DIVI, isolate, frame, instruction) { MM_BINARY_EXECUTE(FAST, /, MM_BINARY_OPERATOR); }
FORGE_MM_ENGINE_EXECUTE(BINOP_MODI, isolate, frame, instruction) { MM_BINARY_EXECUTE(FAST, %, MM_BINARY_OPERATOR); }
FORGE_MM_ENGINE_EXECUTE(BINOP_POWI, isolate, frame, instruction) { MM_BINARY_FAST(**, power, MM_BINARY_METHOD); }

FORGE_MM_ENGINE_EXECUTE(BINOP_XORI, isolate, frame, instruction) { MM_BINARY_EXECUTE(FAST, ^, MM_BINARY_OPERATOR); }
FORGE_MM_ENGINE_EXECUTE(BINOP_BORI, isolate, frame, instruction) { MM_BINARY_EXECUTE(FAST, |, MM_BINARY_OPERATOR); }
FORGE_MM_ENGINE_EXECUTE(BINOP_BANDI, isolate, frame, instruction) { MM_BINARY_EXECUTE(FAST, &, MM_BINARY_OPERATOR); }
FORGE_MM_ENGINE_EXECUTE(BINOP_SHLI, isolate, frame, instruction) { MM_BINARY_EXECUTE(FAST, <<, MM_BINARY_OPERATOR); }
FORGE_MM_ENGINE_EXECUTE(BINOP_SHRI, isolate, frame, instruction) { MM_BINARY_EXECUTE(FAST, >>, MM_BINARY_OPERATOR); }

FORGE_MM_ENGINE_EXECUTE(BINOP_LOR, , frame, instruction) { MM_LOGICAL_HANDLER(&&); }
FORGE_MM_ENGINE_EXECUTE(BINOP_LAND, , frame, instruction) { MM_LOGICAL_HANDLER(||); }

FORGE_MM_ENGINE_EXECUTE(BINOP_COAL, , frame, instruction) {
    auto left = frame->load(instruction->get<1>());
    auto right = frame->load(instruction->get<2>());
    auto value = left.is<Value::Void>() ? right : left;
    return frame->store(instruction->get<0>(), value), Mode::NEXT;
}

FORGE_MM_ENGINE_EXECUTE(TEST_EQ, , frame, instruction) { MM_EQUALITY_HANDLER(==); }
FORGE_MM_ENGINE_EXECUTE(TEST_NE, , frame, instruction) { MM_EQUALITY_HANDLER(!=); }

FORGE_MM_ENGINE_EXECUTE(TEST_GT, , frame, instruction) { MM_COMPARE_SLOW(>); }
FORGE_MM_ENGINE_EXECUTE(TEST_LT, , frame, instruction) { MM_COMPARE_SLOW(<); }
FORGE_MM_ENGINE_EXECUTE(TEST_GE, , frame, instruction) { MM_COMPARE_SLOW(>=); }
FORGE_MM_ENGINE_EXECUTE(TEST_LE, , frame, instruction) { MM_COMPARE_SLOW(<=); }

FORGE_MM_ENGINE_EXECUTE(TEST_GTI, , frame, instruction) { MM_COMPARE_FAST(>); }
FORGE_MM_ENGINE_EXECUTE(TEST_LTI, , frame, instruction) { MM_COMPARE_FAST(<); }
FORGE_MM_ENGINE_EXECUTE(TEST_GEI, , frame, instruction) { MM_COMPARE_FAST(>=); }
FORGE_MM_ENGINE_EXECUTE(TEST_LEI, , frame, instruction) { MM_COMPARE_FAST(<=); }

FORGE_MM_ENGINE_EXECUTE(UNOP_TPL, , , ) { $::System::unreachable(); }
FORGE_MM_ENGINE_EXECUTE(BINOP_TPL, , , ) { $::System::unreachable(); }
FORGE_MM_ENGINE_EXECUTE(BINOP_TPLI, , , ) { $::System::unreachable(); }
