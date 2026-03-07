#ifndef _TALOS_MODULE_DYNAMIC_HPP
#define _TALOS_MODULE_DYNAMIC_HPP

/// Talos Includes
#include "talos/module/interface.hpp"
#include "talos/module/loader.hpp"

namespace Talos::Module {

    /// @brief Type Declaration Module.
    struct Dynamic : public Abstract<Dynamic> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract<Dynamic>::Abstract;

        //  PUBLIC METHODS  //

        /// @brief Gets the associated library name.
        inline constexpr $::String::View name() const noexcept { return resource().body(); }

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

        /**
         * @brief Handles interpreting a module.
         * @param isolate                   Runtime isolate.
         * @param exports                   Exports metadata.
         */
        Async::Thenable* m_interpret(Runtime::Isolate* isolate, Metadata::Attributes<Phase::EXPORTED>* exports) final;
    };

}  // namespace Talos::Module

namespace Talos::Import {

    /// @brief Handles loading dynamic modules.
    template <>
    struct Loader::Proxy<Module::Dynamic> : public Loader::Abstract<Resource::Scheme::DYNAMIC> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;

        //  PUBLIC METHODS  //

        /**
         * @brief Handles fetching a module.
         * @param resource                  Resource to fetch.
         * @param services                  Services container.
         */
        inline $::Ptr::Unique<Module::Interface> fetch(
            const $::URI::View& resource, XI::Container* services) const final {
            return services->get<Module::Dynamic>(resource);
        }
    };

}  // namespace Talos::Import

#endif
