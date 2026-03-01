#ifndef _FORGE_BYTECODE_OPTIMIZER_HPP
#define _FORGE_BYTECODE_OPTIMIZER_HPP

/// Forge Modules
#include "forge/bytecode/binder.hpp"
#include "forge/bytecode/routine.hpp"
#include "forge/runtime/options.hpp"

namespace Forge::Bytecode {

    /// @brief Compilation Optimizer.
    class Optimizer : public XI::Define<Optimizer, XI::Unique> {
        //  PROPERTIES  //

        /// @brief Underlying label allocator.
        Binder* m_labels;

        /// @brief Attached runtime options.
        const Runtime::Options* m_options;

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a bytecode optimizier.
        explicit Optimizer(Binder* labels);
        explicit Optimizer(XI::Container* services, Binder* labels);
        explicit Optimizer(Binder* labels, const Runtime::Options* options);

        //  PUBLIC METHODS  //

        /**
         * @brief Handles optimizing a given callable unit.
         * @param routine                   Routine to optimize.
         */
        void process(Routine* routine) const;

       private:
        //  PRIVATE METHODS  //

        void m_build_graph(Routine* routine) const;  // Builds the active functions CFG.
        void m_dump_graph(Routine* routine) const;   // Attempts dumping the CFG.

        void m_remove_dead_ir(Routine* routine) const;      // Removes any dead-instructions.
        void m_remove_dead_blocks(Routine* routine) const;  // Removes all dead-blocks.

        void m_remove_empty_blocks(Routine* routine) const;       // Removes all empty-blocks.
        void m_remove_useless_jumps(Routine* routine) const;      // Removes all useless jumps.
        void m_rewrite_chained_branches(Routine* routine) const;  // Re-writes chained branches.
    };

}  // namespace Forge::Bytecode

#endif
