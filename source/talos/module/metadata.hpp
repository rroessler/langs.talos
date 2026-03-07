#ifndef _TALOS_MODULE_METADATA_HPP
#define _TALOS_MODULE_METADATA_HPP

/// Talos Modules
#include "talos/module/phase.hpp"

namespace Talos::Module {

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

}  // namespace Talos::Module

#endif
