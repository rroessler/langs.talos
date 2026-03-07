#ifndef _TALOS_BYTECODE_ASSEMBLER_HPP
#define _TALOS_BYTECODE_ASSEMBLER_HPP

/// Talos Modules
#include "talos/linker/arena.hpp"
#include "talos/runtime/options.hpp"

namespace Talos::Bytecode {

    /// @brief Bytecode Assembler Service.
    class Assembler : public XI::Define<Assembler, XI::Unique> {
        //  TYPEDEFS  //

        /// @brief Allow the compiler internal access.
        friend class Compiler;

        /// @brief Instruction cache typing.
        using Cache = std::vector<const Instruction*>;

        //  PROPERTIES  //

        /// @brief Current top-most label.
        Label m_head = 0;

        /// @brief Available source positions.
        Mapping m_positions = {};

        /// @brief All labels that have been placed.
        Label::Placed m_placed = {};

        /// @brief All labels that are unresolved.
        Label::Unresolved m_unresolved = {};

        /// @brief Bound runtime options available.
        const Runtime::Options* m_options = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a bytecode assembler.
        explicit Assembler();
        explicit Assembler(XI::Container* services);
        explicit Assembler(const Runtime::Options* options);

        //  PUBLIC METHODS  //

        /**
         * @brief Handles assembling a routine.
         * @param routine                   Routine to assemble.
         * @param arena                     Bytecode output arena.
         */
        Linker::View process(Routine* routine, Linker::Arena* arena);

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles patching all unresolved labels.
         * @param buffer                    Buffer to patch.
         * @param arena                     Arena to be patched.
         */
        void m_patch(Linker::Buffer& buffer, Linker::Arena* arena) const;

        /**
         * @brief Handles encoding instructions.
         * @param instruction               Instruction to encode.
         * @param offset                    Current offset for the instruction.
         */
        uint64_t m_encode(const Instruction* instruction, Label::Encoded offset);

        /**
         * @brief Elides necessary instructions.
         * @param instructions              Instruction list.
         * @param next                      Current instruction.
         */
        int32_t m_elide(Cache& instructions, const Instruction* current) const;
    };

}  // namespace Talos::Bytecode

#endif
