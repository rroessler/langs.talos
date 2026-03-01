#ifndef _FORGE_MACHINE_TEMPLATE_HPP
#define _FORGE_MACHINE_TEMPLATE_HPP

/// Forge Modules
#include "forge/bytecode/allocator.hpp"
#include "forge/forward/bytecode.hpp"
#include "forge/forward/machine.hpp"
#include "forge/operator/kind.hpp"

namespace Forge::Machine::Template {

    //  PUBLIC METHODS  //

    /**
     * @brief Handles logical negation.
     * @param builder               Machine builder.
     * @param instruction           Instruction given.
     */
    void negate(Builder* builder, Bytecode::Instruction* instruction);

    /**
     * @brief Handles emitting coalescing operations.
     * @param builder               Machine builder.
     * @param instruction           Instruction given.
     */
    void coalesce(Builder* builder, Bytecode::Instruction* instruction);

    /**
     * @brief Handles emitting unary operations.
     * @param builder               Machine builder.
     * @param kind                  Kind of operator.
     * @param instruction           Instruction given.
     */
    void unary(Builder* builder, Operator::Kind kind, Bytecode::Instruction* instruction);

    /**
     * @brief Handles emitting binary operations.
     * @param builder               Machine builder.
     * @param kind                  Kind of operator.
     * @param instruction           Instruction given.
     */
    void binary(Builder* builder, Operator::Kind kind, Bytecode::Instruction* instruction);
    void binary_i(Builder* builder, Operator::Kind kind, Bytecode::Instruction* instruction);

    /**
     * @brief Handles emitting logical operations.
     * @param builder               Machine builder.
     * @param kind                  Kind of operator.
     * @param instruction           Instruction given.
     */
    void logical(Builder* builder, Operator::Kind kind, Bytecode::Instruction* instruction);

    /**
     * @brief Handles emitting comparison operations.
     * @param builder               Machine builder.
     * @param kind                  Kind of operator.
     * @param instruction           Instruction given.
     */
    void compare(Builder* builder, Operator::Kind kind, Bytecode::Instruction* instruction);
    void compare_i(Builder* builder, Operator::Kind kind, Bytecode::Instruction* instruction);

    /**
     * @brief Handles emitting equality operations.
     * @param builder               Machine builder.
     * @param kind                  Kind of operator.
     * @param instruction           Instruction given.
     */
    void equality(Builder* builder, Operator::Kind kind, Bytecode::Instruction* instruction);

    /**
     * @brief Handles loading field values.
     * @param builder               Machine builder.
     * @param dx                    Result register.
     * @param tx                    Target register.
     * @param index                 Constant index.
     */
    Register getter(Builder* builder, const Register&, const Bytecode::Index&);
    Register getter(Builder* builder, const Engine::Register&, const Bytecode::Index&);
    void getter(Builder* builder, const Register&, const Register&, const Bytecode::Index&);
    void getter(Builder* builder, const Engine::Register&, const Register&, const Bytecode::Index&);
    void getter(Builder* builder, const Register&, const Engine::Register&, const Bytecode::Index&);
    void getter(Builder* builder, const Engine::Register&, const Engine::Register&, const Bytecode::Index&);

    /**
     * @brief Handles templated recalls.
     * @param builder               Machine builder.
     * @param dx                    Result register.
     * @param span                  Forwarding registers.
     */
    void recall(Builder* builder, const Register& dx, const Engine::Register::Span& span = {});
    void recall(Builder* builder, const Engine::Register& dv, const Engine::Register::Span& span = {});

    /**
     * @brief Handles templated invocation.
     * @param builder               Machine builder.
     * @param dx                    Result register.
     * @param tv                    Target register.
     * @param args                  Parameter arguments.
     */
    void invoke(Builder*, const Engine::Register&, const Register&, const Engine::Register::Span&);
    void invoke(Builder*, const Engine::Register&, const Register&, const Engine::Register& = {},
        const Engine::Register::Span& = {});

    /**
     * @brief Handles templated invocation.
     * @param builder               Machine builder.
     * @param dx                    Result register.
     * @param tx                    Target register.
     * @param args                  Parameter arguments.
     */
    void invoke(Builder*, const Engine::Register&, const Engine::Register&, const Engine::Register::Span&);
    void invoke(Builder*, const Engine::Register&, const Engine::Register&, const Engine::Register& = {},
        const Engine::Register::Span& = {});

    /**
     * @brief Handles templated spawning.
     * @param builder               Machine builder.
     * @param dx                    Result register.
     * @param tv                    Target register.
     * @param args                  Parameter arguments.
     */
    void spawn(Builder*, const Engine::Register&, const Register&, const Engine::Register::Span&);
    void spawn(Builder*, const Engine::Register&, const Register&, const Engine::Register& = {},
        const Engine::Register::Span& = {});

    /**
     * @brief Handles templated spawning.
     * @param builder               Machine builder.
     * @param dx                    Result register.
     * @param tx                    Target register.
     * @param args                  Parameter arguments.
     */
    void spawn(Builder*, const Engine::Register&, const Engine::Register&, const Engine::Register::Span&);
    void spawn(Builder*, const Engine::Register&, const Engine::Register&, const Engine::Register& = {},
        const Engine::Register::Span& = {});

    /**
     * @brief Allows casting arguments from values.
     * @param values                Values reference.
     */
    inline constexpr const Function::Arguments& arguments(Value::Any*& values) {
        return *reinterpret_cast<const Function::Arguments*>(&values);
    }

}  // namespace Forge::Machine::Template

#endif
