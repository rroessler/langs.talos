#ifndef _FORGE_MODULE_ARCHIVED_HPP
#define _FORGE_MODULE_ARCHIVED_HPP

/// Forge Includes
#include "forge/module/interface.hpp"

namespace Forge::Module {

    /// @brief Bundled Archive Module.
    struct Archived : public Abstract<Archived> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructors.
        using Abstract<Archived>::Abstract;

        /**
         * @brief Constructs an archive from an arena.
         * @param arena                     Codegen arena.
         */
        explicit Archived($::Ptr::Unique<Linker::Arena>&& arena);
        explicit Archived(XI::Container* services, $::Ptr::Unique<Linker::Arena>&& arena);

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles parsing a module.
         * @param services                  Service container.
         * @param syntax                    Syntax metadata.
         */
        void m_parse(XI::Container* services, Metadata::Attributes<Phase::PARSED>* syntax) final;

        /**
         * @brief Handles analyzing a module.
         * @param services                  Service container.
         * @param types                     Type analysis metadata.
         */
        void m_analyze(XI::Container* services, Metadata::Attributes<Phase::TYPED>* types) final;

        /**
         * @brief Handles compiling a module.
         * @param services                  Service container.
         * @param metadata                  Compilation metadata.
         */
        void m_compile(XI::Container* services, Metadata::Attributes<Phase::COMPILED>* metadata) final;
    };

}  // namespace Forge::Module

#endif
