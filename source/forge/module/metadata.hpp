#ifndef _FORGE_MODULE_METADATA_HPP
#define _FORGE_MODULE_METADATA_HPP

/// Forge Modules
#include "forge/module/phase.hpp"

namespace Forge::Module {

    /// @brief Metadata Abstraction.
    struct $_ABSTRACT Metadata {
        //  TYPEDEFS  //

        /// @brief Available metadata attributes.
        template <Phase P>
        class Attributes;

        //  CONSTRUCTORS  //

        /// @brief Virtual abstract destructor.
        virtual ~Metadata() = default;
    };

}  // namespace Forge::Module

#endif
