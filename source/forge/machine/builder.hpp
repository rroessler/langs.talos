#ifndef _FORGE_MACHINE_BUILDER_HPP
#define _FORGE_MACHINE_BUILDER_HPP

/// Forge Modules
#include "forge/function/dynamic.hpp"
#include "forge/machine/emitter.hpp"

namespace Forge::Machine {

    /// @brief Simple Register Allocator.
    class Allocator {
        //  PROPERTIES  //

        /// @brief Underlying compiler instance.
        Compiler* m_compiler = nullptr;

        /// @brief Currently allocated registers.
        $::Map<Engine::Register::Encoded, Register> m_registers = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Do not allow default construction.
        explicit Allocator() = default;

        /// @brief Constructs a contiguous register allocator.
        explicit Allocator(Compiler* compiler) : m_compiler(compiler) {}

        //  PUBLIC METHODS  //

        /**
         * @brief Denotes if a register has been bound.
         * @param vreg              Bytecode register.
         */
        inline constexpr bool bound(const Engine::Register& vreg) const noexcept { return m_registers.contains(vreg); }

        /**
         * @brief Resolves an already bound register.
         * @param vreg              Bytecode register.
         */
        inline constexpr Register resolve(const Engine::Register& vreg) const noexcept { return m_registers.at(vreg); }

        /**
         * @brief Handles allocating a register.
         * @param vreg              Bytecode register.
         */
        inline constexpr Register allocate(const Engine::Register& vreg) {
            return allocate(vreg, fmt::format("{0}", vreg));
        }

        /**
         * @brief Handles allocating a register.
         * @param vreg              Bytecode register.
         * @param name              Name of register.
         */
        inline constexpr Register allocate(const Engine::Register& vreg, const $::String::View& name) {
            if (m_registers.contains(vreg)) return m_registers.at(vreg);  // get cached value
            return m_registers.emplace(vreg, m_compiler->new_gp64(name.data())).first->second;
        }
    };

    /// @brief Scoped Machine-Code Builder.
    struct Builder : public XI::Define<Builder, XI::Unique> {
        //  PROPERTIES  //

        Register isolate = {};  // Isolate register.
        Register stack = {};    // Stack register.
        Register frame = {};    // Frame register.
        Register argv = {};     // Arguments register.
        Register envp = {};     // Context register.
        Register result = {};   // Accumulator register.

        Label panic = {};      // Enables panic handling.
        Label interrupt = {};  // Enables interrupt handling.

        /// @brief Incoming function information.
        Info* info = nullptr;

        /// @brief The underlying scoped compiler.
        Compiler* compiler = nullptr;

        /// @brief Handles emitting complex instrutions.
        Emitter emitter = Emitter();

        /// @brief Handles emitting register allocations.
        Allocator registers = Allocator();

        /// @brief The available labels.
        std::vector<Label> labels = {};

        //  CONSTRUCTORS  //

        /// @brief Do not allow default construction.
        explicit Builder() = delete;

        /// @brief Constructs a defaulted builder.
        explicit Builder(Info* info, Compiler* compiler);

        /// @brief Handles closing off the builder.
        ~Builder();
    };

}  // namespace Forge::Machine

#endif
