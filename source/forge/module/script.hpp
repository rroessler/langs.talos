#ifndef _FORGE_MODULE_SCRIPT_HPP
#define _FORGE_MODULE_SCRIPT_HPP

/// Forge Includes
#include "forge/module/loader.hpp"

namespace Forge::Module {

    /// @brief Script Module Implementation.
    struct Script : public Abstract<Script> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract<Script>::Abstract;
    };

}  // namespace Forge::Module

namespace Forge::Import {

    /// @brief Handles loading script modules.
    template <>
    struct Loader::Proxy<Module::Script> : public Loader::Abstract<Resource::Scheme::SCRIPT> {
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
            return services->get<Module::Script>(resource);
        }
    };

}  // namespace Forge::Import

#endif
